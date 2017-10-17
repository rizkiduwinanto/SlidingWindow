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

struct sockaddr_in serverAddress, clientAddress;
struct sockaddr_storage serverStorage;
socklen_t addressSize, clientAddressSize;

void configureSetting(int portNumber) {
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNumber);
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);
}

int main(int argc, char** argv) {
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
    bind(receiverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

  }
}
