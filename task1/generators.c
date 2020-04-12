#include "generators.h"

void sine_generator(char * track_data_start, int * track_depth, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl)
{
   // specific_freq = interval_freq/track_freq
   // specific_phase = interval_phase / track_freq
   // specific_length = lendth(seconds) * track_freq
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
         if (sample > pow(2,*track_depth - 1)) // 2 ^ (*track_depth - 1) is max value of signed (*track_depth)-bit number  
         {
            sample = pow(2,*track_depth - 1) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1))
         {
             sample = -pow(2,*track_depth - 1);
         }
         
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }  
   }
}

void triangle_generator(char * track_data_start, int * track_depth, int * track_depth_type, 
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
         if (sample > pow(2,*track_depth - 1)) // 2 ^ (*track_depth - 1) is max value of signed (*track_depth)-bit number  
         {
            sample = pow(2,*track_depth - 1) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1))
         {
             sample = -pow(2,*track_depth - 1);
         }
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }  
   }
}
