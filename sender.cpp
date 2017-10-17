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
    FILE *fp;
    fp = fopen(fileName,"r");
    
    /** CEK ERROR **/
    if (fp == NULL) {
        cout << "ERROR : file not found" << endl;
    } else {
        while(!feof(fp)) {
          /** MASUKKAN FILE KE BUFFER **/
          int c;
          int x = 0;
          while ((c = fgetc(fp)) != EOF && x<bufferSize ) {
            buffer[x] = c ;
            x++;
          }
          
          cout << "Send to server: "<< buffer << endl;
          int nBytes = strlen(buffer);
          cout << "NB " << nBytes << endl;
          sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddress,addressSize);
          nBytes = recvfrom(clientSocket,buffer,bufferSize,0,NULL, NULL);
          cout << "Received from server: "<< buffer << endl;
        }
        fclose(fp);
      }
    }
  return 0;
}

