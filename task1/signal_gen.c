#include "signal_gen.h"

int main() {
   int track_length;
   int track_depth;
   int track_depth_type = 0; // 1 if float
   int track_freq;
   int intrvl_start;
   int intrvl_length;
   int ampl;
   int freq;
   int phase;
   int user_choise;
   int user_choise_2nd;
   char * file_name;
   printf("The following program is generating a set of user defined signals on a given time interval. \n");
   while(1)
   {
      get_user_input(&track_length, &track_depth, &track_depth_type, &track_freq, &intrvl_start, &intrvl_length, &ampl, &freq, &phase, &user_choise, &user_choise_2nd, file_name);
   }
   
   return 0;
}