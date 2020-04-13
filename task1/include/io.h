#ifndef IO
#define IO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void write_to_file(FILE* stream, char file_name[], char * track_data, int track_specific_length, int * track_depth, int * track_depth_type);
void print_track(char * track_data_start, int track_specific_length, int * track_depth, int * track_depth_type);
void write_params_to_file(int * track_length, int * track_depth, int * track_depth_type, int * track_freq,
                                                                        char * file_param_name, FILE *stream_par);
void recover_from_file(char ** track_data, int * track_length, int * track_depth, int * track_depth_type, int * track_freq,
                            char * file_name, char * file_param_name, FILE *stream, FILE *stream_par, int * track_memory_allocated);

#endif