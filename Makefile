all: sender receiver
sender: sender.cpp
	g++ -o sender sender.cpp
receiver: receiver.cpp
	g++ -o receiver receiver.cpp
clean:
	rm -f sender.o receiver.o 
