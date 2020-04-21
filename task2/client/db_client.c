#include "db_client.h"

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

void talk_with_server(int sockfd) 
{ 
    char buff[MAX]; 
    int n, user_ans = 0; 
    json_object * jobj;
    while(1)
    { 
        bzero(buff, sizeof(buff)); 
        get_user_input(&user_ans);
        switch (user_ans)
        {
        case 1:
            send_row(buff, MAX);
            write(sockfd, buff, MAX); 
            break;
        case 2:
            remove_row(buff, MAX);
            write(sockfd, buff, MAX); 
            bzero(buff, MAX);
            read(sockfd, buff, sizeof(buff));
            print_a_status(buff, MAX);
            break;
        case 3:
            ask_for_a_table(buff, MAX);
            write(sockfd, buff, MAX); 
            bzero(buff, MAX);
            read(sockfd, buff, sizeof(buff));
            print_a_table(buff, MAX);
            break;
        case 4:
            search(buff, MAX);
            write(sockfd, buff, MAX);
            bzero(buff, MAX);
            read(sockfd, buff, sizeof(buff));
            print_a_row(buff, MAX);
            break;
        case 5:
            exit_command(buff, MAX);
            write(sockfd, buff, MAX);
            break;
        default:
            break;
        
        } 
    if (user_ans == 5) break;
    } 
} 

int main()
{
    printf("Client here.\n");
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    talk_with_server(sockfd); 
    printf("Communication ended. Have a nice day!\n");
    // close the socket 
    close(sockfd); 
}