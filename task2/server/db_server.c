#include "db_server.h"


#define MAX 1024 
#define PORT 8080 
#define SA struct sockaddr

extern int errno ;

void talk_with_client(int sockfd , json_object ** j_db, char * status)
{
    char buff[MAX]; 
    json_object * jmsg;
    json_object *jcommand;
    int n; 
        while(1)
        { 
        bzero(buff, MAX); 
        read(sockfd, buff, sizeof(buff)); 
        jmsg = json_tokener_parse(buff);
        printf("%s", buff);
        json_object_object_get_ex(jmsg, "Command", &jcommand);
        
        if ( !strcmp(json_object_get_string(jcommand), "add") )
        {
            json_object * jrow;
            json_object_object_get_ex(jmsg, "Row", &jrow);
            db_add_row(j_db, jrow);
            printf ("The db now %s\n",json_object_to_json_string(*j_db));
        }
        else if ( !strcmp(json_object_get_string(jcommand), "remove") )
        {
            db_remove_row(j_db, status);
        }
        else if ( !strcmp(json_object_get_string(jcommand), "show") )
        {
            write(sockfd, json_object_to_json_string(*j_db), MAX);
        }
        else if ( !strcmp(json_object_get_string(jcommand), "search") )
        {
            json_object *jrocket_wanted;
            json_object *jrocket;
            json_object *jrockets_array;
            json_object_object_get_ex(j_db, "Name of a rocket", &jrockets_array);
            json_object_object_get_ex(jmsg, "Name of a rocket", &jrocket_wanted);
            int n_rows = json_object_array_length(jrockets_array);
            for(int i = 0; i < n_rows; i++)
            {
                jrocket = json_object_array_get_idx(jrockets_array, i);
                if( strstr( json_object_get_string(jrocket), json_object_get_string(jrocket_wanted) ) == NULL )
                    continue;
                else
                {
                    bzero(buff, sizeof(buff)); 
                    get_row_by_number(*j_db, buff, i, status);
                }
                
            }

        }
        else 
        {

        }
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : ", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n'); 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}

int main()
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;


    json_object * j_db;
    char * status = malloc(100);
    strcpy(status, "ok");
    db_init(&j_db);
    db_save_to_file(&j_db, DB_FILE_NAME, status);
    db_read_from_file(&j_db, DB_FILE_NAME, status);
    // db_remove_row(&j_db, status);
    printf("status: %s\n", status);
    printf ("The json object created: %s\n",json_object_to_json_string(j_db));



    // socket create and verification 
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    // Function for chatting between client and server 
    talk_with_client(connfd, &j_db, status); 
  
    // After chatting close the socket 
    close(sockfd);  
    free(status);
}