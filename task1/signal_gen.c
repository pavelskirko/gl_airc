#include "signal_gen.h"

//TODO switch to sending values to functions instead of pointers where it is suitable

int main() {
   int track_length = 0;
   int track_depth = 0;
   int track_depth_residual = 0;
   int track_depth_type = 0; // 1 if float 32
   int track_freq = 0;
   int intrvl_type = 0; // 1 -- sine; 2 -- triangle
   int intrvl_start = 0;
   int intrvl_length = 0;
   int ampl = 0;
   int freq = 0;
   int phase = 0;
   int user_choise = 0;
   int user_choise_2nd = 0;
   char file_name[] = "generated_signal.csv";
   char file_param_name[] = "track_parameters.txt";
   FILE *stream = NULL;
   FILE *stream_par = NULL;
   char * track_data;
   int track_memory_allocated = 0;
   printf("The following program is generating a set of user defined signals on a given time interval. \n");
   while(1)
   {
      get_user_input(&track_length, &track_depth, &track_depth_type, &track_freq, &intrvl_type, &intrvl_start,
                         &intrvl_length, &ampl, &freq, &phase, &user_choise, &user_choise_2nd, file_name);
      // user_choise:
      //    1) Read track from .csv file 
      //    2) Create new track 
      //    3) Add signal to the track 
      //    4) Write track to the file
      //    5) Print track to the console
      //    6) Close
      
      switch (user_choise)
      {
      case 1:
         recover_from_file(&track_data, &track_length, &track_depth, &track_depth_residual, &track_depth_type, &track_freq, file_name, file_param_name, 
                                       stream, stream_par, &track_memory_allocated);
         printf("Done.\n");
         break;
      case 2:
         track_depth_check(&track_depth, &track_depth_residual);
         if(track_memory_allocated)
         {
            free(track_data);
         }
         track_data = (char *) malloc((track_depth/8) * track_length * track_freq); // track_depth is a multiple of 8 by the design  
         track_memory_allocated = 1;     
         break;
      case 3:
         if (track_length - intrvl_start - intrvl_length >= 0)
         {
            if (intrvl_type == 1)
            {
               sine_generator(track_data + (track_depth/8) * intrvl_start * track_freq, 
                              &track_depth, &track_depth_residual, &track_depth_type, (double)freq/track_freq, phase, intrvl_length * track_freq, &ampl);
            }
            else if (intrvl_type == 2)
            {
               triangle_generator(track_data + (track_depth/8) * intrvl_start * track_freq, 
                              &track_depth, &track_depth_residual, &track_depth_type, (double)freq/track_freq, phase, intrvl_length * track_freq, &ampl);
            }
         }
         else
         {
            printf("Interval doesn't fit into track.");
         }
         break;

      case 4:
       write_params_to_file(&track_length, &track_depth, &track_depth_residual, &track_depth_type, &track_freq, file_param_name, stream_par);
       printf("Parameters of the track saved to track_parameters.txt\n");
       write_to_file(stream,file_name, track_data, track_length*track_freq, &track_depth, &track_depth_type);
       printf("Data saved in generated_signal.csv\n");
       
       break;

      case 5:
       print_track(track_data, track_length*track_freq, &track_depth, &track_depth_type);
       printf("\n");
       break;
      case 6:
       if(track_memory_allocated)
       {
          free(track_data);
       }
       break;
      default:
         break;
      }
      if(user_choise == 6)
      {
         break;
      }
   }
   
   return 0;
}