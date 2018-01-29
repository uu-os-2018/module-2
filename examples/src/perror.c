#include <fcntl.h> // open()
#include <stdio.h> // printf()

int main (void) {
  int fd;
  char* name = "missing-file.txt";

  fd = open(name, O_RDONLY);

  printf("fd = %d\n", fd);

  if (fd == -1) {
    perror(name);
  }

}
