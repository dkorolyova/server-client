#include "functions_client.h"

const char *kPathToConfig = "config.conf";

struct ConfigStruct ParseConfigFile() {
  FILE *file;
  char *line = NULL;
  size_t mem_size = 0;
  struct ConfigStruct config_data;
  config_data.port = 0;
  file = fopen(kPathToConfig, "r");
  if (file != NULL) {
    while (getline(&line, &mem_size, file) != -1) {
      if (strstr(line, "port") != NULL) {
        config_data.port = (uint16_t) atoi(line + 4);
      }
    }
    fclose(file);
  }
  return config_data;
}