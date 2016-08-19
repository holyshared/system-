#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

ssize_t safe_read_string(int fd, void *buf, ssize_t len) {
  ssize_t ret;
  ssize_t total;

  total = 0;

  while(len > 0) {
    ret = read(fd, buf, len);

    //Interrupted system call
    if (ret < 0 && errno == EINTR) {
      continue;
    }

    //EOF or Error
    if (ret <= 0) {
      return ret;
    }

    len -= ret;
    buf += ret;
    total += ret;
  }

  return total;
}

int main() {
  int fd;
  ssize_t total;
  char buf[BUFSIZ];

  fd = open("./fixture.log", O_RDONLY);

  if (fd == -1) {
    perror("read");
    return 0;
  }
  total = 0;

  do {
    char rbuf[BUFSIZ];
    memset(rbuf, '\0', sizeof(rbuf));
    total = safe_read_string(fd, rbuf, sizeof(rbuf));
    strcat(buf, rbuf);
  } while (total > 0);

  printf("%s\n", buf);

  close(fd);
  return 0;
}
