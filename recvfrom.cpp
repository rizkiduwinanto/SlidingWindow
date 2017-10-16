#include <iostream>
using namespace std;



int main() {
  //UDP socket
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
  configureSetting(IP, portNumber);
}
