"""
Server receiver buffer is char[256]
If correct, the server will send a message back to you saying "I got your message"
Write your socket client code here in python
Establish a socket connection -> send a short message -> get a message back -> terminate
use python "input->" function, enter a line of a few letters, such as "abcd"
"""
import socket

HOST= '192.168.1.146'
PORT= 8824

def main():
    # TODO: Create a socket and connect it to the server at the designated IP and port
    my_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    my_sock.connect((HOST,PORT))
    # TODO: Get user input and send it to the server using your TCP socket
    text= input("Input what you would like to send: ")
    my_sock.send(text.encode())
    # TODO: Receive a response from the server and close the TCP connection
    data= my_sock.recv(256)
    data= data.decode()
    print(data)
    my_sock.close()
if __name__ == '__main__':
    main()
