#include "db_handling.h"

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

void db_save_to_file(json_object ** jobj, char * file_name, char * status)
{
    int errnum;
    FILE * stream = fopen(file_name, "w");
    if (stream == NULL)
    {
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      strcpy(status, strerror(errnum));
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
    else 
    {
    fprintf(stream, "%s", json_object_to_json_string(*jobj));
    fclose(stream);
    }
}

void db_read_from_file(json_object ** jobj, char * file_name, char * status)
{
    int errnum;
    FILE * stream = fopen(file_name, "r");
    if (stream == NULL)
    {
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      strcpy(status, strerror(errnum));
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

void get_row_by_number(json_object * j_db, char * buff, int row_num, char * status)
{
    json_object *j_row = json_object_new_object();
    json_object *j_msg_ans = json_object_new_object();

    json_object *jarray1;
    json_object *jarray2;
    json_object *jarray3;

    json_object *jrocket;
    json_object *jflights;
    json_object *jsucc;

    json_object *jstatus;

    json_object_object_get_ex(j_db, "Name of a rocket", &jarray1);
	json_object_object_get_ex(j_db, "Number of flights", &jarray2);
	json_object_object_get_ex(j_db, "Success rate", &jarray3);

    int n_rows1 = json_object_array_length(jarray1);
    int n_rows2 = json_object_array_length(jarray2);
    int n_rows3 = json_object_array_length(jarray3);

    if(n_rows1 != n_rows2 || n_rows2 != n_rows3) strcpy(status, "db corrupted");
    else{
        if(n_rows1 == 0) strcpy(status, "db_empty");
        else if (n_rows1 < row_num) strcpy(status, "no such row");
        else
        {
            jrocket = json_object_array_get_idx(jarray1, row_num); // last element
            jflights = json_object_array_get_idx(jarray2, row_num);
            jsucc = json_object_array_get_idx(jarray3, row_num);

            json_object_object_add(j_row, "Name of a rocket", jrocket);
            json_object_object_add(j_row, "Number of flights", jflights);
            json_object_object_add(j_row, "Success rate", jsucc);
        }
    } 
    jstatus = json_object_new_string(status);
    json_object_object_add(j_msg_ans, "Status", jstatus);
    json_object_object_add(j_msg_ans, "Row", j_row);
    
    strcpy(buff, json_object_to_json_string(j_msg_ans));
}