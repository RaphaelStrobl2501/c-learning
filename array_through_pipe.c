#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>


// child process should generate rand numbers and send them to the parent
// parent receives it and sums all up

int main(void)
{
  int fd[2];
  if (pipe(fd) == -1)
    return 2;
  pid_t pid = fork();
  if (pid == -1)
    return 1;
  
  if (pid == 0)
  {
    close(fd[0]);
    int arr[10] = {0};
    srand(time(NULL));
    // generate random number of elements between 1 and 9 inclusive
    int number_of_elements = rand() % 10 + 1;
    // fill array with random numbers
    for (int i = 0; i < number_of_elements; i++)
    {
      arr[i] = rand() % 11;
      printf("%d ", arr[i]);
    }
  
    // send the amount of elements so i know how much to read  
    if (write(fd[1], &number_of_elements, sizeof(int)) < 0)
      return 4;
    if (write(fd[1], arr, sizeof(int) * number_of_elements) < 0)
      return 3;
    close(fd[1]);
  }
  else
  {
    close(fd[1]);
    int number_of_elements = 0;
    int arr[10] = {0};
    if (read(fd[0], &number_of_elements, sizeof(int)) < 0)
      return 5;
    if (read(fd[0], arr, sizeof(int) * number_of_elements ) < 0)
      return 6;
    int sum = 0;
    for (int i = 0; i < number_of_elements; i++)
    {
      sum += arr[i];
    }
    printf("Result ist %d\n", sum);
    close(fd[0]);

    waitpid(pid, NULL, 0);
    
  }

  return 0;
}