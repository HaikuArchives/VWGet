#ifndef VWGet_H
#define VWGet_H

#include <Application.h>

#include "TShare.h"
#include "TWindow.h"

class VWGetApplication : public BApplication
{
public:
					VWGetApplication();
	virtual void	ArgvReceived(int32 argc, char** argv);
	virtual void	MessageReceived (BMessage* msg);
	bool			QuitRequested();

	TWindow*		mainWindow;
	BWindow* fakeWin;

	//Big thanks to Tyler Riti:
	int32 StartEngines(void);

private:
	int32 arg_count;
	char** arg_values;
};

#endif
