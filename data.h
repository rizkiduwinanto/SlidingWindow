#include <iostream>
using namespace std;

class Segment {
  public:
    Segment();
    Segment(int sequenceNumber, char data);
    Segment(const char *bytes);
  private:
    char bytes[length];
    static size_t length = 9;
    char calculateChecksum();
}

class ACK {
  public:
    ACK();
    ACK(int nextSequenceNumber, char advertisedWindowSize);
    ACK(const char *bytes);
  private:
    char bytes[length];
    static size_t length = 7;
    char calculateChecksum();
}
