#include <iostream>
using namespace std;

class Segment {
  public:
    Segment();
    Segment(int sequenceNumber, char data);
    Segment(char *buffer);
    void printSegment();
    char getChecksum();
    char getResultSum();
    char* toBytes();
    ~Segment();
    void setSequenceNumber(int sequenceNumber);
    int getSequenceNumber();
    void setData(char data);
    char getData();

    static const size_t length = 9;
    char * bytes;
    char calculateChecksum();
};

class ACK {
  public:
    ACK();
    ACK(int nextSequenceNumber, char advertisedWindowSize);
    ACK(char *bytes);
    int getIntFromACK();
    void printACK();
    char getChecksum();
    char getResultSum();
    char* toBytes();
    ~ACK();
    int getNextSequenceNumber();
    static const size_t length = 7;
    char * bytes;
    char calculateChecksum();
};
