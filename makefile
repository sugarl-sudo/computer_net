TCPEchoClient: TCPEchoClient.o DieWithError.o
	gcc -o TCPEchoClient TCPEchoClient.c

TCPEchoServer: TCPEchoServer.o DieWithError.o HandleTCPClient.o
	gcc -o TCPEchoServer TCPEchoServer.c

TCPEchoServer-Fork: TCPEchoServer-Fork.o DieWithError.o HandleTCPClient.o CreateTCPServerSocket.o AcceptTCPConnection.o
	gcc -o TCPEchoServer-Fork TCPEchoServer-Fork.c

TCPEchoServer-Thread: TCPEchoServer-Thread.o DieWithError.o HandleTCPClient.o CreateTCPServerSocket.o AcceptTCPConnection.o
	gcc -o TCPEchoServer-Thread TCPEchoServer-Thread.c -lpthread