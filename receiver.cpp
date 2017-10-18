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
#include "data.h"

using namespace std;

struct sockaddr_in serverAddress;
struct sockaddr_storage serverStorage;
socklen_t addressSize;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cout << "Usage : ./receiver​ <filename>​ ​ <windowsize>​ ​ <buffersize>​ ​ <port>";
  } else {
    //INPUT dari recvfile
    char* fileName = argv[1];
    int windowSize = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    int portNumber = atoi(argv[4]);
    int udpSocket;
    char buffer[bufferSize];
    
    //UDP socket
    if ((udpSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout << "ERROR : cannot create socket" << endl;
		return 0;
	}
	
	//CONFIGURE
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);
    
    //BIND
    if (bind(udpSocket,(struct sockaddr*) &serverAddress, sizeof(serverAddress))) {
		cout << "ERROR : bind failed" << endl;
		return 0;
	}
    
    addressSize = sizeof serverStorage;
    
    //CLEAR EXISTING FILE 
    if( remove(fileName) != 0 ){
		//do nothing
	}
	
    //RECEIVE & WRITE FILE
	
    while(1) {
		int nBytes = recvfrom(udpSocket,buffer,bufferSize,0,(struct sockaddr *)&serverStorage, &addressSize);
		Segment received(buffer);
		ofstream fp;
		fp.open (fileName, ios_base::app | ios::binary);
		int i = 0;
		while (i<nBytes){
			fp << received.getData();
			i++;
		}
		cout << "Received by server: "<< buffer << endl;   
		fp.close();
		//sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addressSize);
	}

  

  }
  return 0;
}
