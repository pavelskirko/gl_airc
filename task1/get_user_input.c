#include "get_user_input.h"

void ask_user(char * question, int * answer)
{
   char c = '0';
   while(1)
    {
      printf("%s", question);
      if (scanf("%d", answer) == 1) break;
      else 
      {
         printf("Input is incorrect, try again\n");
         do {
         c = getchar();
      }
      while (!isdigit(c));
      ungetc(c, stdin);
      }
      }
}

void get_user_input(int * track_length, int * track_depth, int * track_depth_type, int * track_freq, int * intrvl_type, int * intrvl_start, int * intrvl_length, 
                     int * ampl, int * freq, int * phase, int * user_choise, int * user_choise_2nd, char * file_name)
{
   *user_choise = 0;
   *user_choise_2nd = 0;
   char c = '0';
   ask_user("Please choose what would you like to do: \n"
    "1) Read track from .csv file \n"
    "2) Create new track \n"
    "3) Add signal to the track \n"
    "4) Write track to the file\n"
    "5) Print track to the console\n"
    "6) Close\n", user_choise);
    switch (*user_choise)
    {
    case 1:
       printf("Reading file... \n");
       break;
    case 2:
      ask_user("Please enter the length of a track in seconds: \n", track_length);
      ask_user("Please choose a desired depth (1-6): \n"
                  "\t1) 8 bit \n"
                  "\t2) 16 bit \n"
                  "\t3) 24 bit \n"
                  "\t4) 32 bit \n"
                  "\t5) 32 bit float\n"
                  "\t6) custom integer depth (1-32) \n", user_choise_2nd);
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
         ask_user("\tPlease enter a custom depth (integer number): ", track_depth);
         break;
      default:
         printf("Wrong input, try again. \n");
         break;
      }
      *user_choise_2nd = 0;
      ask_user("Please choose a desired discretization freq (1-4): \n"
                  "\t1) 44.1 kHz \n"
                  "\t2) 44 kHz \n"
                  "\t3) 96 kHz \n"
                  "\t4) Custom freq\n", user_choise_2nd);
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
         ask_user("\tPlease enter a desired freq (integer, Hz): ", track_freq);
         break;
      
      default:
         printf("Wrong input. Try again. \n");
         break;
      }
      break;
    case 3:
      ask_user("What type of signal would you like to create? (1-2)\n"
                  "\t1) sine\n"
                  "\t2) triangle\n", intrvl_type);
      ask_user("Please enter the start time (in seconds) ", intrvl_start);
      ask_user("Please enter the length (in seconds) ", intrvl_length);
      ask_user("Please enter the amplitude (integer) ", ampl);
      ask_user("Please enter the freq (integer) ", freq);
      ask_user("Please enter the phase (integer) ", phase);
      break;
    case 4:
      printf("Writing to the file... \n");
      break;
    case 5:
      
      break;
    case 6:

      break;
    default:
       printf("Wrong input, try again. \n");
       break;
    }   
}
