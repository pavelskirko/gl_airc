#include "db_server.h"


#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr

extern int errno ;

void talk_with_client(int sockfd)
{
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
        while(1)
        { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
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


    json_object * jobj;
    json_object * jobj_rec;
    char * status = malloc(100);
    strcpy(status, "ok");
    db_init(&jobj);
    db_save_to_file(&jobj, DB_FILE_NAME, status);
    db_read_from_file(&jobj, DB_FILE_NAME, status);
    db_read_from_file(&jobj_rec, DB_FILE_NAME_REC, status);
    db_add_row(&jobj, jobj_rec);
    db_remove_row(&jobj, status);
    printf("status: %s\n", status);
    printf ("The json object created: %s\n",json_object_to_json_string(jobj));



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
    talk_with_client(connfd); 
  
    // After chatting close the socket 
    close(sockfd);  
}