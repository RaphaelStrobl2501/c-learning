#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(void)
{
  int arr[3];

  int fd = open("fifofile", O_RDONLY);
  if (fd == -1)
  {
    printf("Error while opening the file\n");
    return 2;
  }
  if (read(fd, arr, sizeof(int) * 3) == -1)
  {
    printf("Error while reading the file\n");
    return 3;
  }
  close(fd);

  int sum = 0;
  for (size_t i = 0; i < 3; i++)
  {
    sum += arr[i];
  }

  printf("Sum is: %d\n", sum);
  


  return 0;
}
