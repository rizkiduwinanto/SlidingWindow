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
int clientSocket;

void configureSetting(char* IP, int portNumber) {
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = inet_addr(IP);
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);
}

int main(int argc, char* argv[]) {
  if(argc != 6){
    cout << "Usage : ./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>";
  } else {
    //INPUT dari SendFile
    char* fileName = argv[1];
    int windowSize = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    char* IP = argv[4];
    int portNumber = atoi(argv[5]);
    //UDP socket
    clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    configureSetting(IP, portNumber);
    sendto(clientSocket, fileName, strlen(fileName), 0, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
  }
  return 0;
}
