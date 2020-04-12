#include "io.h"

void write_to_file(FILE* stream, char file_name[], char * track_data, int track_specific_length, int * track_depth, int * track_depth_type)
{
   stream = fopen(file_name, "w");
   if (*track_depth_type)
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         float sample = 0;
         memcpy(&sample, track_data + i * *track_depth / 8, *track_depth / 8);
         fprintf(stream, "%f\n", sample);
      }      
   }
   else
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         int sample = 0;
         memcpy(&sample, track_data + i * *track_depth / 8, *track_depth / 8);
         if(sample & (1 << (*track_depth - 1))) // if it was originally negative
         {
             sample = -1; // not efficient but clear way to make sure it will be negative in Two's complement notation
             memcpy(&sample, track_data + i * *track_depth / 8, *track_depth / 8);
         }
         fprintf(stream, "%i\n", sample);
      }
   }
   fclose(stream);    
}

void print_track(char * track_data_start, int track_specific_length, int * track_depth, int * track_depth_type)
{
   // track_specific_length is a number of samples in the track
   if (*track_depth_type)
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         float sample = 0;
         memcpy(&sample, track_data_start + i * *track_depth / 8, *track_depth / 8);
        //  track_data_start += *track_depth / 8;
         printf("%f ", sample);
      }      
   }
   else
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         int sample = 0;  
         memcpy(&sample, track_data_start + i * *track_depth / 8, *track_depth / 8);
         if(sample & (1 << (*track_depth - 1))) // if it was originally negative
         {
             sample = -1; // not efficient but clear way to make sure it will be negative in Two's complement notation
             memcpy(&sample, track_data_start + i * *track_depth / 8, *track_depth / 8);
         }
         printf("%d ", sample);
      }
   }   
}