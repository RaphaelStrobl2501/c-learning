#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(void)
{
  int arr[3] = { 1, 2, 10 };

  if (mkfifo("fifofile", 0666) == -1)
  {
    if (errno != EEXIST)
    {
      printf("Failed to create fifo file\n");
      return 1;
    }
  }

  int fd = open("fifofile", O_WRONLY);
  if (fd == -1)
  {
    printf("Error while opening the file\n");
    return 2;
  }
  if (write(fd, arr, sizeof(int) * 3) == -1)
  {
    printf("Error while writing to the fd\n");
    return 3;
  }
  close(fd);
  


  return 0;
}