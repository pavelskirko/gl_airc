#ifndef DB_MESSAGES
#define DB_MESSAGES

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

void send_row(char * msg, int msg_length);
void remove_row(char * msg, int msg_length);
void ask_for_a_table(char * msg, int msg_length);
void exit_command(char * msg, int msg_length);
void search(char * msg, int msg_length);


#endif