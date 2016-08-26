#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

#define TIMEOUT 5

int main() {
  struct pollfd fds[2];
  struct pollfd in = { STDIN_FILENO, POLLIN };
  struct pollfd out = { STDOUT_FILENO, POLLOUT };

  fds[0] = in;
  fds[1] = out;

  int ret = poll(fds, 2, TIMEOUT * 1000);

  if (ret == -1) {
    perror("poll");
    return 1;
  }
  if (!ret) {
    printf("%d seconds elapsed.\n", TIMEOUT);
    return 0;
  }

  if (fds[0].revents & POLLIN) {
    printf("stdin is readable\n");
  }

  if (fds[1].revents & POLLOUT) {
    printf("stdout is writable\n");
  }

  return 0;
}
