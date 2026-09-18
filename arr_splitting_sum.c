#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
  int arrSize = sizeof(arr) / sizeof(arr[0]);
  int start = 0;
  int end = 0;

  int fd[2];
  if (pipe(fd) == -1)
  {
    printf("Error while creating the pipes\n");
    return 1;
  }

  int id1 = fork();
  if (id1 < 0)
  {
    printf("Error while forking\n");
    return 2;
  }

  if (id1 == 0)
  {
    // childs process
    close(fd[0]);
    start = 0;
    end = arrSize / 3;
    int sum = 0;

    for (int i = start; i < end; i++)
    {
      sum += arr[i];
    }
    write(fd[1], &sum, sizeof(int));
    close(fd[1]);

    return 0;
  }
  else
  {
    // parent process
    int id2 = fork();
    if (id2 < 0)
    {
      printf("Error while forking\n");
      return 2;
    }
    if (id2 == 0)
    {
      // childs process
      close(fd[0]);
      start = arrSize / 3;
      end = start + (arrSize / 3);
      int sum = 0;

      for (int i = start; i < end; i++)
      {
        sum += arr[i];
      }
      write(fd[1], &sum, sizeof(int));
      close(fd[1]);

      return 0;
    }
    else
    {
      close(fd[1]);
      int partial_sum1 = 0;
      int partial_sum2 = 0;
      read(fd[0], &partial_sum1, sizeof(int));
      read(fd[0], &partial_sum2, sizeof(int));
      close(fd[0]);

      start = 2 * (arrSize / 3);
      end = arrSize;
      int partial_sum3 = 0;

      for (int i = start; i < end; i++)
      {
        partial_sum3 += arr[i];
      }

      int total_sum = partial_sum1 + partial_sum2 + partial_sum3;
      printf("Total sum: %d\n", total_sum);

      waitpid(id1, NULL, 0);
      waitpid(id2, NULL, 0);
    }
  }

  return 0;

}