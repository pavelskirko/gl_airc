#ifndef IO
#define IO

#include <stdio.h>
#include <string.h>

void write_to_file(FILE* stream, char file_name[], char * track_data, int track_specific_length, int * track_depth, int * track_depth_type);
void print_track(char * track_data_start, int track_specific_length, int * track_depth, int * track_depth_type);

#endif