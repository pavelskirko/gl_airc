#include "db_client.h"

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