#include "functions_server.h"
#include "../shared/constants.h"

char *ParseSortType(char *buffer) {
  char delim = ':';
  char *pdelim = strchr(buffer, delim);
  if (pdelim == NULL || pdelim + 1 == NULL) {
    fprintf(stderr, "Invalid sorting type: %s", buffer);
    return NULL;
  }
  const char *kSortValue = strtok(pdelim + 1, "\n");
  if (strcmp(kSortValue, PARAM_NAME) == 0) {
    return (char *) PARAM_NAME;
  } else if (strcmp(kSortValue, PARAM_DATE) == 0) {
    return (char *) PARAM_DATE;
  } else if (strcmp(kSortValue, PARAM_TYPE) == 0) {
    return (char *) PARAM_TYPE;
  }
  fprintf(stderr, "Invalid sorting type");
  return NULL;
}

struct ConfigStruct ParseConfigFile() {
  FILE *file;
  char *line = NULL;
  size_t mem_size = 0;
  const char *kPathToConfig = "config.conf";
  struct ConfigStruct config_data;
  config_data.port = 0;
  file = fopen(kPathToConfig, "r");
  if (file != NULL) {
    while (getline(&line, &mem_size, file) != -1) {
      if (strstr(line, "port") != NULL) {
        config_data.port = (uint16_t) atoi(line + 4);
      }
      if (strstr(line, "path") != NULL) {
        config_data.path_to_folder = strdup(line + 5);
      }
    }
    fclose(file);
  }
  return config_data;
}