
#include "platform.h"
#ifdef _WIN32

void SetWsaData() {
  WSADATA wsa_data;
  if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
    fprintf(stderr, "WSAStartup() failed");
    exit(1);
  }
}

int CloseSocket(int socket_desc) {
  int close_connection = closesocket(socket_desc);
  WSACleanup();
  return close_connection;
}

#else

void SetWsaData() {}

int CloseSocket(int socket_desc) {
  return close(socket_desc);
}

#endif