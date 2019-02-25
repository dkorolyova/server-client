#ifndef SOCKET_CONFIG_FILE_PARSER_H
#define SOCKET_CONFIG_FILE_PARSER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

struct ConfigStruct {
  char *path_to_folder;
  uint16_t port;
};

struct ConfigStruct ParseConfigFile();
char *ParseSortType(char *buffer);

#endif //SOCKET_CONFIG_FILE_PARSER_H
