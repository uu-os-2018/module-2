#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <stdbool.h> // true, false

bool done = false;

int divide_by_zero() {
  int a = 1;
  int b = 0;
  return a / b;
}

void segfault() {
  int *ptr = NULL;
  *ptr = 42;
}

void signal_handler(int s) {
  switch(s) {
    case SIGFPE:
      fputs("Caught SIGFPE: arithmetic exception, such as division by zero.\n", stderr);
      exit(EXIT_FAILURE);
    case SIGSEGV:
      fputs("Caught SIGSEGV: segfault.\n", stderr);
      exit(EXIT_FAILURE);
      break;
    case SIGINT:
      fputs("Caught SIGINT: interactive attention signal, probably a ctrl+c.\n", stderr);
      break;
    case SIGUSR1:
      puts("Hello!");
      break;
  }
}

int main(void) {

  printf("My PID = %ld\n", (long) getpid());

  // Install signal handlers.

  // signal(SIGFPE,  signal_handler);

  // divide_by_zero();
  // segfault();

  // Wait until a signal is delivered.

  // pause();

  puts("I'm done!");

  exit(EXIT_SUCCESS);
}
