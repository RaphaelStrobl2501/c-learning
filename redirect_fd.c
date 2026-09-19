#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
  pid_t pid = fork();
  if (pid == -1)
  {
    printf("Error while forking\n");
    return 1;
  }
  
  if (pid == 0)
  {
    printf("On the terminal\n");
    int file = open("testfile", O_WRONLY | O_CREAT, 0777);
    if (file == -1)
    {
      printf("Not able to open the file\n");
      return 2;
    }
    dup2(file, STDOUT_FILENO);
    close(file);
    printf("In the file\n");
  }
  else
  {
    waitpid(pid, NULL, 0);
  }

  return 0;
}