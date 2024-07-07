// server.c
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h>
  #include <unistd.h>
#include <arpa/inet.h> 
#include <pthread.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int tutor_num; int chair_num; int server_socket;

// Function to handle client connections
void *handle_client(void *client_sock);

int main(int argc, char *argv[]) { if (argc != 3) {
printf("Usage: %s <# of tutors> <# of chairs>\n", argv[0]); exit(EXIT_FAILURE);
}

tutor_num = atoi(argv[1]); chair_num = atoi(argv[2]);

struct sockaddr_in server_addr, client_addr; socklen_t client_len = sizeof(client_addr); int *client_socket;

// Create socket
if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) { perror("Socket creation failed");
exit(EXIT_FAILURE);
}

// Setup server address server_addr.sin_family = AF_INET; server_addr.sin_addr.s_addr = INADDR_ANY; server_addr.sin_port = htons(SERVER_PORT);
 

// Bind the socket
if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
perror("Socket bind failed"); close(server_socket); exit(EXIT_FAILURE);
}

// Listen for connections
if (listen(server_socket, 3) < 0) { perror("Listen failed"); close(server_socket); exit(EXIT_FAILURE);
}

printf("Administration: Listening on port %d\n", SERVER_PORT);

while (1) {
// Accept incoming connection
client_socket = malloc(sizeof(int));
if ((*client_socket = accept(server_socket, (struct sockaddr
*)&client_addr, &client_len)) < 0) {
perror("Server: Accept failed"); free(client_socket);
continue;
}

printf("Server: Accepted connection from client\n");

// Create a new thread to handle the client
pthread_t thread_id;
if (pthread_create(&thread_id, NULL, handle_client, (void
*)client_socket) != 0) {
perror("Server: Failed to create thread"); free(client_socket);
continue;
}

// Detach the thread to allow resources to be cleaned up automatically
pthread_detach(thread_id);
}

printf("server: Shutting down.\n");
 
// Close the server socket
close(server_socket);

return 0;
}

// Function to handle communication with a client
void *handle_client(void *client_sock) { int sock = *(int *)client_sock; free(client_sock);

char buffer[BUFFER_SIZE];
int n;

while ((n = read(sock, buffer, BUFFER_SIZE)) > 0) { buffer[n] = '\0';
printf("Administration received: %s\n", buffer);

// Check for termination signal
if (strcmp(buffer, "TERMINATE") == 0) {
printf("Administration: Termination signal received. Shutting
down.\n");

// Send acknowledgment to the client strcpy(buffer, "Termination Acknowledged"); send(sock, buffer, strlen(buffer), 0);

// Close the client socket
close(sock);

// Exit the loop to shut down the server
break;
}
}

// Close the client socket if it wasn't already closed due to termination
if (strcmp(buffer, "TERMINATE") != 0) { close(sock);
printf("Administration: Connection closed with Coordinator.\n");
}

return NULL;
}
