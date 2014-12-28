#include "TView.h"

TView::TView(BRect rect, const char *name)
	   	   : BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW | B_PULSE_NEEDED )
{

SetViewColor(216,216,216);


BRect t_rect = Bounds();
t_rect.Set(0,0,Bounds().Width()-32,20);

progress = new BStatusBar(t_rect,NULL,NULL,NULL);
progress->SetBarHeight(7);
progress->SetBarColor(ptg.color_normal);

AddChild(progress);

progress->SetText("(URL)");
progress->SetTrailingText("(0% - 0 bytes)");

speed = new BStringView(BRect(0,24,((Bounds().Width()-32)/2)-48,24+10),"", "(speed)");
AddChild(speed);


remaining = new BStringView(BRect(((Bounds().Width()-32)/2)-48,24,Bounds().Width()-32,24+10),"", "(remaining time)");
remaining->SetAlignment(B_ALIGN_RIGHT);
AddChild(remaining);

//--------------------

InitDisplay();
}

void TView::InitDisplay()
{

old_time=0;
old_value=0;
first_time=true;
}

//---------------------------------------------------------------------

void TView::SetDisplay()
{


if (download_over==false)
{

if (file_length!=0)
{



sprintf(str,"(%ld / %ld)",current_value,file_length);
progress->SetTrailingText(str); 


//CALCUL kb/sec
percent_val =(float(current_value)/file_length*100);

if (current_value > 0) 
	{	
	sprintf(the_info," %.2f%% ",percent_val);
	Window()->PostMessage(new BMessage(UPDATE_TITLE));
	float delta = percent_val - progress->CurrentValue();
	if (delta>=0.5) progress->Update(delta); //sinon il fait des updates trop petits qui niquent l'affichage
	}



if  ((the_time-old_time) > 4 ) //chaque cinq seconde
	{
	kbytes_per_second = float(((current_value-old_value))/1024) / (the_time - old_time);
	old_time  = the_time;
	old_value = current_value;
	DoDisplay();
	}


			
if (first_time==true) 
	{
		//if we're from the command line we didn't receive the NAME_CHOSEN message
		if (is_command_line==true)
		{
		char *final = rindex(the_url, '/'); //se place sur le dernier slash de URL
		if (final!=NULL) 
			{
				final++ ; //on saute le slash
				sprintf(only_file_name, final);
			}
		}
	progress->SetText(the_url);
	first_time=false;
	}

//check si download over (attention faut rester à l'intérieur de if (file_length!=0) )
//et après l'update des textes...
if (current_value==file_length)  { StopDownload(); FinalDisplay(); return; }



}//fin if file_lenght!=0
}//fin if download over

TimeDisplay(); //faut bien updater elapsed time en real_time ;-)


	//pour updater les messages dans the_info (ceux de Wget) nottamment les "logging in as" etc.
	Window()->PostMessage(new BMessage(UPDATE_TITLE));



//Check si la tâche wget_function existe (sinon erreur donc...)
if ( get_thread_info(ptg.wget_thread, &tr_info) != B_NO_ERROR ) 
  	 {
 					progress->SetBarColor(ptg.color_error);
					progress->Draw(progress->Bounds()); //sinon la barre se redraw pas
					error_happened=true;
  	 				StopDownload();
	}

}


void TView::Pulse()
{
	SetDisplay();
}


void TView::DoDisplay()
{


//affichage kb/sec	
if (kbytes_per_second > 1024) sprintf(str,"Download speed: %3.2f Mb/sec (WOW!)",kbytes_per_second/1024); 
else
{
	if (kbytes_per_second > 1) sprintf(str,"Download speed: %3.2f kb/sec",kbytes_per_second); 
	else sprintf(str,"Download speed: %3.0f bytes/sec",kbytes_per_second*1024); 
}
speed->SetText(str);


}

void TView::StopDownload()
{
					beep();
					download_over=true; 
					Window()->SetPulseRate(0); //stop it
				   	Window()->PostMessage(new BMessage(UPDATE_TITLE));
				    SetBackButton();//if the download is over (or arborted) the pause/play button turns into a back button
}



