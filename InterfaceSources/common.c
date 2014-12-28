/* C'est juste du C, on crée les variables définies dans common.h */
#include "common.h"
#include <stdio.h>

unsigned long file_length;
unsigned long current_value;
unsigned long previous_value;
unsigned long the_time;
int server_supports_resume; //1 pour true qui est pas défini ici
int download_over; //= 0pour false
char the_url[2048]; //"" to avoid displaying garbage in titlebar at startup
char the_info[2048];
char save_name[2048];
char save_path[2048];
char only_file_name[256];
int params_entered;
int error_happened;
int can_restart;

int is_command_line; //1=true

void init_params()
{
	file_length = 0;
	current_value = 0;
	previous_value = 0;
	the_time = 0;
	server_supports_resume = 1; //1 pour true qui est pas défini ici
	download_over = 0; //= 0pour false
	sprintf(the_url, "(...)"); //"" to avoid displaying garbage in titlebar at startup
	sprintf(the_info, "(...)");
	sprintf(save_name, "(...)");
	sprintf(save_path, "(...)");
	sprintf(only_file_name, "(...)");
	params_entered = 0; //0=false
	is_command_line = 1; //1=true
	error_happened = 0; //0=false
	can_restart = 0; //0=false
}


