#ifndef T_SHARE_H
#define T_SHARE_H
#include "common.h"
#include "SharedMessages.h"

//ALL includes are here for simplicity

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <Application.h>
#include <Window.h>
#include <View.h>

#include <Alert.h>
#include <Path.h>
#include <Bitmap.h>
#include <StringView.h>
#include <ScrollView.h>
#include <ScrollBar.h>
#include <BitmapStream.h>
#include <TranslatorRoster.h>
#include <List.h>
#include <ListView.h>
#include <TextView.h>
#include <TextControl.h>
#include <ColorControl.h>
#include <CheckBox.h>
#include <Beep.h>
#include <File.h>
#include <FilePanel.h>
#include <Slider.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <MenuField.h>
#include <Screen.h>
#include <Roster.h>
#include <TranslationUtils.h>
#include <PictureButton.h>
#include <Control.h>
#include <StatusBar.h>
#include <NodeInfo.h>
#include <AppFileInfo.h>

#define UPDATE_TITLE 'udtt'
#define URL_GIVEN	'urlg'
#define NAME_CHOSEN 'nmch'
#define ABOUT_BOX 'abbx'
#define PAUSE_DOWNLOAD 'psdl'

class TShare {
public:
	TShare();
	bool paused;
	thread_id wget_thread;

	rgb_color color_error;
	rgb_color color_normal;
	rgb_color color_paused;
	rgb_color color_over;
};

extern TShare ptg;
#endif
