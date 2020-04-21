#include "print_to_console.h"

void ask_user(char * question, int * answer)
{
   char c = '0';
   while(1)
    {
      printf("%s", question);
      if (scanf("%d", answer) == 1) break;
      else 
      {
        printf("Input should be integer, try again\n");
        do {
            c = getchar();
        }
        while (!isdigit(c));
        ungetc(c, stdin);
        }
      }
}



void print_a_status(char * msg, int msg_length)
{
    json_object *jmsg = json_tokener_parse(msg);
    
    json_object *jstatus;

    json_object_object_get_ex(jmsg, "Status", &jstatus);
    printf("Status: %s\n", json_object_get_string(jstatus) );
}


void print_a_table(char * msg, int msg_length)
{
    json_object *jmsg = json_tokener_parse(msg);
    json_object *jtable;
    json_object *jarray1;
    json_object *jarray2;
    json_object *jarray3;

    json_object *jrocket;
    json_object *jflights;
    json_object *jsucc;

    json_object *jstatus;

    json_object_object_get_ex(jmsg, "Status", &jstatus);
    json_object_object_get_ex(jmsg, "Table", &jtable);
    json_object_object_get_ex(jtable, "Name of a rocket", &jarray1);
    json_object_object_get_ex(jtable, "Number of flights", &jarray2);
    json_object_object_get_ex(jtable, "Success rate", &jarray3);
    int n_rows1 = json_object_array_length(jarray1);
    int n_rows2 = json_object_array_length(jarray2);
    int n_rows3 = json_object_array_length(jarray3);
    if(n_rows1 != n_rows2 || n_rows2 != n_rows3) printf("db is corrupted");
    else
    {   
        printf("#\tName of a rocket\tNumber of flights\tSuccess rate\n");
        for(int i = 0; i < n_rows1; i++)
        {
            jrocket = json_object_array_get_idx(jarray1, i); // last element
            jflights = json_object_array_get_idx(jarray2, i);
            jsucc = json_object_array_get_idx(jarray3, i);
            printf("%i\t\t%s\t%i\t\t\t%.2f\n", i, json_object_get_string(jrocket),
                            json_object_get_int(jflights), json_object_get_double(jsucc));
        }
        printf("Status: %s\n", json_object_get_string(jstatus) );
    }
}

void print_a_row(char * msg, int msg_length)
{
    json_object *jmsg = json_tokener_parse(msg);
    json_object *jrow;

    json_object *jrocket;
    json_object *jflights;
    json_object *jsucc;

    json_object *jstatus;

    json_object_object_get_ex(jmsg, "Status", &jstatus);
    if( strcmp(json_object_get_string(jstatus), "ok") ) printf("Status: %s\n", json_object_get_string(jstatus));
    else
    {    
        json_object_object_get_ex(jmsg, "Row", &jrow);
        json_object_object_get_ex(jrow, "Name of a rocket", &jrocket);
        json_object_object_get_ex(jrow, "Number of flights", &jflights);
        json_object_object_get_ex(jrow, "Success rate", &jsucc);
       
        printf("Name of a rocket\tNumber of flights\tSuccess rate\n");
        printf("%s\t\t%i\t\t\t%.2f\n", json_object_get_string(jrocket),
                            json_object_get_int(jflights), json_object_get_double(jsucc));
        printf("Status: %s\n", json_object_get_string(jstatus) );
    }
}

void get_user_input(int * user_ans)
{
    int n = 0;
    char user_input[MAX];
    while(1)
    {
        printf("What would you like to do?\n"
        "\t1) Add row\n"
        "\t2) Remove last row\n"
        "\t3) Show the whole table\n"
        "\t4) Search\n"
        "\t5) Exit\n");
        while ((user_input[n++] = getchar()) != '\n'); 
        *user_ans = atoi(user_input);
        bzero(user_input, MAX);
        if( *user_ans < 1 || *user_ans > 5 ) continue;
        else break;
    }
}
