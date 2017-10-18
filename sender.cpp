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
      int seq = 0;
      do {
        while (x<bufferSize && fp.get(c)) {
          buffer[x] = c;
          x++;
        }
        nBytes = x;

        cout << "NB " << nBytes << endl;

        int j = 0;
        seq = 0;
        while (j < nBytes) {
          Segment msg;
          msg.setSequenceNumber(seq);
          msg.setData(buffer[j]);  
          j++;
          ACK ack;
          do {
            sendto(clientSocket,msg.toBytes(),9,0,(struct sockaddr *)&serverAddress,addressSize);
            cout << msg.toBytes();            
            char ackbytes[7];
            int nack = recvfrom(clientSocket,ackbytes,7,0,NULL,NULL);
            ack.bytes[0] = ackbytes[0];
            ack.bytes[1] = ackbytes[1];
            ack.bytes[2] = ackbytes[2];
            ack.bytes[3] = ackbytes[3];
            ack.bytes[4] = ackbytes[4];
            ack.bytes[5] = ackbytes[5];
            cout << "ack seqnum : " << ack.getNextSequenceNumber() << endl;
            ack.bytes[6] = ackbytes[6];
            cout << "ack checksum : " << int(ack.getResultSum()) << endl;
          } while (ack.getResultSum() != 0);
           seq++;       
        }

        if (fp.eof()){
		  // do nothing
          break;
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

