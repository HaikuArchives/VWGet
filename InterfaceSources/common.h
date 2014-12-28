#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

int text_main(int argc, char **argv);

extern unsigned long file_length;
extern unsigned long current_value;
extern unsigned long previous_value; 
extern unsigned long the_time;
extern char the_url[2048];
extern char the_info[2048];
extern int server_supports_resume;
extern int is_command_line;
extern int params_entered;
extern int error_happened;
extern int download_over;
extern char save_name[2048];
extern char save_path[2048];
extern char only_file_name[256];
extern void init_params();
extern int can_restart;

#ifdef __cplusplus
}
#endif


#endif 