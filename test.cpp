#include <iostream>
#include "data.h"
using namespace std;

int main() {
    Segment Seg(2,'P');
    Seg.printSegment();
    cout << "Test!" << endl;
    cout << Seg.getData() << endl;
    return 0;
}