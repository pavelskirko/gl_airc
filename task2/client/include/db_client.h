#ifndef DB_CLIENT
#define DB_CLIENT

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
#define PORT 8080 
#define SA struct sockaddr 

#define DB_FILE_NAME        "db.json"
#define DB_FILE_NAME_REC    "dbrec.json"

#endif