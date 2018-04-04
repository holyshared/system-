#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int status;

  pid_t c_pid = fork();

  if (c_pid == 0) {
    printf("Child process. id=%d\n", c_pid);
    sleep(5);
  // parent process
  } else if (c_pid != -1) {
    pid_t pid = getpid();
    printf("Parent process. id=%d\n", pid);
    printf("Child process. id=%d\n", c_pid);
    wait(&status);
    printf("Parent process finish\n");
  } else {
    printf("Fork failed\n");
  }

  printf("%s\n", "main\n");
  return 0;
}
