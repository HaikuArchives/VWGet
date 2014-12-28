#ifndef T_WINDOW_H
#define T_WINDOW_H

#include <Window.h>
#include "TShare.h"
#include "EnterParams.h"
#include "TView.h"

class TWindow : public BWindow {
public:
					TWindow(BRect frame);
	virtual	bool	QuitRequested();
	virtual void	MessageReceived (BMessage *msg);
	TView*			mainView;
	ParamView*		paramView;
	BFilePanel*		panneau_save;
	bool			file_panel_created;

	int16			nb_args;
	BAlert*			alert;
	char*			final;
	char			str[1024];
	char			stra[1024];
	char			strb[1024];
	char			strc[1024];
	char*			ptr[10];
	const char*		FileName;

	entry_ref		Directory; // Ref sur le répertoire dans lequel sauver
	BPath			the_path;
	BEntry			entry;
};

#endif
