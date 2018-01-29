#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid()

int main(void) {

  printf(" CHILD <%ld> I'm alive and my PPID = %ld.\n",
       (long) getpid(), (long) getppid());

  printf(" CHILD <%ld> Press any key to make me terminate!\n",
         (long) getpid());

  getchar();

  printf(" CHILD <%ld> Goodbye!\n",
         (long) getpid());

  exit(127);
}
