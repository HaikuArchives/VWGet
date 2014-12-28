#ifndef PARAM_VIEW_H
#define PARAM_VIEW_H

#include <View.h>
#include "TShare.h"

class ParamView : public BView
{
public:
	ParamView(BRect frame, const char* name);
	BTextControl* the_params;
	BButton* confirm;

	char title[1024];
};


#endif
