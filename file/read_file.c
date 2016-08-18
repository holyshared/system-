#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void read_bytes(int fd, int len) {
  ssize_t ret;
  unsigned long buf;
  int errno;

  while(len != 0 && (ret = read(fd, &buf, len)) != 0) {
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

  fd = open("./fixture.log", O_RDONLY);

  if (fd == -1) {
    perror("read");
    return 0;
  }
  read_bytes(fd, 10);
  close(fd);
  return 0;
}
