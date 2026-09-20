#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
  pid_t pid = fork();
  if (pid == -1)
    return 1;

  if (pid == 0)
  {
    while (1)
    {
      printf("Output\n");
      usleep(100000);
    }
  }
  else
  {
    kill(pid, SIGSTOP);
    int t = 0;
    do
    {
      printf("How many seconds?\n");
      scanf("%d", &t);
      if (t > 0)
      {
        kill(pid, SIGCONT);
        sleep(t);
        kill(pid, SIGSTOP);
      }
    } while (t > 0);

    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
    
  }

  return 0;
}