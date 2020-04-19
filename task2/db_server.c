#include "db_server.h"

#define DB_FILE_NAME    "db.json"
void db_init(json_object ** jobj)
{
    *jobj = json_object_new_object();
    json_object *jarray1 = json_object_new_array();
    json_object *jarray2 = json_object_new_array();
    json_object *jarray3 = json_object_new_array();

    json_object_object_add(*jobj,"Name of rocket", jarray1);
    json_object_object_add(*jobj,"Number of flights", jarray2);
    json_object_object_add(*jobj,"Success rate", jarray3);

    //put some data

    json_object *jstring1 = json_object_new_string("Falcon 9");
    json_object *jint1 = json_object_new_int(83);
    json_object *jdouble1 = json_object_new_double(0.98);
    json_object *jstring2 = json_object_new_string("Falcon Heavy");
    json_object *jint2 = json_object_new_int(3);
    json_object *jdouble2 = json_object_new_double(1);
    json_object *jstring3 = json_object_new_string("Electron");
    json_object *jint3 = json_object_new_int(9);
    json_object *jdouble3 = json_object_new_double(0.89);

    json_object_array_add(jarray1,jstring1);
    json_object_array_add(jarray1,jstring2);
    json_object_array_add(jarray1,jstring3);

    json_object_array_add(jarray2,jint1);
    json_object_array_add(jarray2,jint2);
    json_object_array_add(jarray2,jint3);

    json_object_array_add(jarray3,jdouble1);
    json_object_array_add(jarray3,jdouble2);
    json_object_array_add(jarray3,jdouble3);

}

void db_save_to_file(json_object ** jobj)
{
    FILE * stream = fopen(DB_FILE_NAME, "w");
    fprintf(stream, "%s", json_object_to_json_string(*jobj));
    fclose(stream);
}

void db_read_from_file(json_object ** jobj)
{
    FILE * stream = fopen(DB_FILE_NAME, "r");
    char buffer[1024];
    fread(buffer, 1024, 1, stream);
	fclose(stream);
    *jobj = json_tokener_parse(buffer);
}
int main()
{
    json_object * jobj;

    db_init(&jobj);
    db_save_to_file(&jobj);
    db_read_from_file(&jobj);
    printf ("The json object created: %s\n",json_object_to_json_string(jobj));
    
    // printf("here we go\n");
}