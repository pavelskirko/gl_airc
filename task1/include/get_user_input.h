#ifndef GET_USER_INPUT
#define GET_USER_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void get_user_input(int * track_length, int * track_depth, int * track_depth_type, int * track_freq, int * intrvl_type, int * intrvl_start, 
                    int * intrvl_length, int * ampl, int * freq, int * phase, int * user_choise, int * user_choise_2nd, char * file_name);
void ask_user(char * question, int * answer);

#endif