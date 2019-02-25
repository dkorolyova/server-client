#ifndef SOCKET_FILE_SORTER_H
#define SOCKET_FILE_SORTER_H

#include <dirent.h>
#include <stdio.h>
#include <zconf.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

struct FileStruct {
  const char *file_name;
  const char *file_type;
  long modified;
};

struct FileStruct* LookDir(char *dir, int *size);
const char *GetFileExtension(const char *filename);
void SortFileStructureBy(__compar_fn_t (*compare)(int), struct FileStruct *fs, size_t size);
void SortFileStructureByType(struct FileStruct *fs, size_t size);
void SortFileStructureByTime(struct FileStruct *fs, size_t size);
void SortFileStructureByName(struct FileStruct *fs, size_t size);
int TypeComparator(const void *a, const void *b);
int TimeComparator(const void *a, const void *b);
int NameComparator(const void *a, const void *b);

#endif //SOCKET_FILE_SORTER_H
