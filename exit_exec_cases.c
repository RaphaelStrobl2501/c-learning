#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid = fork();
  if (pid == -1)
    return 1;

  if (pid == 0)
  {
    // what if the program ls is found and executed but theres an error at executing it for example the arguments are wrong
    // err returns -1 if the program stated couldnt be executed
    int err = execlp("ls", "ls", NULL);
    if (err == -1)
    {
      printf("Could not find the program to execute\n");
      return 2;
    }
  }
  else
  {
    // wstatus stores an information about how the child finished
    int wstatus;
    wait(&wstatus);
    // did the child return normally using return, exit? if not add some else if with more termination cases
    if (WIFEXITED(wstatus))
    {
      int status_code = WEXITSTATUS(wstatus);
      if (status_code == 0)
        printf("Success\n");
      else
        printf("Failure with status code %d\n", status_code);
    }
    // here can come 
    printf("Post processing\n");
  }

  return 0;
}