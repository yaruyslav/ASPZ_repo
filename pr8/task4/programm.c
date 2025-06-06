#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int pid;
  pid = fork();
  printf("%d\n", pid);
}