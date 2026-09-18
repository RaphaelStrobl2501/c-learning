#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int arr = { 1, 2, 3, 4, 5, 6, 7 };
  int arrSize = sizeof(arr) / sizeof(int);

  int fd[2];
  if (pipe(fd) == -1)
  {
    printf("Error while creating the pipes\n");
    return 1;
  }

  int id = fork();
}