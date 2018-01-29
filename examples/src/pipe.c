/*

  A small example program you can use to experiment with basic pipe behavior.

  1) A pipe is created.
  2) N integers are written one by one to the pipe.
  3) N integers are read from the pipe.

  Experiment to find out what happens when:

   - Writing to a pipe with no open read descriptors?
   - Reading from an empty pipe with open write descriptor(s)?

   2016-11-29

   First version by Karl Marklund <karl.marklund@it.uu.se>.

*/

#include <signal.h> // signal()
#include <stdio.h>  // printf()
#include <unistd.h> // getpid()
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

// Flags set to 1 by signal handler when receiving the SIGPIPE signal.
volatile sig_atomic_t SIGNAL = 0;

// Numbers of integers to be written to and read from the pipe.
#define N 3

// Signal handler.
void sigpipe_handler(int sig) {
  SIGNAL = sig;
}


int main(){

  // File descriptors to the pipe:
  int pfd[2];
  // Array of integer to be written to the pipe.
  int src[N] = {127, 155, 777};
  // This variable will hold the result when reading an integer from the pipe.
  int dst;
  // Number of bytes read from the pipe.
  int n;


  // Create the pipe and check for errors.
  if (pipe(pfd) < 0) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  };

  // On success:
  //    pfd[0] = read descriptor
  //    pfd[1] = write descriptor


  // TODO 1: What happens if you uncomment the line behlow and why?
  // close(pfd[0]);

  // Register the function sigpipe_handler as the handler for the SIGPIPE signal. 
  // TODO 2: What happens and why if you comment out the line below?
  signal(SIGPIPE, sigpipe_handler);


  // Write the N integers to the pipe.

  for (int i = 0; i < N; i++) {

    // Write one integer to the pipe.
    n = write(pfd[1], &src[i], sizeof(int));

    // Check if the write caused a SIGPIPE.
    if (SIGNAL == SIGPIPE) {
      fprintf(stderr, "SIGPIPE detected!!!\n");
      exit(EXIT_FAILURE);
    }

    // Check for errors.
    if (n < 0) {
      perror("Writing to pipe");
      exit(EXIT_FAILURE);
    }

    printf("Integer %d (%d bytes) written to the pipe.\n", src[i], n);

  }

  printf("\n");

  // TODO 3: What happens if you comment out the below line out and why?
  close(pfd[1]);

  // Read integers from the pipe until the pipe is empty and no open write descriptors (n == 0).

  while ( (n = read(pfd[0], &dst, sizeof(dst))) ) {

    // Check for errors.
    if (n < 0)  {
      perror("Read from pipe failed");
      exit(EXIT_FAILURE);
    }

    printf("Integer %d (%d bytes) read from the pipe.\n", dst, n);

  }

  // No more data in the pipe make read() return 0 (EOF).
  printf("\n0 bytes read from the pipe (EOF).\n");
}
