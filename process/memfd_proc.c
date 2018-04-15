#include <sys/syscall.h>
#include <linux/memfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * int memfd_create(const char *name, unsigned int flags);
 */
static int memfd_create(const char *name, unsigned int flags) {
  return syscall(SYS_memfd_create, name, flags);
}

int main() {
  int fd = memfd_create("shared", MFD_ALLOW_SEALING);

  if (fd == -1) {
    printf("print error string by strerror: %s\n", strerror(errno));
    return -1;
  }

  ssize_t len;

  if (ftruncate(fd, len) == -1) {
    printf("print error string by strerror: %s\n", strerror(errno));
    return -1;
  }

  printf("success!!\n");

  exit(EXIT_SUCCESS);
}
