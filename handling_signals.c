#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_sigtstp(int sig)
{
  printf("Stop not allowed\n");
}

void handle_sigcont(int sig)
{
  printf("Input number: ");
  fflush(stdout);
}

int main(void)
{
  struct sigaction sa;
  sa.sa_handler = &handle_sigcont;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGCONT, &sa, NULL);

  // signal works different on different versions on linux so use sigaction
  // signal(SIGTSTP, &handle_sigtstp);

  int x = 0;
  printf("Input: ");
  scanf("%d", &x);
  printf("Result: %d\n", x * 2);

  return 0;
}