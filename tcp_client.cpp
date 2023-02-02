// Server side C/C++ program to demonstrate Socket programming 
// Here's some include statements that might be helpful for you
#include <string> 
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) 
{ 
	// check to see if user input is valid
	char socket_read_buffer[1024];
	
	// TODO: Fill out the server ip and port
	std::string server_ip = "localhost";
	std::string server_port = "8080";

	int opt = 1;

	// TODO: Create a TCP 
	int client_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Enable reusing address and port
	if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		return -1;
	}

	// Check if the client socket was set up properly
	if(client_fd == -1){
		printf("Error- Socket setup failed");
		return -1;
	}
	
	// Helping you out by pepping the struct for connecting to the server
	struct addrinfo hints;
	struct addrinfo *server_addr;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// TODO: Connect() to the server (hint: you'll need to use server_addr)
	int status = getaddrinfo(server_ip.c_str(), server_port.c_str(), &hints, &server_addr);
	if (status != 0) {
		printf("Error- Failed to get address information: %s\n", gai_strerror(status));
		return -1;
	}
	
	if (connect(client_fd, server_addr->ai_addr, server_addr->ai_addrlen) < 0) {
		printf("Error- Failed to connect to server\n");
		return -1;
	}
	// TODO: Retreive user input
	
	std::string message;
	std::cout << "Enter message to send to server: ";
	std::cin >> message;
	
	// TODO: Send() the user input to the server
	send(client_fd, message.c_str(), message.length(), 0);
	
	// TODO: Receive any messages from the server and print it here. Don't forget to make sure the string is null terminated!
	int bytes_received = recv(client_fd, socket_read_buffer, sizeof(socket_read_buffer), 0);
	if (bytes_received > 0) {
		socket_read_buffer[bytes_received] = '\0';
		printf("Received message from server: %s\n", socket_read_buffer);
	}
	
	// TODO: Close() the socket
	close(client_fd);
} 
