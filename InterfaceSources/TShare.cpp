#include "TShare.h"

TShare ptg;
//LanguageClass	Language;

TShare::TShare()
{
	paused = false;
	color_error =	(rgb_color) { 200,   0,   0};
	color_normal =	(rgb_color) {   0, 127, 255};
	color_paused =	(rgb_color) {   0, 200, 200};
	color_over =	(rgb_color) {   0, 200,   0};
}
