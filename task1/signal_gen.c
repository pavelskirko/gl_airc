#include "signal_gen.h"

//TODO implement custom depth

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
         float sample = *ampl * sin(specific_phase + specific_freq * i);
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }
      else
      {
         int sample = (int)( *ampl * sin(specific_phase + specific_freq*i));
         if (sample > pow(2,*track_depth - 1)) // 2 ^ (*track_depth - 1) is max value of signed (*track_depth)-bit number  
         {
            sample = pow(2,*track_depth - 1);
         }
         memcpy(track_data_start, &sample, *track_depth / 8); // *track_depth / 8 is a number of bytes in (*track_depth)-bit number
         track_data_start += *track_depth / 8;
      }  
   }
}

void print_track(char * track_data_start, int track_specific_length, int * track_depth, int * track_depth_type)
{
   // track_specific_length is a number of samples in the track
   if (*track_depth_type)
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         float sample = 0;
         memcpy(&sample, track_data_start, *track_depth / 8);
         track_data_start += *track_depth / 8;
         printf("%f ", sample);
      }      
   }
   else
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         int sample = 0;
         memcpy(&sample, track_data_start + i * *track_depth / 8, *track_depth / 8);
         printf("%d ", sample);
      }
   }   
}

int main() {
   int track_length;
   int track_depth;
   int track_depth_type = 0; // 1 if float
   int track_freq;
   int intrvl_type; // 1 -- sine; 2 -- triangle
   int intrvl_start;
   int intrvl_length;
   int ampl;
   int freq;
   int phase;
   int user_choise;
   int user_choise_2nd;
   char * file_name;

   char * track_data;
   printf("The following program is generating a set of user defined signals on a given time interval. \n");
   while(1)
   {
      get_user_input(&track_length, &track_depth, &track_depth_type, &track_freq, &intrvl_type, &intrvl_start,
                         &intrvl_length, &ampl, &freq, &phase, &user_choise, &user_choise_2nd, file_name);
      // user_choise:
      //    1) Read track from .csv file 
      //    2) Create new track 
      //    3) Add signal to the track 

      switch (user_choise)
      {
      case 1:
         /* code */
         break;
      case 2:
         // if (!track_depth_type) 
         // {
         track_data = (char *) malloc((track_depth/8) * track_length * track_freq); // track_depth is a multiple of 8 by the design       
         // }   
         // else
         // {
         //    track_data = (float *) malloc(sizeof(float) * track_length * track_freq);
         // }
         break;
      case 3:
         if (track_length - intrvl_start - intrvl_length >= 0)
         {
            if (intrvl_type == 1)
            {
               sine_generator(track_data + (track_depth/8) * intrvl_start * track_freq, 
                              &track_depth, &track_depth_type, (double)freq/track_freq, phase, intrvl_length * track_freq, &ampl);
               print_track(track_data, track_length*track_freq, &track_depth, &track_depth_type);
            }
         }
         else
         {
            printf("Interval doesn't fit into track.");
         }
         
         
         break;
      
      default:
         break;
      }
   }
   
   return 0;
}