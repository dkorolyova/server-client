
#ifndef SOCKET_NETWORK_WIN_H
#define SOCKET_NETWORK_WIN_H

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
  #include <winsock.h>
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <stdbool.h>
#endif

#ifdef _WIN32
  typedef long in_addr_t;
  typedef u_short uint16_t;
#endif

void SetWsaData();
int CloseSocket(int socket_desc);

#endif //SOCKET_NETWORK_WIN_H
