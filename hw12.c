#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[]) {

  DIR *dir;
  struct dirent *dent;
  struct stat sb;

  char name[50];
  if (argc > 1) {
    strcpy(name, argv[1]);
  }
  else {
    printf("Enter a valid directory.\n");
    scanf("%s", name); 
  }

  dir = opendir(name);
  if (dir == NULL) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  dent = readdir(dir);
  if (dent == NULL) {
    printf("%s\n", strerror(errno));
    return -1;
  }

  unsigned int bytes = 0;
  char dirs[500][100];
  char files[500][100];
  int i;
  int j;

  for (i = 0; i < 500; i++) {
    strcpy(dirs[i], " ");
    strcpy(files[i], " ");
  }

  i = 0;
  j = 0;

  while(dent || i > 498 || j > 498) {
    stat(dent->d_name, &sb);
    if (S_ISREG(sb.st_mode)) {
      strcpy(files[i], dent->d_name);
      i++;
    }
    else if (S_ISDIR(sb.st_mode)) {
      strcpy(dirs[j], dent->d_name);
      j++;
    }
    bytes += sb.st_size;
    dent = readdir(dir);
  }
  i = 0;

  printf("Statistics for directory:\n");
  printf("Total Directory size: %d Bytes\n", bytes);
  printf("Directories:\n");

  while(strcmp(dirs[i], " ")) {
    printf("\t%s\n", dirs[i]);
    i++;
  }

  i = 0;

  printf("\nRegular files:\n");

  while(strcmp(files[i], " ")) {
    printf("\t%s\n", files[i]);
    i++;
  }

  closedir(dir);

  return 0;
}
