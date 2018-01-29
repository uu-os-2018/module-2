#include <stdio.h>  // perror()
#include <stdlib.h> // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> // fork()

int main(void) {

  pid_t pid;

  switch (pid = fork()) {

  case -1:
    // On error fork() returns -1.
    perror("fork failed");
    exit(EXIT_FAILURE);

  case 0:
    // On success fork() returns 0 in the child.

    // Add code for the child process here.

    exit(EXIT_SUCCESS);

  default:
    // On success fork() returns the pid of the child to the parent.

    // Add code for the parent process here.

    exit(EXIT_SUCCESS);
  }
}
