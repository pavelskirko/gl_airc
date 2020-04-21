#include "db_messages.h"

void send_row(char * msg, int msg_length)
{
    int n = 0; 
    char user_input[MAX];
    char *end_pointer;
    bzero(user_input, MAX);

    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("add");
    json_object_object_add(jmsg,"Command", jcommand);

    printf("Please enter the name of a rocket: ");
    while ((user_input[n++] = getchar()) != '\n'); 
    user_input[n-1] = 0;
    json_object *jrocket = json_object_new_string(user_input);
    bzero(user_input, MAX);
    n = 0;

    printf("Please enter number of flights (ineger > 0): ");
    while ((user_input[n++] = getchar()) != '\n'); 
    json_object *jflights = json_object_new_int(atoi(user_input));
    bzero(user_input, MAX);
    n = 0;

    printf("Please enter success rate (float number (0-1) ): ");
    while ((user_input[n++] = getchar()) != '\n'); 
    json_object *jsucc = json_object_new_double( strtod(user_input, &end_pointer) );
    bzero(user_input, MAX);

    json_object *jrow = json_object_new_object();
    json_object_object_add(jrow, "Name of a rocket", jrocket);
    json_object_object_add(jrow, "Number of flights", jflights);
    json_object_object_add(jrow, "Success rate", jsucc);
    json_object_object_add(jmsg, "Row", jrow);

    strcpy(msg, json_object_to_json_string(jmsg) );
}

void remove_row(char * msg, int msg_length)
{
    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("remove");
    json_object_object_add(jmsg,"Command", jcommand);

    strcpy(msg, json_object_to_json_string(jmsg) );
}

void ask_for_a_table(char * msg, int msg_length)
{
    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("show");
    json_object_object_add(jmsg,"Command", jcommand);

    strcpy(msg, json_object_to_json_string(jmsg) );
}

void exit_command(char * msg, int msg_length)
{
    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("exit");
    json_object_object_add(jmsg,"Command", jcommand);

    strcpy(msg, json_object_to_json_string(jmsg) );
}

void search(char * msg, int msg_length)
{
    int n = 0; 
    char user_input[MAX];
    char *end_pointer;
    bzero(user_input, MAX);

    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("search");
    json_object_object_add(jmsg,"Command", jcommand);

    printf("Please enter the name of a rocket you are looking for: ");
    while ((user_input[n++] = getchar()) != '\n'); 
    user_input[n-1] = 0;
    json_object *jrocket = json_object_new_string(user_input);
    bzero(user_input, MAX);
    n = 0;

    json_object *jrow = json_object_new_object();
    json_object_object_add(jmsg, "Name of a rocket", jrocket);

    strcpy(msg, json_object_to_json_string(jmsg) );
}