void TView::FinalDisplay()
{
		
kbytes_per_second = (float(current_value)/1024) / the_time; //moyenne pendant durée totale download

//affichage kb/sec	
if (kbytes_per_second > 1024) sprintf(str,"Average download speed: %3.2f Mb/sec (WOW!)",kbytes_per_second/1024); 
else
{
	if (kbytes_per_second > 1) sprintf(str,"Average download speed: %3.2f kb/sec",kbytes_per_second); 
	else sprintf(str,"Average download speed: %3.0f bytes/sec",kbytes_per_second*1024); 
}
speed->SetText(str);

TimeDisplay();

			progress->SetBarColor(ptg.color_over);
			progress->Update(100); //des fois, selon les cas elle va pas au fond...
			progress->Draw(progress->Bounds()); //sinon la barre se redraw pas
			sprintf(the_info,"This download completed succesfully.");
			Window()->PostMessage(new BMessage(UPDATE_TITLE));

void SetBackButton();

}


void TView::TimeDisplay()
{

//-----------
uint32 elp_seconds = the_time;
uint32 elp_minutes = uint32(elp_seconds/60);
elp_seconds -= (elp_minutes*60);
uint32 elp_hours = uint32(elp_minutes/60);
elp_minutes -= (elp_hours*60);

//-------------
uint32 rem_seconds = uint32((file_length-current_value)/(kbytes_per_second*1024));
uint32 rem_minutes = uint32(rem_seconds/60);
rem_seconds -= (rem_minutes*60);
uint32 rem_hours = uint32(rem_minutes/60);
rem_minutes -= (rem_hours*60);


if (download_over==false)
sprintf(str,"Elapsed time:  %ld h %ld min %ld s     Remaining time: %ld h %ld min %ld s",
		elp_hours,elp_minutes,elp_seconds,rem_hours,rem_minutes,rem_seconds);

else sprintf(str,"Elapsed time:  %ld h %ld min %ld s", elp_hours,elp_minutes,elp_seconds);

remaining->SetText(str);



}

void TView::AttachedToWindow()
{

//To create the picture needed by the pause button the view needs to be attached.

BRect rect;
//CREATE A TWO STATE BUTTON FOR THE PAUSE BUTTON
rect.Set(Bounds().Width()-28,6, Bounds().Width()-2,Bounds().Height()-4);

//WIDTH = 26;
//HEIGHT = 22;
			

			//fill bitmap
			BBitmap *downBitmap = BTranslationUtils::GetBitmap('RGBB',111);
			BBitmap *upBitmap  =  BTranslationUtils::GetBitmap('RGBB',222);
			
			//just in case the resources happen to be missing
			if (downBitmap == NULL) downBitmap = new BBitmap(BRect(0,0,26-1,22-1),B_RGB32);
			if (upBitmap == NULL) upBitmap  =  new BBitmap(BRect(0,0,26-1,22-1),B_RGB32);
			
			//tempview for creating the picture
			BView *tempView = new BView( BRect(0,0,26-1,22-1), "temp", B_FOLLOW_NONE, B_WILL_DRAW );
			AddChild(tempView);
	

			BPicture *on,*off;
			
			//create on picture
			tempView->BeginPicture(new BPicture); 
   			tempView->DrawBitmap(upBitmap);
   			on = tempView->EndPicture();
   			
   			//create off picture
   			tempView->BeginPicture(new BPicture); 
   			tempView->DrawBitmap(downBitmap);
   			off = tempView->EndPicture();
   			//get rid of tempview
   			RemoveChild(tempView);
   			delete tempView;

pause = new BPictureButton(rect,"",off, on, new BMessage(PAUSE_DOWNLOAD),B_TWO_STATE_BUTTON);
AddChild(pause);

//-----------------



}



void TView::SetBackButton()
{

can_restart = true;

be_app->Lock();
Window()->Lock();

BRect rect = pause->Frame(); //same coordinates as the old one

//WIDTH = 26;
//HEIGHT = 22;
			
			//fill bitmap
			BBitmap *downBitmap = BTranslationUtils::GetBitmap('RGBB',333);
			
			//just in case the resources happen to be missing
			if (downBitmap == NULL) downBitmap = new BBitmap(BRect(0,0,26-1,22-1),B_RGB32);
			
			//tempview for creating the picture
			BView *tempView = new BView( BRect(0,0,26-1,22-1), "temp", B_FOLLOW_NONE, B_WILL_DRAW );
			AddChild(tempView);
	
			BPicture *on;
			
			//create on picture
			tempView->BeginPicture(new BPicture); 
   			tempView->DrawBitmap(downBitmap);
   			on = tempView->EndPicture();
   			
   			//get rid of tempview
   			RemoveChild(tempView);
   			delete tempView;

pause->RemoveSelf();
pause = new BPictureButton(rect,"",on, on, new BMessage(PAUSE_DOWNLOAD)); //oui 2x la même image
AddChild(pause);

Window()->Unlock();
be_app->Unlock();
}
