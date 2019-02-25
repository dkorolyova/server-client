#include <stdio.h>
#include <stdlib.h>
#include "functions_server.h"
#include "file_sorter.h"
#include "../shared/platform.h"
#include "../shared/network.h"
#include "../shared/constants.h"

const char *kInvalidValue = "Invalid value\n";
const char *kErrorStartingServer = "Error while starting listening connections\n";

int ConnectionHandler(struct ConfigStruct config_data);

int main(int argc, char *argv[]) {
  struct ConfigStruct config_data = ParseConfigFile();
  if (ConnectionHandler(config_data) < 0) {
    fprintf(stderr, "%s", kErrorStartingServer);
  }
  return 0;
}

int ConnectionHandler(struct ConfigStruct config_data) {
  int socket_desc = 0, server_sock = 0;
  const size_t kRequestSize = 20;
  char request_string[kRequestSize + 1];

  server_sock = BindSocket(config_data.port);

  if (server_sock < 0) {
    perror("bind");
    return -1;
  }

  if (Listen(server_sock) < 0) {
    perror("listen");
    return -1;
  }

  socket_desc = Accept(server_sock);
  if (socket_desc < 0) {
    perror("accept");
    return -1;
  }

  int filesInDir = 0;

  while (socket_desc > 0) {
    Receive(socket_desc, request_string, kRequestSize);
    char *sorting_value = ParseSortType(request_string);
    if (sorting_value != NULL) {

#ifdef __linux__
      struct FileStruct *fs = LookDir((char *) config_data.path_to_folder, &filesInDir);
      if (strcmp(sorting_value, PARAM_DATE) != 0) {
        SortFileStructureByTime(fs, (size_t) filesInDir);
      }

      if (strcmp(sorting_value, PARAM_TYPE) != 0) {
        SortFileStructureByType(fs, (size_t) filesInDir);
      }

      if (strcmp(sorting_value, PARAM_NAME) != 0) {
        SortFileStructureByName(fs, (size_t) filesInDir);
      }
#endif
      //TODO: Write a function for sorting files for Windows

      char response_string[50];
      snprintf(response_string, sizeof(response_string), "%s%d", "Files sorted:", filesInDir);

      Send(socket_desc, response_string);
      printf("%s\n", sorting_value);
    } else {
      Send(socket_desc, kInvalidValue);
    }
    socket_desc = Accept(server_sock);
  }

  if (CloseSocket(socket_desc) < 0) {
    fprintf(stderr, "Error closing socket");
    return -1;
  }

  return 0;
}
