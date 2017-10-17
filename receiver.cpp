#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

struct sockaddr_in serverAddress;
struct sockaddr_storage serverStorage;
socklen_t addressSize;

int main(int argc, char* argv[]) {
  if(argc != 6){
    cout << "Usage : ./receiver <filename> <windowsize> <buffersize> <destination_ip> <destination_port>";
  } else {
    //INPUT dari SendFile
    char* fileName = argv[1];
    int windowSize = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    char* IP = argv[4];
    int portNumber = atoi(argv[5]);
    int clientSocket;
	
	fileName = "textfile.txt";
    windowSize = 1;
    bufferSize = 256;
    IP = "127.0.0.1";
    portNumber = 7891;
	
	char buffer[256];
	
	// UDP
	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	serverAddress.sin_addr.s_addr = inet_addr(IP);
	memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);  
	
	addressSize = sizeof serverAddress;
	
	while(1) {
		buffer[0] = 'h';
		printf("Send to server: %s\n",buffer);
		int nBytes = strlen(buffer) + 1;
	    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddress,addressSize);
		nBytes = recvfrom(clientSocket,buffer,bufferSize,0,NULL, NULL);
		printf("Received from server: %s\n",buffer);
	}
  }
  return 0;
}
