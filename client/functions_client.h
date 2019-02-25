#ifndef SOCKET_CONFIG_FILE_PARSER_H
#define SOCKET_CONFIG_FILE_PARSER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

struct ConfigStruct {
  uint16_t port;
};

struct ConfigStruct ParseConfigFile();
#endif //SOCKET_CONFIG_FILE_PARSER_H
