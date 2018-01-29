#include <unistd.h> // execv()
#include <stdio.h>  // perror()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

int main() {
  char *const argv[] = {"/bin/ls", "-l", NULL};
  execv(argv[0], argv);
  perror("Return from execv() not expected");
  exit(EXIT_FAILURE);
}
