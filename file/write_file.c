#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

ssize_t safe_wrtie_string(int fd, void *buf, ssize_t len) {
  ssize_t ret;
  ssize_t total;

  total = 0;

  while (len > 0) {
    ret = write(fd, buf, len);

    if (ret < 0 && ret == EINTR) {
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
  int fd;
  char *buf = "text";
  ssize_t ret;

  fd = open("test.log", O_WRONLY);

  if (fd == -1) {
    perror("write");
    return 0;
  }

  ret = safe_wrtie_string(fd, buf, strlen(buf));
  printf("%zd\n", ret);

  close(fd);
  return 0;
}
