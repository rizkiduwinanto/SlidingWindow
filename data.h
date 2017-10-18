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
    char* toBytes();
    ~Segment();
    void setSequenceNumber(int sequenceNumber);
    int getSequenceNumber();
    void setData(char data);
    char getData();
  private:
    static const size_t length = 9;
    char * bytes;
    char calculateChecksum();
};

class ACK {
  public:
    ACK();
    ACK(int nextSequenceNumber, char advertisedWindowSize);
    ACK(const char *bytes);
    int getIntFromACK();
    void printACK();
    char* toBytes();
    ~ACK();
  private:
    static const size_t length = 7;
    char * bytes;
    char calculateChecksum();
};
