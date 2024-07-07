#include <stdio.h>
 #include <stdlib.h>
  #include <string.h> 
  #include <winsock2.h>
   #include <windows.h>
    #include <time.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

void error_exit(const char *message) { perror(message); exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) { if (argc != 5) {
printf("Usage: %s <server IP> <# of students> <# of help sessions> <# of chairs>\n", argv[0]);
exit(-1);
}

char *server_ip = argv[1];
int student_num = atoi(argv[2]); int help_num = atoi(argv[3]); int chair_num = atoi(argv[4]);

WSADATA wsa;
SOCKET sock;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE];
// Initialize Winsock
if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
return 1;
}

// Create socket
if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
printf("Socket creation failed. Error Code: %d\n", WSAGetLastError()); WSACleanup();
return 1;
}

// Setup server address server_addr.sin_family = AF_INET; server_addr.sin_port = htons(SERVER_PORT);
server_addr.sin_addr.s_addr = inet_addr(server_ip);

// Connect to the server
if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
0) {
printf("Connection to the server failed. Error Code: %d\n", WSAGetLastError());
closesocket(sock); WSACleanup(); return 1;
}

printf("Coordinator: Connected to server at %s:%d\n", server_ip, SERVER_PORT);

// Simulate the client actions
for (int i = 0; i < student_num; i++) {
sprintf(buffer, "Student %d needs %d help sessions and %d chairs", i + 1, help_num, chair_num);
send(sock, buffer, strlen(buffer), 0); printf("Coordinator: Sent message: %s\n", buffer);

// Simulate some delay
Sleep(1000);
}

// Send termination signal
strcpy(buffer, "TERMINATE");
send(sock, buffer, strlen(buffer), 0); printf("Coordinator: Sent termination signal.\n");

// Receive acknowledgment from the server int n = recv(sock, buffer, BUFFER_SIZE, 0); if (n > 0) {
buffer[n] = '\0';
printf("Coordinator received: %s\n", buffer);
}

// Close the socket closesocket(sock); WSACleanup();

return 0;
}
