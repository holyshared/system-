#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int safe_read_string(int fd, void *buf, int len) {
  int total;
  ssize_t ret;

  while(len != 0 && (ret = read(fd, buf, len)) != 0) {
    if (ret == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("read");
      return -1;
    }
    len -= ret;
    buf += ret;
    total += ret;
  }
  return total;
}

int main() {
  int fd;
  int total;
  char buf[BUFSIZ];

  fd = open("./fixture.log", O_RDONLY);

  if (fd == -1) {
    perror("read");
    return 0;
  }
  total = 0;

  do {
    char rbuf[BUFSIZ];
    memset(rbuf, '\0', BUFSIZ);
    total = safe_read_string(fd, rbuf, BUFSIZ);
    strcat(buf, rbuf);
  } while (total > 0);

  printf("%s\n", buf);

  close(fd);
  return 0;
}
