#include <Application.h>
#include "TWindow.h"
#include "TView.h"


TWindow::TWindow(BRect frame)
	:
	BWindow(frame, "Visual-WGet",
			B_TITLED_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	SetPulseRate(500 * 1000); //2 fois par second 

	SetLook(B_FLOATING_WINDOW_LOOK);

	// set up a rectangle and instantiate a new view
	paramView = new ParamView(Bounds(), "");
	AddChild(paramView);

	file_panel_created = false;

	PostMessage(new BMessage(UPDATE_TITLE));
}


bool TWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return false;
}


void TWindow::MessageReceived (BMessage *msg)
{
	switch (msg->what) {
		case PAUSE_DOWNLOAD:
			if (can_restart == true) {
				//if there's been an error the button causes to bring back the parameter enter view
				be_app->Lock();
				Lock();
				mainView->RemoveSelf();
				paramView = new ParamView(Bounds(), "");
				AddChild(paramView);
				Unlock();
				be_app->Unlock();
				init_params();

				PostMessage(new BMessage(UPDATE_TITLE));
			}
			else {
				if (ptg.paused == false) {
					//Pause
					ptg.paused = true;
					suspend_thread(ptg.wget_thread);
					download_over = true; //stop la boucle display
					mainView->progress->SetBarColor(ptg.color_paused);
					//sinon la barre se redraw pas
					mainView->progress->Draw(mainView->progress->Bounds());
					sprintf(the_info, "(PAUSED)");
					PostMessage(new BMessage(UPDATE_TITLE));
				}
				else {
					//restart 
					mainView->progress->SetBarColor(ptg.color_normal);
					mainView->progress->Draw(mainView->Bounds()); //sinon la barre se redraw pas
					sprintf(the_info, "...");
					PostMessage(new BMessage(UPDATE_TITLE));
					ptg.paused = false;
					download_over = false; //relance la boucle display d'abord
					resume_thread(ptg.wget_thread);
				}
			}
			break;

		case UPDATE_TITLE:
			if (params_entered == true) {
				Lock();
				sprintf(str, "VWGet - ");
				strcat(str, only_file_name);
				strcat(str, " - ");
				strcat(str, the_info);
				if (error_happened == true)
					strcat(str, " -- DOWNLOAD ABORTED");
				if (server_supports_resume == false)
					strcat(str, "  >>NO RESUMING!<<");
				// printf("\nThe title is: %s",str);
				SetTitle(str);
				Unlock();
			}
			else {
				SetTitle("Visual-WGet - Enter URL to download from and press Go");
			}
			break;

		case URL_GIVEN:
			is_command_line = false;
			params_entered = true;

			if (file_panel_created == false) {
				panneau_save =
					new BFilePanel(B_SAVE_PANEL,
							NULL, NULL, B_FILE_NODE,
							false, NULL, NULL, false, true);
				file_panel_created = true;
				panneau_save->SetPanelDirectory("/boot/");
				panneau_save->SetTarget(this);
				panneau_save->Window()->SetTitle("Save file as...");
			}
			panneau_save->Show();

			//on met le nom du fichier dans le savepanel
			final = rindex(paramView->the_params->Text(), '/'); //se place sur le dernier slash de URL
			if (final!=NULL) {
				final++ ; //on saute le slash
				panneau_save->SetSaveText(final);
			}
			break;

		case NAME_CHOSEN:
			sprintf(str, "Visual-Wget"); //nom de l'application ;-)
			sprintf(stra, paramView->the_params->Text());

			ptr[0] = NULL;
			ptr[1] = NULL;
			ptr[2] = NULL;
			ptr[3] = NULL;
			ptr[4] = NULL;
			ptr[5] = NULL;
			ptr[6] = NULL;
			ptr[7] = NULL;

			//These two are essential 
			ptr[0] = str;
			ptr[1] = stra;
			nb_args = 2;

			// If I remove the following lines (output and continue)
			// the bug not allowing to download after having cancelled disappears

			//output-document	
			if (is_command_line == false) {
				sprintf(strb, "--output-document=");
				strcat(strb, save_name);
				nb_args++;
				ptr[nb_args - 1] = strb; //active_arg = nb_args-1 !!! 
			}

			server_supports_resume = true;	//FOR TESTING PURPOSES, testing not implemented yet

			//--continue
			if (server_supports_resume==true) {
				sprintf(strc, "--continue");   //avec l'option continue
				nb_args++;
				ptr[nb_args - 1] = strc; //active_arg = nb_args-1 !!!  
			}

			be_app->ArgvReceived(nb_args,ptr);
			break;

		case B_SAVE_REQUESTED:
			msg->FindRef("directory", &Directory );
			msg->FindString( "name",  &FileName);
			sprintf(only_file_name, FileName);

			entry = &Directory;
			entry.GetPath(&the_path);

			sprintf(save_path, the_path.Path()); //on en a besoin pour faire un local CD...
			sprintf(save_name, save_path);
			strcat(save_name, "/");
			strcat(save_name, only_file_name);

			PostMessage(NAME_CHOSEN);
			break;

		case ABOUT_BOX:
			alert = new BAlert("",
			             "Visual-WGet 0.8b for the BeOS\n\n"
			             "by Santiago Lema <santiago.lema@cryogen.ch>\n"
			             "based on GNU's WGet 1.5.2\n"
			             "by Hrvoje Niksic <hniksic@srce.hr>\n"
			             "Freeware: see included licence\n\n"
			             "Get latest version on Beware or at:\n"
			             "http://home.beoscentral.com/free/\n"
			             "\nReleased in March 1999.",
			             "So what?",NULL,NULL,
						 B_WIDTH_FROM_WIDEST, B_INFO_ALERT);
			alert->Go(NULL);
			break;
	}
}
