#ifndef SOCKET_NETWORK_H
#define SOCKET_NETWORK_H

#include "platform.h"
#include <string.h>

const struct sockaddr_in CreateAddrStructure(uint16_t port_number, in_addr_t ip_address);
int ConnectSocket(uint16_t port_number, const char *ip_address);
int BindSocket(uint16_t port_number);
int Listen(int fd);
int Accept(int fd);
int Send(int socket_desc, const char* value);
int Receive(int socket_desc, char *recv_value, size_t size);

#endif //SOCKET_NETWORK_H
