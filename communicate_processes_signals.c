#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int x = 0;

void handle_sigusr1(int sig)
{
  if (x == 0)
    printf("This is a hint\n");
}

int main(void)
{
  pid_t pid = fork();
  if (pid == -1)
    return 1;

  if (pid == 0)
  {
    sleep(5);
    // SIGUSR1 is user defined and can be modified
    kill(getppid(), SIGUSR1);
  }
  else
  {
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = &handle_sigusr1;
    sigaction(SIGUSR1, &sa, NULL);

    printf("What is 2*5? ");
    scanf("%d", &x);
    if (x == 10)
      printf("Right\n");
    else
      printf("False\n");
    
    waitpid(pid, NULL, 0);
  }

  return 0;
}