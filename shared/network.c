#include "network.h"
#include <stdio.h>

const int kBackLog = 5;

const struct sockaddr_in CreateAddrStructure(uint16_t port_number, in_addr_t ip_address) {
  struct sockaddr_in server_addr;
  memset(&server_addr, '\0', sizeof(struct sockaddr_in));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port_number);
  server_addr.sin_addr.s_addr = ip_address;

  return server_addr;
}

int ConnectSocket(uint16_t port_number, const char *ip_address) {
  int socket_file_desc = 0;
  SetWsaData();
  if ((socket_file_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Cannot create socket");
    return -1;
  }
  struct sockaddr_in server_addr = CreateAddrStructure(port_number, inet_addr(ip_address));

  if (connect(socket_file_desc, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("connect");
    return -1;
  }

  return socket_file_desc;
}

int BindSocket(uint16_t port_number) {
  int server_sock = 0;

  SetWsaData();
  if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    printf("Socket() failed");
    return -1;
  }
  const struct sockaddr_in server_addr = CreateAddrStructure(port_number, htonl(INADDR_ANY));
  bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
  return server_sock;
}

int Listen(int fd) {
  return listen(fd, kBackLog);
}

int Accept(int fd) {
  return accept(fd, (struct sockaddr *) NULL, NULL);
}

int Send(int socket_desc, const char *value) {
  return (int) send(socket_desc, value, strlen(value), 0);
}
int Receive(int socket_desc, char *recv_value, size_t size) {
  memset(recv_value, '\0', (size + 1) * sizeof(char));
  return (int) recv(socket_desc, recv_value, size, 0);
}