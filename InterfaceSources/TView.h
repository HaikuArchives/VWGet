#ifndef T_VIEW_H
#define T_VIEW_H

#include <View.h>
#include "TShare.h"

class TView : public BView {
public:
						TView(BRect frame, const char *name);
	BStatusBar*			progress;
	BStringView*		speed;
	BStringView*		remaining;
	BPictureButton*		pause;

	void SetDisplay();
	void DoDisplay();
	void TimeDisplay();
	void FinalDisplay();
	void InitDisplay();
	void StopDownload();
	void SetBackButton();

	virtual void Pulse();
	virtual void	AttachedToWindow();

	float			kbytes_per_second;
	float			percent_val;
	uint32_t		old_time;
	uint32_t		old_value;
	bool			first_time;
	char			str[255];
	thread_info		tr_info;
};


#endif
