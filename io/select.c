#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define TIMEOUT 5

int main() {
  struct timeval tv;
  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  tv.tv_sec = TIMEOUT;
  tv.tv_usec = 0;

  int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

  if (ret == -1) {
    perror("select");
    return 1;
  } else if (!ret) {
    printf("%d seconds elapsed.\n", TIMEOUT);
    return 0;
  }

  if (FD_ISSET(STDIN_FILENO, &readfds)) {
    char buf[BUFSIZ + 1];

    ssize_t len = read(STDIN_FILENO, buf, BUFSIZ);

    if (len == -1) {
      perror("read");
      return 1;
    }

    if (len) {
      buf[len] = '\0';
      printf("read: %s\n", buf);
    }

    return 0;
  }

  fprintf(stderr, "this should not happen!\n");
  return 1;
}
