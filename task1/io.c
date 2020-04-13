#include "io.h"

void recover_from_file(char ** track_data, int * track_length, int * track_depth, int * track_depth_residual, int * track_depth_type, int * track_freq,
                            char * file_name, char * file_param_name, FILE *stream, FILE *stream_par, int * track_memory_allocated)
{
   stream_par = fopen(file_param_name, "r");
   if(stream_par == NULL)
   {
       printf("There is no parameter file. Apparently, it wasn't saved previous time.\n");
   }
   else
   {
        fscanf(stream_par, "%i\n", track_length);
        fscanf(stream_par, "%i\n", track_depth);
        fscanf(stream_par, "%i\n", track_depth_residual);
        fscanf(stream_par, "%i\n", track_depth_type);
        fscanf(stream_par, "%i\n", track_freq);
        fclose(stream_par);
        if(*track_memory_allocated)
         {
            free(*track_data);
         }
         *track_data = (char *) malloc((*track_depth/8) * *track_length * *track_freq); // track_depth is a multiple of 8 by the design  
         *track_memory_allocated = 1; 
   }
   
   stream = fopen(file_name, "r");
   if(stream == NULL)
   {
       printf("There is no data file. Apparently, it wasn't saved previous time.\n");
   }
   else
   {
       int r, i = 0;
       if(*track_depth_type)
       {
           float sample = 0;
           r = fscanf(stream, "%f\n", &sample);
           while(r != EOF)
           {
               memcpy(*track_data + i * *track_depth / 8, &sample, *track_depth / 8);
               i++;
               r = fscanf(stream, "%f\n", &sample);
           }
       }
       else
       {
           int sample = 10;
           r = fscanf(stream, "%i\n", &sample);
           printf("sample = %i\n", sample);
           printf("r = %i", r);
           while(r != EOF)
           {
               memcpy(*track_data + i * *track_depth / 8, &sample, *track_depth / 8);
               i++;
               r = fscanf(stream, "%i\n", &sample);
           }
       }
       fclose(stream);
   }
    
}

void write_params_to_file(int * track_length, int * track_depth, int * track_depth_residual, int * track_depth_type, int * track_freq,
                                                                    char * file_param_name, FILE *stream_par)
{
    stream_par = fopen(file_param_name, "w");
    fprintf(stream_par, "%i\n", *track_length);
    fprintf(stream_par, "%i\n", *track_depth);
    fprintf(stream_par, "%i\n", *track_depth_residual);
    fprintf(stream_par, "%i\n", *track_depth_type);
    fprintf(stream_par, "%i\n", *track_freq);
    fclose(stream_par);
}

void write_to_file(FILE* stream, char file_name[], char * track_data, int track_specific_length, int * track_depth, int * track_depth_type)
{
    int track_byte_depth = *track_depth / 8; // depth in bytes 
   stream = fopen(file_name, "w");
   if (*track_depth_type)
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         float sample = 0;
         memcpy(&sample, track_data + i * track_byte_depth, track_byte_depth);
         fprintf(stream, "%f\n", sample);
      }      
   }
   else
   {
      for(int i = 0; i < track_specific_length; i++)
      {
         int sample = 0;
         memcpy(&sample, track_data + i * track_byte_depth, track_byte_depth);
         if(sample & (1 << (*track_depth - 1))) // if it was originally negative
         {
             sample = -1; // not efficient but clear way to make sure it will be negative in Two's complement notation
             memcpy(&sample, track_data + i * track_byte_depth, track_byte_depth);
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