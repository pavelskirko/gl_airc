#include "db_server.h"

#define DB_FILE_NAME        "db.json"
#define DB_FILE_NAME_REC    "dbrec.json"

extern int errno ;

void db_init(json_object ** jobj)
{
    *jobj = json_object_new_object();
    json_object *jarray1 = json_object_new_array();
    json_object *jarray2 = json_object_new_array();
    json_object *jarray3 = json_object_new_array();

    json_object_object_add(*jobj,"Name of a rocket", jarray1);
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

void db_read_from_file(json_object ** jobj, char * file_name)
{
    int errnum;
    FILE * stream = fopen(file_name, "r");
    if (stream == NULL)
    {
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
    else 
    {
    char buffer[1024];
    // memset(buffer, 0, 1024);
    fread(buffer, 1024, 1, stream);
	fclose(stream);
    *jobj = json_tokener_parse(buffer);
    }
}



void db_add_row(json_object ** jobj, json_object * new_jobj)
{
    json_object *jarray1;
    json_object *jarray2;
    json_object *jarray3;

    json_object *jstring;
    json_object *jint;
    json_object *jdouble;

    json_object_object_get_ex(*jobj, "Name of a rocket", &jarray1);
	json_object_object_get_ex(*jobj, "Number of flights", &jarray2);
	json_object_object_get_ex(*jobj, "Success rate", &jarray3);

    json_object_object_get_ex(new_jobj, "Name of a rocket", &jstring);
	json_object_object_get_ex(new_jobj, "Number of flights", &jint);
	json_object_object_get_ex(new_jobj, "Success rate", &jdouble);

    json_object_array_add(jarray1,jstring);
    json_object_array_add(jarray2,jint);
    json_object_array_add(jarray3,jdouble);

}

void db_remove_row(json_object ** jobj, char * status)
{
    json_object *jarray1;
    json_object *jarray2;
    json_object *jarray3;

    json_object *jstring;
    json_object *jint;
    json_object *jdouble;

    json_object_object_get_ex(*jobj, "Name of a rocket", &jarray1);
	json_object_object_get_ex(*jobj, "Number of flights", &jarray2);
	json_object_object_get_ex(*jobj, "Success rate", &jarray3);

    int n_rows1 = json_object_array_length(jarray1);
    int n_rows2 = json_object_array_length(jarray2);
    int n_rows3 = json_object_array_length(jarray3);

    if(n_rows1 != n_rows2 || n_rows2 != n_rows3) strcpy(status, "db corrupted");
    else{
        if(n_rows1 == 0) strcpy(status, "db_empty");
        else
        {
            n_rows1 -= 1;
            jstring = json_object_array_get_idx(jarray1, n_rows1); // last element
            jint = json_object_array_get_idx(jarray2, n_rows1);
            jdouble = json_object_array_get_idx(jarray3, n_rows1);
            json_object_array_del_idx(jarray1, n_rows1, 1);
            json_object_array_del_idx(jarray2, n_rows1, 1);
            json_object_array_del_idx(jarray3, n_rows1, 1);
        }
    }
    
    
}

int main()
{
    json_object * jobj;
    json_object * jobj_rec;
    char * status = malloc(100);
    strcpy(status, "ok");
    db_init(&jobj);
    db_save_to_file(&jobj);
    db_read_from_file(&jobj, DB_FILE_NAME);
    db_read_from_file(&jobj_rec, DB_FILE_NAME_REC);
    db_add_row(&jobj, jobj_rec);
    db_remove_row(&jobj, status);
    printf("status: %s\n", status);
    printf ("The json object created: %s\n",json_object_to_json_string(jobj));
}