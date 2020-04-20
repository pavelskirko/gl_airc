#ifndef DB_HANDLING
#define DB_HANDLING

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <json-c/json.h>

void db_init(json_object ** jobj);
void db_save_to_file(json_object ** jobj,char * file_name, char * status);
void db_read_from_file(json_object ** jobj, char * file_name, char * status);
void db_add_row(json_object ** jobj, json_object * new_jobj);
void db_remove_row(json_object ** jobj, char * status);


#endif