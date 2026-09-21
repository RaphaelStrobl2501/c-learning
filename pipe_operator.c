#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int fd[2];
  if (pipe(fd) == -1)
    return 1;

  pid_t pid1 = fork();
  if (pid1 < 0)
    return 2;

  if (pid1 == 0)
  {
    // redirect stdout to fd[1]
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if (execlp("ping", "ping", "-c", "5", "google.com", NULL) == -1)
      return 3;
  }
  // no need for an else here because child process will not come back
  pid_t pid2 = fork();
  if (pid2 < 0)
    return 2;
  if (pid2 == 0)
  {
    // redirect stdin to fd[0]
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
    if (execlp("grep", "grep", "round-trip", NULL) == -1)
      return 4;
  }
  // close the main process pipes
  close(fd[0]);
  close(fd[1]);

  waitpid(pid2, NULL, 0);
  waitpid(pid1, NULL, 0);
  
  return 0;
}