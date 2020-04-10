#include "signal_gen.h"

void get_user_input(int * track_length, int * track_depth, int * track_depth_type, int * track_freq, int * intrvl_start, int * intrvl_length, 
                     int * ampl, int * freq, int * phase, int * user_choise, int * user_choise_2nd, char * file_name)
{
   *user_choise = 0;
   *user_choise_2nd = 0;
   printf("Please choose what would you like to do: \n"
    "1) Read track from .csv file \n"
    "2) Create new track \n"
    "3) Add signal to the track \n");
    scanf("%d", user_choise);
    switch (*user_choise)
    {
    case 1:
       /* code */
       break;
    case 2:
      printf("Please enter the length of a track in seconds: \n");
      scanf("%d", track_length);
      printf("Please choose a desired depth (1-6): \n");
      printf("\t1) 8 bit \n");
      printf("\t2) 16 bit \n");
      printf("\t3) 24 bit \n");
      printf("\t4) 32 bit \n");
      printf("\t5) 32 bit float\n");
      printf("\t6) custom input \n");
      scanf("%d", user_choise_2nd);
      switch (*user_choise_2nd)
      {
      case 1:
         *track_depth = 8;
         break;
      case 2:
         *track_depth = 16;
         break;
      case 3:
         *track_depth = 24;
         break;
      case 4:
         *track_depth = 32;
         break;
      case 5:
         *track_depth = 32;
         *track_depth_type = 1;
         break;
      case 6:
         printf("\tPlease enter a custom depth(integer number): ");
         scanf("%d", track_depth);
         break;
      default:
         printf("Wrong input, try again. \n");
         break;
      }
      *user_choise_2nd = 0;
      scanf("%d", track_depth);
      printf("Please choose a desired freq (1-4): \n"
      "\t1) 44.1 kHz \n"
      "\t2) 44 kHz \n"
      "\t3) 96 kHz \n"
      "\t4) Custom \n");
      scanf("%d", user_choise_2nd);
      switch (*user_choise_2nd)
      {
      case 1:
         *track_freq = 44100;
         break;
      case 2:
         *track_freq = 44000;
         break;
      case 3:
         *track_freq = 96000;
         break;
      case 4:
         printf("\tPlease enter a desired freq (integer, Hz): ");
         scanf("%d", track_freq);
      
      default:
         printf("Wrong input. Try again. \n");
         break;
      }
      break;
    case 3:
      printf("Please enter the start time (in seconds) ");
      scanf("%d", intrvl_start);
      printf("Please enter the length (in seconds) ");
      scanf("%d", intrvl_length);
      printf("Please enter the amplitude ");
      scanf("%d", ampl);
      printf("Please enter the freq ");
      scanf("%d", freq);
      printf("Please enter the phase ");
      scanf("%d", phase);
      break;
    default:
       printf("Wrong input, try again. \n");
       break;
    }   
}

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
      get_user_input(&track_length, &track_depth, &track_depth_type, &track_freq, &intrvl_start, &intrvl_length, 
                     &ampl, &freq, &phase, &user_choise, &user_choise_2nd, file_name);
   }
   
   return 0;
}