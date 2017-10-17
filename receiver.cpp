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

void configureSetting(int portNumber) {
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNumber);
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cout << "Usage : ./recvfile​ ​ <filename>​ ​ <windowsize>​ ​ <buffersize>​ ​ <port>";
  } else {
    //INPUT dari recvfile
    char* fileName = argv[1];
    int windowSize = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    //UDP socket
    int receiverSocket, portNumber;
    portNumber = atoi(argv[4]);
    receiverSocket = socket(PF_INET, SOCK_DGRAM, 0);
    configureSetting(portNumber);
    char *buffer[256] = {0};
    bind(receiverSocket,(struct sockaddr*) &serverAddress, sizeof(serverAddress));
    while(1) {
      recvfrom(receiverSocket, buffer, bufferSize,0, (struct sockaddr*)&serverAddress, (socklen_t *)sizeof(serverAddress));
      if (bufferSize>0) {
        cout << buffer;
      }
    }
  }
  return 0;
}
