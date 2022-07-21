#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void    error_handing(char *err_message);
void    tcp_client_handing(int clntSocket);
int     create_tcp_socket(unsigned short port);
void    accept_tcp_connect(int servSock);