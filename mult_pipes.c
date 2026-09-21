#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PIPES 3
#define NUM_PROCESSES 3

int main(void)
{
  int fd[NUM_PIPES][2];
  for (int i = 0; i < NUM_PIPES; i++)
  {
    if (pipe(fd[i]) == -1)
      return 1;
  }
  pid_t pid1 = fork();
  if (pid1 == -1)
    return 2;
  if (pid1 == 0)
  {
    for (int i = 0; i < NUM_PIPES; i++)
    {
      for (int j = 0; j < 2; j++)
      {
        if (!((i == 0 && j == 0) || (i == 1 && j == 1)))
        {
          close(fd[i][j]);
        }
      }
    }
    
    int x = 0;
    if (read(fd[0][0], &x, sizeof(int)) < 0)
      return 3;
    close(fd[0][0]);
    x++;
    if (write(fd[1][1], &x, sizeof(int)) < 0)
      return 3;
    close(fd[1][1]);

    return 0;
  }
  else
  {
    pid_t pid2 = fork();
    if (pid2 == -1)
      return 1;
    if (pid2 == 0)
    {
      for (int i = 0; i < NUM_PIPES; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          if (!((i == 1 && j == 0) || (i == 2 && j == 1)))
          {
            close(fd[i][j]);
          }
        }
      }

      int x = 0;
      if (read(fd[1][0], &x, sizeof(int)) < 0)
        return 3;
      close(fd[1][0]);
      x++;
      if (write(fd[2][1], &x, sizeof(int)) < 0)
        return 3;
      close(fd[2][1]);
      
      return 0;
    }
    else
    {
      for (int i = 0; i < NUM_PIPES; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          if (!((i == 0 && j == 1) || (i == 2 && j == 0)))
          {
            close(fd[i][j]);
          }
        }
      }

      int x = 1;
      if (write(fd[0][1], &x, sizeof(int)) < 0)
        return 3;
      close(fd[0][1]);
      if (read(fd[2][0], &x, sizeof(int)) < 0)
        return 3;
      close(fd[2][0]);

      printf("Result is %d\n", x);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
  }

  return 0;
}