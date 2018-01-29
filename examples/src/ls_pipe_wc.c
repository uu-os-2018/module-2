#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd[2];

  if (pipe(fd) == -1) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:

    // The child process will execute wc.

    // Close the pipe write descriptor.
    close(fd[WRITE]);

    // Redirect STDIN to read from the pipe.
    dup2(fd[READ], STDIN_FILENO);

    // Close the dangling pipe read descriptor.
    close(fd[READ]);

    // Execute wc
    execlp("wc", "wc", NULL);

  case -1:

    perror("fork() failed)");
    exit(EXIT_FAILURE);

  default:

    // The parent process will execute ls.

    // Close the pipe read descriptor.
    close(fd[READ]);

    // Redirect STDOUT to write to the pipe.
    dup2(fd[WRITE], STDOUT_FILENO);

    // Close the dangling pipe write descriptor.
    close(fd[WRITE]);

    // Execute ls -l
    execlp("ls", "ls", NULL);

  }

}
