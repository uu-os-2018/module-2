#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Path to text file.
#define FILE "./data/data.txt"

// Number of bytes to read at a time.
#define N 4

int main() {

  // File descriptor.
  int  fd;

  // When reading from the file, store the read bytes in this buffer. To be able
  // to read N bytes and add a terminating NULL `\0` the size of the buffer must
  // be N + 1.

  char buffer[N+1];

  // Number of bytes actually read from the file, may be less than requested.
  int  n;

  // Open file for reading.
  fd = open(FILE, O_RDONLY);

  if (fd == -1) {
    perror("Open file");
    exit(EXIT_FAILURE);
  }

  printf("File %s open for reading using file descriptor %d.\n\n", FILE, fd);

  // Read n bytes at a time from file descriptor fd and store the read bytes in
  // buffer.

  while ((n = read(fd, buffer, N))) {

    // Check for error.
    if (n == - 1) {
      perror("Reading from file");
      exit(EXIT_FAILURE);
    }

    // Now n = number of bytes actually read. Note that n < N or N == 0.

    // NULL-terminate.
    buffer[n] = '\0';

    printf("Read %d bytes: %s", n, buffer);
  }

  printf("\nRead %d bytes (EOF)!\n", n);
}
