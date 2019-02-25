#include <stdio.h>
#include <stdlib.h>
#include "functions_client.h"
#include "../shared/platform.h"
#include "../shared/network.h"

#define RESPONSE_SIZE 50
#define REQUEST_SIZE 10

const char
    *kTypeRequestString = "Please enter type of sorting as <sorting_type> (possible sorting types: name/type/date): ";

int RunClient();

int main(int argc, char *argv[]) {
  if (RunClient() < 0) {
    fprintf(stderr, "Error running client");
  }
  return 0;
}

int RunClient() {
  int socket_file_desc = 0;
  const char *kIpAddr = "127.0.0.1";

  struct ConfigStruct config_data = ParseConfigFile();

  socket_file_desc = ConnectSocket(config_data.port, kIpAddr);

  if (socket_file_desc < 0) {
    return -1;
  }

  char sort_request[] = "sort:";
  char request_string[REQUEST_SIZE];
  printf("%s", kTypeRequestString);
  fflush(stdout);
  scanf("%s", request_string);
  strcat(sort_request, request_string);
  if (Send(socket_file_desc, sort_request) == -1) {
    perror("send");
    return -1;
  }

  char response[RESPONSE_SIZE];
  memset(&response, '\0', sizeof(response));
  Receive(socket_file_desc, response, RESPONSE_SIZE);
  printf("%s%s", "Server response:", response);

  if (CloseSocket(socket_file_desc) < 0) {
    fprintf(stderr, "Error closing socket");
    return -1;
  }

  return 0;
}