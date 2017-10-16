#include <data.h>

char Segment::calculateChecksum() {

}

char ACK::calculateChecksum() {

}

Segment::Segment(int sequenceNumber, char data) {
  //SOH
  bytes[0] = 0x1;
  //sequenceNumber
  bytes[1] = (sequenceNumber >> 24) & 0xFF;
  bytes[2] = (sequenceNumber >> 16) & 0xFF;
  bytes[3] = (sequenceNumber >> 8) & 0xFF;
  bytes[4] = sequenceNumber & 0xFF;
  //STX
  bytes[5] = 0x2;
  //Data
  bytes[6] = data;
  //ETX
  bytes[7] = 0x3;
  //calculateChecksum
  bytes[8] = calculateChecksum();
}

ACK::ACK(int nextSequenceNumber, char advertisedWindowSize) {
  //ACK
  bytes[0] = 0x6;
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
