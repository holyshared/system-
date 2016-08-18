#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void read_bytes(int fd, char *buf, int len) {
  ssize_t ret;
  int errno;

  while(len != 0 && (ret = read(fd, buf, len)) != 0) {
    if (ret == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("read");
      break;
    }
    len -= ret;
    buf += ret;
  }
}

int main() {
  int fd;
  char buf[256];

  fd = open("./fixture.log", O_RDONLY);

  if (fd == -1) {
    perror("read");
    return 0;
  }
  read_bytes(fd, buf, sizeof(buf));
  printf("%s\n", buf);

  close(fd);
  return 0;
}
