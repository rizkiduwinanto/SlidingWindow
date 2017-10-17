#include <iostream>
#include "data.h"
using namespace std;

int main() {
    Segment Seg(2,'3');
    Seg.printSegment();
    cout << "Test!" << endl;
    cout << hex <<(unsigned int) (Seg.getResultSum()) << endl;
    return 0;
}