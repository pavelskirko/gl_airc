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

void show_the_whole_table(char * msg, int msg_length)
{
    json_object *jmsg = json_object_new_object();
    json_object *jcommand = json_object_new_string("show");
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

    printf("Please enter the name of a rocket you are looking for ");
    while ((user_input[n++] = getchar()) != '\n'); 
    user_input[n-1] = 0;
    json_object *jrocket = json_object_new_string(user_input);
    bzero(user_input, MAX);
    n = 0;

    json_object *jrow = json_object_new_object();
    json_object_object_add(jmsg, "Name of a rocket", jrocket);

    strcpy(msg, json_object_to_json_string(jmsg) );
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
        "\t4) Search\n");
        while ((user_input[n++] = getchar()) != '\n'); 
        *user_ans = atoi(user_input);
        if( *user_ans < 1 || *user_ans > 4 ) continue;
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
            break;
        case 3:
            show_the_whole_table(buff, MAX);
            write(sockfd, buff, MAX); 
            break;
        case 4:
            search(buff, MAX);
            write(sockfd, buff, MAX); 
            break;

        default:
            break;
        }

        // write(sockfd, buff, sizeof(buff)); 
        // bzero(buff, sizeof(buff)); 
        // read(sockfd, buff, sizeof(buff)); 
        // printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
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
  
    // close the socket 
    close(sockfd); 
}