#include <iostream>
using namespace std;

class Segment {
  public:
    Segment();
    Segment(int sequenceNumber, char data);
    Segment(const char *bytes);
    void printSegment();
    char getChecksum();
    char getResultSum();
  private:
    static const size_t length = 9;
    char bytes[9];
    char calculateChecksum();
};

class ACK {
  public:
    ACK();
    ACK(int nextSequenceNumber, char advertisedWindowSize);
    ACK(const char *bytes);
    int getIntFromACK();
    void printACK();
  private:
    static const size_t length = 7;
    char bytes[7];
    char calculateChecksum();
};
