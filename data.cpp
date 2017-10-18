#include "data.h"
#define SOH 0x1
#define STX 0x2
#define ETX 0x3
#define ACKID 0x6

char Segment::calculateChecksum() {
  char sum = 0;
  for (int i=0; i<length-1; i++) {
    sum += bytes[i];
  }
  char negation = -sum;
  return (negation & 0xFF);
}

char Segment::getResultSum() {
  char sum = 0;
  for (int i=0; i<length-1; i++) {
    sum += bytes[i];
  }
  sum += getChecksum();
  char negation = -sum;
  return (negation & 0xFF);
}

char Segment::getChecksum(){
  return calculateChecksum();
}

char ACK::calculateChecksum() {
  char sum = 0;
  for (int i=0; i<length-1; i++) {
    sum += bytes[i];
  }
  char negation = -sum;
  return (negation & 0xFF);
}

char ACK::getResultSum() {
  char sum = 0;
  for (int i=0; i<length-1; i++) {
    sum += bytes[i];
  }
  sum += getChecksum();
  char negation = -sum;
  return (negation & 0xFF);
}

char ACK::getChecksum(){
  return calculateChecksum();
}

Segment::Segment() {
  bytes = new char[length];
  //SOH
  bytes[0] = SOH;
  //sequenceNumber
  bytes[1] = 0;
  bytes[2] = 0;
  bytes[3] = 0;
  bytes[4] = 0;
  //STX
  bytes[5] = STX;
  //Data
  bytes[6] = 0;
  //ETX
  bytes[7] = ETX;
  //calculateChecksum
  bytes[8] = calculateChecksum();
}

Segment::Segment(int sequenceNumber, char data) {
  bytes = new char[length];
  //SOH
  bytes[0] = SOH;
  //sequenceNumber
  bytes[1] = (sequenceNumber >> 24) & 0xFF;
  bytes[2] = (sequenceNumber >> 16) & 0xFF;
  bytes[3] = (sequenceNumber >> 8) & 0xFF;
  bytes[4] = sequenceNumber & 0xFF;
  //STX
  bytes[5] = STX;
  //Data
  bytes[6] = data;
  //ETX
  bytes[7] = ETX;
  //calculateChecksum
  bytes[8] = calculateChecksum();
}

Segment::Segment(char* buffer) {
  bytes = new char[length];
  for (int i=0; i<length; i++) {
	bytes[i] = buffer[i]; 
	}
 }

void Segment::printSegment(){
  for (int i=0; i<length; i++){
    cout << hex <<(unsigned int) (bytes[i]) << endl;
  }
}

char* Segment::toBytes(){
  return bytes;
}

Segment::~Segment(){
  delete [] bytes;
}

void Segment::setSequenceNumber(int sequenceNumber){
  bytes[1] = (sequenceNumber >> 24) & 0xFF;
  bytes[2] = (sequenceNumber >> 16) & 0xFF;
  bytes[3] = (sequenceNumber >> 8) & 0xFF;
  bytes[4] = sequenceNumber & 0xFF;
}

int Segment::getSequenceNumber(){
  int integer = (int)(bytes[1] << 24 | bytes[2] << 16 | bytes[3] << 8 | bytes[4]);
  return integer;
}

void Segment::setData(char data){
  bytes[6] = data;
}

char Segment::getData(){
  return bytes[6];
}

ACK::~ACK(){
  delete [] bytes;
}

char* ACK::toBytes(){
  return bytes;
}

ACK::ACK() {
  bytes = new char[length];
  //ACK
  bytes[0] = ACKID;
  //nextSequenceNumber
  bytes[1] = 0;
  bytes[2] = 0;
  bytes[3] = 0;
  bytes[4] = 0;
  //advertisedWindowSize
  bytes[5] = 0;
  //calculateChecksum
  bytes[6] = calculateChecksum();
}

ACK::ACK(char* buffer) {
  bytes = new char[length];
  for (int i=0; i<length; i++) {
  bytes[i] = buffer[i]; 
  }
 }

ACK::ACK(int nextSequenceNumber, char advertisedWindowSize) {
  bytes = new char[length];
  //ACK
  bytes[0] = ACKID;
  //nextSequenceNumber
  bytes[1] = (nextSequenceNumber >> 24) & 0xFF;
  bytes[2] = (nextSequenceNumber >> 16) & 0xFF;
  bytes[3] = (nextSequenceNumber >> 8) & 0xFF;
  bytes[4] = nextSequenceNumber & 0xFF;
  //advertisedWindowSize
  bytes[5] = advertisedWindowSize;
  //calculateChecksum
  bytes[6] = calculateChecksum();
}

int ACK::getNextSequenceNumber(){
  int integer = (int)(bytes[1] << 24 | bytes[2] << 16 | bytes[3] << 8 | bytes[4]);
  return integer;
}