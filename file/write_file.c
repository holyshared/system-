#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

ssize_t safe_write_string(int fd, void *buf, size_t len) {
  ssize_t total = 0;

  while (len > 0) {
    ssize_t ret = write(fd, buf, len);

    if (ret < 0 && errno == EINTR) {
      continue;
    }

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
  char *buf = "text";
  int fd = open("test.log", O_WRONLY);

  if (fd == -1) {
    perror("write");
    return 0;
  }

  ssize_t ret = safe_write_string(fd, buf, strlen(buf));
  printf("%zd\n", ret);

  close(fd);
  return 0;
}
