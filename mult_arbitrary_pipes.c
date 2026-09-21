#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 10

int main(void)
{
  int fd[NUM_PROCESSES + 1][2];
  for (int i = 0; i < NUM_PROCESSES + 1; i++)
  {
    if (pipe(fd[i]) == -1)
      return 1;
  }

  for (int i = 0; i < NUM_PROCESSES; i++)
  {
    pid_t pid = fork();
    if (pid < 0)
      return 2;
    if (pid == 0)
    {
      for (int j = 0; j < NUM_PROCESSES + 1; j++)
      {
        if (i != j)
        {
          close(fd[j][0]);
        }
        if (i + 1 != j)
        {
          close(fd[j][1]);
        }
      }

      int x = 0;
      if (read(fd[i][0], &x, sizeof(int)) == -1)
        return 3;
      x++;
      if (write(fd[i + 1][1], &x, sizeof(int)) == -1)
        return 4;

      close(fd[i][0]);
      close(fd[i + 1][1]);
      return 0;
    }
  }

  for (int i = 0; i < NUM_PROCESSES + 1; i++)
  {
    if (i != NUM_PROCESSES)
    {
      close(fd[i][0]);
    }
    if (i != 0)
    {
      close(fd[i][1]);
    }
  }
  

  int x = 1;
  if (write(fd[0][1], &x, sizeof(int)) < 0)
    return 3;
  close(fd[0][1]);
  if (read(fd[NUM_PROCESSES][0], &x, sizeof(int)) < 0)
    return 3;
  close(fd[NUM_PROCESSES][0]);

  printf("Result is %d\n", x);

  for (int i = 0; i < NUM_PROCESSES; i++)
  {
    wait(NULL);
  }
  

  return 0;
}