#include <stdio.h>

#define SUCCESSFUL 0
#define FAILED -1

struct user {
  char name[100];
  char password[32];
};

ssize_t write_users(struct user *users, int size, FILE *out) {
  int total = size;

  while (total > 0) {
    ssize_t wrote_size = fwrite(users, sizeof(struct user), total, out);

    if (wrote_size <= 0) {
      return -1;
    }

    total -= wrote_size;
    users += wrote_size;
  }

  return 0;
}

ssize_t read_users(struct user *users, int size, FILE *in) {
  int total = size;

  while (total > 0 && feof(in) == 0) {
    ssize_t readed_size = fread(users, sizeof(struct user), total, in);

    if (readed_size <= 0) {
      return -1;
    }

    total -= readed_size;
    users += readed_size;
  }

  return 0;
}

ssize_t write_all_users(struct user *users, int total) {
  FILE *out = fopen("users", "w");
  ssize_t ret = write_users(users, total, out);
  fclose(out);
  return ret;
}

ssize_t read_all_users(struct user *users, int total) {
  FILE *in = fopen("users", "r");
  ssize_t ret = read_users(users, total, in);
  fclose(in);
  return ret;
}

int main() {
  ssize_t ret;

  struct user output_users[] = {
    { "User1", "password1" },
    { "User2", "password2" },
    { "User3", "password3" }
  };

  int total = (sizeof(output_users) / sizeof(struct user));
  ret = write_all_users(output_users, total);

  if (ret == -1) {
    printf("output failed!!");
    return FAILED;
  }

  struct user input_users[3];
  int read_size = (sizeof(input_users) / sizeof(struct user));

  if (read_all_users(input_users, read_size) == -1) {
    printf("output failed!!");
    return FAILED;
  }

  int pos = 0;

  while (read_size > pos) {
    printf("name=%s\n", input_users[pos].name);
    printf("password=%s\n", input_users[pos].password);
    pos++;
  }

  return SUCCESSFUL;
}
