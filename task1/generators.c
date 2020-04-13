#include "generators.h"

void track_depth_check(int * track_depth, int * track_depth_residual)
{
   // C mostly works with data in bytes, so the size of values should be a multiple of 8
   // custom bit depth implemented by limiting maximum and minimum value of generated signals
   if(*track_depth % 8 != 0 && *track_depth_residual == 0)
   {
      *track_depth_residual = 8 - *track_depth % 8;
      *track_depth = *track_depth - (*track_depth % 8) + 8; // to make it a multiple of 8
      // so (track_depth - track_depth_residual) will be a real track depth 
   }
   
}

void sine_generator(char * track_data_start, int * track_depth, int * track_depth_residual, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl)
{
   // specific_freq = interval_freq/track_freq
   // specific_phase = interval_phase / track_freq
   // specific_length = lendth(seconds) * track_freq

   // track_depth_check(track_depth, track_depth_residual);

   for (int i = 0; i < specific_length; i++)
   {
      if (*track_depth_type)
      {
         float sample = *ampl * sin(specific_phase + 6.28 * specific_freq * i);
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }
      else
      {
         int sample = (int)( *ampl * (sin(specific_phase + 6.28 * specific_freq*i)));
         if (sample > pow(2,*track_depth - 1 - *track_depth_residual)) // 2 ^ (*track_depth - 1) is max value of signed (*track_depth)-bit number  
         {
            sample = pow(2,*track_depth - 1 - *track_depth_residual) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1 - *track_depth_residual))
         {
             sample = -pow(2,*track_depth - 1 - *track_depth_residual);
         }
         
         memcpy(track_data_start, &sample, *track_depth / 8); // track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }  
   }
}

void triangle_generator(char * track_data_start, int * track_depth, int * track_depth_residual, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl)
{
   for (int i = 0; i < specific_length; i++)
   {
      if (*track_depth_type)
      {
         float sample = (double)*ampl * asin(sin(specific_phase + 6.28 * specific_freq * i)) * (2 / 3.14);
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }
      else
      {
         int sample = (int) ((double)*ampl * asin(sin(specific_phase + 6.28 * specific_freq * i)) * (2 / 3.14) );
         if (sample > pow(2,*track_depth - 1 - *track_depth_residual)) // 2 ^ (*track_depth - 1) is max value of signed (*track_depth)-bit number  
         {
            sample = pow(2,*track_depth - 1 - *track_depth_residual) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1 - *track_depth_residual))
         {
             sample = -pow(2,*track_depth - 1 - *track_depth_residual);
         }
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }  
   }
}
