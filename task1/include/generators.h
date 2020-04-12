#ifndef GENERATORS
#define GENERATORS

#include <math.h>
#include <string.h>

void sine_generator(char * track_data_start, int * track_depth, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl);
void triangle_generator(char * track_data_start, int * track_depth, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl);

#endif