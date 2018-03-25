#include <stdio.h>

#define SUCCESSFUL 0
#define FAILED -1

struct user {
  char name[100];
  char password[32];
};

ssize_t write_users(struct user *users, int size, FILE *out) {
  ssize_t done_size;
  int total = size;

  while (total > 0) {
    done_size = fwrite(&users, sizeof(struct user), 1, out);

    printf("done = %zu\n", done_size);

    if (done_size <= 0) {
      return -1;
    }
    total--;
  }

  return 0;
}

int main() {
  FILE *out;
  ssize_t ret;

  struct user users[] = {
    { "User1", "password1" },
    { "User2", "password2" },
    { "User3", "password3" }
  };
  int total = (sizeof(users) / sizeof(struct user));

  out = fopen("users", "w");

  ret = write_users(&users, total, out);

  if (ret == -1) {
    printf("output failed!!");
    return FAILED;
  }

  fclose(out);

  return SUCCESSFUL;
}
