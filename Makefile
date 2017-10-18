all: sender receiver
sender: sender.cpp data.cpp
	g++ -o sender sender.cpp data.cpp --std=c++11
receiver: receiver.cpp data.cpp
	g++ -o receiver receiver.cpp data.cpp --std=c++11
clean:
	rm -f sender receiver sender.o receiver.o 
