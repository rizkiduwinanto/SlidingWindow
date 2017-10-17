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

Segment::Segment() {
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

void Segment::printSegment(){
  for (int i=0; i<length; i++){
    cout << hex <<(unsigned int) (bytes[i]) << endl;
  }
}

ACK::ACK() {
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


ACK::ACK(int nextSequenceNumber, char advertisedWindowSize) {
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
