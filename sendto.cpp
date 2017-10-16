#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void configureSetting(char* IP, int portNumber) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNumber);
    serverAddr.sin_addr.s_addr = inet_addr(IP);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
}

int main(int argc, char* argv[]) {
  //INPUT dari SendFile
  char* fileName = argv[0];
  int windowSize = atoi(argv[1]);
  int bufferSize = atoi(argv[2]);
  char* IP = argv[3];
  int portNumber = atoi(argv[4]);
  //UDP socket
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
  configureSetting(IP, portNumber);
  //Init

  return 0;
}
