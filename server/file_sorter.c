#include "file_sorter.h"

const int kMinSize = 200;

int NameComparator(const void *a, const void *b) {
  return strcmp(((struct FileStruct *) a)->file_name, ((struct FileStruct *) b)->file_name);
}
int TimeComparator(const void *a, const void *b) {
  return (int) ((((struct FileStruct *) a)->modified) - (((struct FileStruct *) b)->modified));
}

int TypeComparator(const void *a, const void *b) {
  return NameComparator(a, b);
}

void SortFileStructureBy(__compar_fn_t (*compare)(int), struct FileStruct *fs, size_t size) {
  qsort(fs, size, (size_t) sizeof(struct FileStruct), (__compar_fn_t) compare);
}

void SortFileStructureByTime(struct FileStruct *fs, size_t size) {
  SortFileStructureBy((__compar_fn_t (*)(int)) TimeComparator, fs, size);
}

void SortFileStructureByType(struct FileStruct *fs, size_t size) {
  SortFileStructureBy((__compar_fn_t (*)(int)) TypeComparator, fs, size);
}
void SortFileStructureByName(struct FileStruct *fs, size_t size) {
  SortFileStructureBy((__compar_fn_t (*)(int)) NameComparator, fs, size);
}

const char *GetFileExtension(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename) return "";
  return dot + 1;
}

struct FileStruct *LookDir(char *dir, int *size) {
  int i = 0;
  int m_size = kMinSize;

  struct FileStruct *file_struct = (struct FileStruct *) malloc(sizeof(struct FileStruct) * m_size);

  DIR *dir_pointer;
  struct dirent *entry;
  struct stat file_stat;
  if ((dir_pointer = opendir(dir)) == NULL) {
    fprintf(stderr, "Cannot open directory, possible reason NEW LINE symbol in the config file(path): %s\n", dir);
  }
  chdir(dir);
  while ((entry = readdir(dir_pointer)) != NULL) {
    lstat(entry->d_name, &file_stat);
    if (S_ISDIR(file_stat.st_mode)) {
      continue;
    }
    struct FileStruct *f = malloc(sizeof(struct FileStruct));
    f->file_name = entry->d_name;
    f->file_type = GetFileExtension(entry->d_name);
    f->modified = file_stat.st_ctime;

    file_struct[i] = *f;

    if ((i + 1) > m_size) {
      m_size = (m_size + kMinSize);
      file_struct = (struct FileStruct *) realloc(file_struct, sizeof(file_struct) * m_size);
    }

    i++;
  }
  chdir("..");
  closedir(dir_pointer);

  *size = i;

  return file_struct;
}