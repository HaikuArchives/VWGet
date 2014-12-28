#ifndef T_VIEW_H
#define T_VIEW_H

#include <View.h>
#include "TShare.h"

class TView : public BView 
{
public:
	TView(BRect frame, const char *name); 
BStatusBar		*progress;
BStringView		*speed,*remaining;
BPictureButton *pause;

void SetDisplay();
void DoDisplay();
void TimeDisplay();
void FinalDisplay();
void InitDisplay();
void StopDownload();
void SetBackButton();

virtual void Pulse();

float kbytes_per_second;
float percent_val;
uint32 old_time, old_value;
bool first_time;
char str[255];
thread_info tr_info;
virtual void AttachedToWindow();
};


#endif 
