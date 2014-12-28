#include "VWGet.h"
#include "TWindow.h"

main()
{	
	VWGetApplication	myApplication;

	myApplication.Run();

	return(0);
}

VWGetApplication::VWGetApplication()
		  		  : BApplication("application/x-vnd.slema-vwget")
{

	BRect			aRect;

	// set up a rectangle and instantiate a new window
	aRect.Set(100, 80, 100+600, 80+32);
	mainWindow = new TWindow(aRect);
			
	// make window visible
	mainWindow->Show();


//INIT avec valeurs fake
//snooze(3000 *1000); //pause de trois secondes histoire de voir...

}


/*
void VWGetApplication::ArgvReceived(int32 argc, char **argv)
{


text_main(argc, argv); 


}
*/

bool VWGetApplication::QuitRequested()
{

char str[2048];

  if (download_over==true || params_entered==false)  return true; 
  //quitte direct si le dl est terminé ou si les params_ont pas été entrés.. 
  {
  BAlert *alert = new BAlert("", 
                     "Do you really wish to abort this download?", 
                     "Cancel", "Erase file","Continue later",B_WIDTH_FROM_WIDEST); 
   int32 button_index;

 
   switch(button_index = alert->Go())
   {
   //les boutons ont toujours les valeurs 0,1,2 (trois boutons max)
   case 0:
   //back to the jeu
   break;

	case 1:
	kill_thread(ptg.wget_thread); //kill the download thread so that it won't interfere when deleting
	sprintf(str,"rm %s",save_name);
	system(str);
	return true ; //and we quit
	break;
	
   	
   case 2:
	if (server_supports_resume==false) //AVERTIR SI ON SUPPORTE pas le resume qu'on pourra pas recommencer
	{
		BAlert *xxalert = new BAlert("","Warning, server does not support resuming aborted downloads, your file will be lost if you close connection.",
	 	"Cancel","Do it anyway",NULL,B_WIDTH_FROM_WIDEST); 
		int32 b_index;
	
		switch(b_index = xxalert->Go())
  			 {
  				 case 0: break; //reste
   				 case 1: return(true); break; //quitte
			 }	
   		}
    else
    	{
			return(true); //QUITTE
    	}
    break;
    
	}
	return false;
	} //fin download over
}

void VWGetApplication::MessageReceived (BMessage *msg)
{

	       
	switch (msg->what)
	{
		case MAKE_ME_BEEP:
		beep();
		break;
		
		
	}
}	

//---------------------------------


//---------------------------------------------------------
//BIG THANKS TO TYLER RITI FOR writing the base of the following functions...
//It surely would have taken me years to understand how to do it alone ;-)
//---------------------------------------------------------

int32 start_engines(void *obj)
{
    // Take the pointer and cast it to the VWGetApplication type.
    // Call the StartEngines() method on it.
    return ((VWGetApplication *)obj)->StartEngines();
}

void VWGetApplication::ArgvReceived(int32 argc, char **argv)
{

if (is_command_line==true) params_entered=true; 


//envoie les paramètres à la version originale
		mainWindow->SetTitle("Visual-WGet - Connecting..."); 
		//si on a reçu le paramètre on peut swapper les views...
		Lock();
		mainWindow->Lock();
		mainWindow->paramView->RemoveSelf();
		mainWindow->mainView = new TView(mainWindow->Bounds() , "");
		mainWindow->AddChild(mainWindow->mainView);
		mainWindow->Unlock();
		Unlock();

//-------------------------------------------------------------------------------

    
    // These two variables are private members of the VWGetApplication class
    arg_count = argc;

//    arg_values = argv; //we can't just do that since the pointer might not be valid anymore
						 //which is the case when invoking from command-line  
  
arg_values = new char *[argc];
for (int32 i = 0; i < argc; ++i)
{
	arg_values[i] = new char[strlen(argv[i]) + 1];
	strcpy(arg_values[i], argv[i]); // I hope this isn't backwards!
}

    
    // Spawn a thread and give the thread function a pointer to
    // this object.

    ptg.wget_thread = spawn_thread(start_engines, "wget_function", 
        B_NORMAL_PRIORITY, (void *)this);
    resume_thread(ptg.wget_thread);
    
    //save the thread id in order to be able to kill it if needed (canceled download)
    
}

int32 VWGetApplication::StartEngines(void)
{
    // We are still in the engine_thread but now we can access
    // arg_count and arg_values because we've got access to
    // the implicit 'this' pointer.
    
    // Print the arguments
    	printf("\n\nArguments passed to the original WGet main function \n");
	    for (int32 i = 0; i < arg_count; ++i)
  	  	printf("%ld: %s\n", i, arg_values[i]);
    
    text_main(arg_count, arg_values); 
    return 1;
}

