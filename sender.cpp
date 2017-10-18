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
    cout << "Usage : ./sender <filename> <windowsize> <buffersize> <destination_ip> <destination_port>";
  } else {
    //INPUT dari SendFile
    char* fileName = argv[1];
    int windowSize = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    char* IP = argv[4];
    int portNumber = atoi(argv[5]);
    int clientSocket;
    
    char buffer[bufferSize];
    
    // UDP
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = inet_addr(IP);
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);  
    
    addressSize = sizeof serverAddress;
    
    /** OPEN FILE **/
    ifstream fp;
    fp.open(fileName);
    
    /** CEK ERROR **/
    if (!fp) {
        cout << "ERROR : file not found" << endl;
    } else {
      char c;
      int x = 0;
      int nBytes = 0;
      do {
        while (x<bufferSize && fp.get(c)) {
          buffer[x] = c;
          cout << "X: "<<x << "C: "<<c << endl;
          x++;
        }
        nBytes = x;
        cout << "NB " << nBytes << endl;
        sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddress,addressSize);
        nBytes = recvfrom(clientSocket,buffer,bufferSize,0,NULL, NULL);
        // cout << "Received from server: "<< buffer << endl;  
        if (fp.eof()){
			// do nothing
        } else if (!fp.eof() && x == bufferSize){
          memset(buffer,'\0',sizeof(buffer));
        }
        x = 0;
        buffer[x] = c;
      } while (nBytes > 0);
      fp.close();
   }
  }
  return 0;
}

