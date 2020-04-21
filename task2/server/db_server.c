#include "db_server.h"


#define MAX 1024 
#define STATUS_SIZE 100
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
            db_save_to_file(j_db, DB_FILE_NAME, status);
        }
        else if ( !strcmp(json_object_get_string(jcommand), "remove") )
        {
            bzero(status, STATUS_SIZE);
            strcpy(status, "ok");
            db_remove_row(j_db, status);
            bzero(buff, MAX); 
            get_json_status(buff, MAX, status);
            write(sockfd, buff, MAX);
            db_save_to_file(j_db, DB_FILE_NAME, status);
            
        }
        else if ( !strcmp(json_object_get_string(jcommand), "show") )
        {
            json_object *jmsg_ans = json_object_new_object();
            json_object *jstatus = json_object_new_string(status); 
            json_object_object_add(jmsg_ans, "Status", jstatus);
            json_object_object_add(jmsg_ans, "Table", *j_db);

            write(sockfd, json_object_to_json_string(jmsg_ans), MAX);
            bzero(status, STATUS_SIZE);
            strcpy(status, "ok");
        }
        else if ( !strcmp(json_object_get_string(jcommand), "search") )
        {
            json_object *jrocket_wanted;
            json_object *jrocket;
            json_object *jrockets_array;
            json_object_object_get_ex(*j_db, "Name of a rocket", &jrockets_array);
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
                    bzero(status, STATUS_SIZE);

                    strcpy(status, "ok");
                    get_row_by_number(*j_db, buff, i, status);
                    write(sockfd, buff, MAX);

                    bzero(status, STATUS_SIZE);
                    strcpy(status, "row is found");
 
                    break;
                }
            }
            if ( strcmp(status, "row is found") )
            {
                bzero(status, STATUS_SIZE);
                strcpy(status, "row is not found");
                printf("row is not found");
                bzero(buff, MAX);
                get_json_status(buff, MAX, status);
                write(sockfd, buff, MAX);
                bzero(status, STATUS_SIZE);
                strcpy(status, "ok");
            }

        }
        else if ( !strcmp(json_object_get_string(jcommand), "exit") )
        {
            printf("Exit\n");
            break;
        }
        else
        {
            printf("wrong command");
            strcpy(status, "wrong command");
        }
    } 
}

int main()
{
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;


    json_object * j_db;
    char * status = malloc(STATUS_SIZE);
    strcpy(status, "ok");
    db_init(&j_db);
    db_save_to_file(&j_db, DB_FILE_NAME, status);
    printf("Database is stored in file %s\n", DB_FILE_NAME);
    // db_read_from_file(&j_db, DB_FILE_NAME, status);
    printf("status: %s\n", status);

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