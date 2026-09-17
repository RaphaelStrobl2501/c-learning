#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 10

int main(void)
{
  int pids[PROCESS_NUM];
  int pipes[PROCESS_NUM + 1][2];
  for (int i = 0; i < PROCESS_NUM + 1; i++)
  {
    if (pipe(pipes[i]) == -1)
    {
      printf("Error while creating pipes\n");
      return 1;
    }
  }
  for (int i = 0; i < PROCESS_NUM; i++) // i is telling which child im in
  {
    pids[i] = fork();
    if (pids[i] == -1)
    {
      printf("Error while creating pipes\n");
      return 2;
    }
    if (pids[i] == 0)
    {
      // children
      for (int j = 0; j < PROCESS_NUM + 1; j++) // j is looping over all pipes
      {
        if (i != j) // close all pipes except the one where i == j
        {
          close(pipes[j][0]);
        }
        if (i + 1 != j) // close all pipes except the one where i + 1 == j
        {
          close(pipes[j][1]);
        }
      }
      int x = 0;
      if (read(pipes[i][0], &x, sizeof(int)) == -1)
      {
        printf("Error while reading\n");
        return 3;
      }
      printf("(%d) Got %d\n", i, x);
      x++;
      if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
      {
        printf("Error while writing\n");
        return 4;
      }
      printf("(%d) Sent %d\n", i, x);
      close(pipes[i][0]);
      close(pipes[i + 1][1]);
      return 0;
    }
  }

  // main process
  for (int i = 0; i < PROCESS_NUM + 1; i++)
  {
    if (i != PROCESS_NUM)
    {
      close(pipes[i][0]);
    }
    if (i != 0)
    {
      close(pipes[i][1]);
    }
  }
  int y = 10;
  if (write(pipes[0][1], &y, sizeof(int)) == -1)
  {
    printf("Error while reading\n");
    return 3;
  }
  printf("Sent out %d\n", y);
  if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
  {
    printf("Error while writing\n");
    return 4;
  }
  printf("Got back %d\n", y);

  close(pipes[PROCESS_NUM][0]);
  close(pipes[0][1]);
  
  for (int i = 0; i < PROCESS_NUM; i++)
  {
    wait(NULL);
  }
  


  return 0;
}