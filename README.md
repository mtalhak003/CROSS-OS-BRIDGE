 ## CROSS-OS BRIDGE
CROSS-OS BRIDGE is a server-client communication system developed for my Operating Systems Lab at UET Peshawar. The server handles multiple client connections, manages tutor and chair resources, and shuts down gracefully upon receiving a termination signal. This project demonstrates practical applications in resource management, remote tutoring, and distributed task processing.


## Problem Statement
I aim to create a server-client communication system where a server can handle multiple client connections. The server will manage tutor and chair resources and respond to client requests. Clients will connect to the server, request a specified number of help sessions and chairs, and then terminate the connection. The server will shut down gracefully upon receiving a termination signal from a client.

## Algorithms

## 1. Server Algorithm
Parse command-line arguments to get the number of tutors and chairs.
Create a socket and bind it to a specified port.
Listen for incoming client connections.
Accept a connection and create a new thread to handle each client.
In each client handler thread:
Read data from the client.
Check for a termination signal.
If a termination signal is received, send an acknowledgment and set a flag to shut down the server.
Close the client socket.
Shut down the server by user (the server will run in a while(1) loop and wait for more clients).
## 2. Client Algorithm
Parse command-line arguments to get the server IP, number of students, help sessions, and chairs.
Initialize Winsock and create a socket.
Connect to the server.
Simulate client actions by sending requests to the server.
Send a termination signal to the server.
Receive acknowledgment from the server.
Close the socket and clean up Winsock resources.


## Functions and Libraries Used
## Server Side (server.c on Linux)
## Functions:
socket(): Creates a socket for communication.
bind(): Binds the socket to a specific IP address and port.
listen(): Sets the socket to listen for incoming connections.
accept(): Accepts an incoming connection request from a client.
pthread_create(): Creates a new thread to handle each client connection.
pthread_join(): Waits for thread termination.
read(), write(), send(), recv(): Functions for reading from and writing to sockets.
close(): Closes sockets and cleans up resources.
## Libraries:
stdio.h, stdlib.h, string.h: Standard C libraries for basic I/O, memory allocation, and string manipulation.
unistd.h: Provides access to the POSIX operating system API (used for close() function).
arpa/inet.h: Definitions for internet operations (used for struct sockaddr_in).
pthread.h: POSIX threads library for thread management.
## Client Side (client.c for Windows)
## Functions:
WSAStartup(), WSACleanup(): Initialize and clean up Winsock (Windows Sockets API).
socket(), connect(), send(), recv(): Functions for socket creation, connection establishment, and data transmission/reception.
sprintf(): Format string into buffer.
Sleep(): Pause execution for a specified number of milliseconds.
closesocket(): Close the socket and release resources.
## Libraries:
stdio.h, stdlib.h, string.h: Standard C libraries.
winsock2.h: Header for Windows Sockets 2 API.
windows.h: Windows API header providing access to core functions like Sleep().
time.h: Header providing time-related functions (though not extensively used in this code).

