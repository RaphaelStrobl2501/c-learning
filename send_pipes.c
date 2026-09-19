#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int p1[2]; // C-P
  int p2[2]; // P-C

  if (pipe(p1) == -1)
  {
    printf("Error while creating the pipe\n");
    return 1;
  }
  if (pipe(p2) == -1)
  {
    printf("Error while creating the pipe\n");
    return 1;
  }

  pid_t pid = fork();
  if (pid == -1)
  {
    printf("Error while forking\n");
    return 2;
  }

  if (pid == 0)
  {
    // childs process
    close(p1[0]);
    close(p2[1]);
    int x = 10;
    if (write(p1[1], &x, sizeof(int)) == -1)
    {
      printf("Error while writing\n");
      return 3;
    }

    if (read(p2[0], &x, sizeof(int)) == -1)
    {
      printf("Error while reading\n");
      return 4;
    }

    printf("x is %d\n", x);
  }
  else
  {
    // parents process
    close(p1[1]);
    close(p2[0]);
    int x = 0;
    if (read(p1[0], &x, sizeof(int)) == -1)
    {
      printf("Error while reading\n");
      return 4;
    }

    x *= 2;

    if (write(p2[1], &x, sizeof(int)) == -1)
    {
      printf("Error while writing\n");
      return 3;
    }
    
  }

  return 0;
}
