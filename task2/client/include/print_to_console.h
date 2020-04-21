#ifndef DB_PRINT_TO_CONSOLE
#define DB_PRINT_TO_CONSOLE

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <json-c/json.h>
#include <netdb.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX 1024 

#define DB_FILE_NAME        "db.json"
#define DB_FILE_NAME_REC    "dbrec.json"

void ask_user(char * question, int * answer);
void print_a_status(char * msg, int msg_length);
void print_a_table(char * msg, int msg_length);
void print_a_row(char * msg, int msg_length);
void get_user_input(int * user_ans);


#endif