#include "EnterParams.h"

ParamView::ParamView(BRect rect, const char *name)
	   	   : BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW)
{
SetViewColor(216,216,216);
BRect r;
r.Set(16,Bounds().Height()-24, Bounds().Width()-32,Bounds().Height());
the_params= new BTextControl(r, NULL, "URL:", "", NULL );
the_params->SetDivider(22);
AddChild(the_params);

/*
r.Set(Bounds().Width()-200+4,Bounds().Height()-24, Bounds().Width()-116,Bounds().Height());
login= new BTextControl(r, NULL, "L:", "", NULL ); 
login->SetDivider(10);
AddChild(login);

r.Set(Bounds().Width()-100+4,Bounds().Height()-24, Bounds().Width()-32,Bounds().Height());
pass= new BTextControl(r, NULL, "P:", "", NULL );
pass->SetDivider(10);
AddChild(pass);
*/

r.Set(Bounds().Width()-28,6, Bounds().Width()-2,Bounds().Height()-4);
confirm= new BButton(r,"", "Go", new BMessage(URL_GIVEN) );
AddChild(confirm);

r.Set(0,4,16,Bounds().Height()-4);
BButton *bt = new BButton(r,"", " ?", new BMessage(ABOUT_BOX) );
AddChild(bt);


init_params();
}
