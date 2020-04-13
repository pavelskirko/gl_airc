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

   int track_byte_depth = *track_depth / 8; // track_byte_depth is a number of bytes needed to store
                                                               //  (*track_depth- *track_depth_residual)-bit number
   for (int i = 0; i < specific_length; i++)
   {
      if (*track_depth_type)
      {
         float sample = *ampl * sin(specific_phase + 6.28 * specific_freq * i);
         float sample_prev = 0;
         memcpy(&sample_prev, track_data_start, track_byte_depth);
         sample += sample_prev;
         memcpy(track_data_start, &sample, track_byte_depth); 
         track_data_start += track_byte_depth;
      }
      else
      {
         int sample = (int)( *ampl * (sin(specific_phase + 6.28 * specific_freq*i)));
         int sample_prev = 0;
         memcpy(&sample_prev, track_data_start, track_byte_depth);
         if(sample_prev & (1 << (*track_depth - 1))) // if it was originally negative
         {
             sample_prev = -1; // not an efficient but a clear way to make sure it will be negative in the Two's complement notation
             memcpy(&sample_prev, track_data_start, track_byte_depth);
         }
         sample += sample_prev;
         if (sample > pow(2,*track_depth - 1 - *track_depth_residual)) // 2 ^ (*track_depth - 1 - *track_depth_residual) is 
                                                         // a max value of a signed (*track_depth - *track_depth_residual)-bit number  
         {
            sample = pow(2,*track_depth - 1 - *track_depth_residual) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1 - *track_depth_residual))
         {
             sample = -pow(2,*track_depth - 1 - *track_depth_residual);
         }
         
         memcpy(track_data_start, &sample, track_byte_depth); 
         track_data_start += track_byte_depth;
      }  
   }
}

void triangle_generator(char * track_data_start, int * track_depth, int * track_depth_residual, int * track_depth_type, 
                     float specific_freq, float specific_phase, int specific_length, int * ampl)
{
   int track_byte_depth = *track_depth / 8; // track_byte_depth is a number of bytes needed to store
                                                               //  (*track_depth- *track_depth_residual)-bit number
   for (int i = 0; i < specific_length; i++)
   {
      if (*track_depth_type)
      {
         float sample = (double)*ampl * asin(sin(specific_phase + 6.28 * specific_freq * i)) * (2 / 3.14);
         float sample_prev = 0;
         memcpy(&sample_prev, track_data_start, track_byte_depth);
         sample += sample_prev;
         memcpy(track_data_start, &sample, track_byte_depth); 
         track_data_start += track_byte_depth;
      }
      else
      {
         int sample = (int) ((double)*ampl * asin(sin(specific_phase + 6.28 * specific_freq * i)) * (2 / 3.14) );
         int sample_prev = 0;
         memcpy(&sample_prev, track_data_start, track_byte_depth);
         if(sample_prev & (1 << (*track_depth - 1))) // if it was originally negative
         {
             sample_prev = -1; // not an efficient but a clear way to make sure it will be negative in the Two's complement notation
             memcpy(&sample_prev, track_data_start, track_byte_depth);
         }
         sample += sample_prev;
         if (sample > pow(2,*track_depth - 1 - *track_depth_residual)) // 2 ^ (*track_depth - 1 - *track_depth_residual) is 
                                                         // a max value of a signed (*track_depth - *track_depth_residual)-bit number 
         {
            sample = pow(2,*track_depth - 1 - *track_depth_residual) - 1;
         }
         else if (sample < -pow(2,*track_depth - 1 - *track_depth_residual))
         {
             sample = -pow(2,*track_depth - 1 - *track_depth_residual);
         }
         memcpy(track_data_start, &sample, track_byte_depth); 
         track_data_start += track_byte_depth;
      }  
   }
}
