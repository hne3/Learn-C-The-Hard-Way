#include <stdio.h>

int main(int argc, char *argv[])
{
  int numbers[4] = {0};
  int i, val= 0;
  char name[4] = {'a'};

  // first, print them out raw
  printf("numbers: %d %d %d %d\n",
	 numbers[0], numbers[1],
	 numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
	 name[0], name[1],
	 name[2], name[3]);

  printf("name: %s\n", name);

  // set up the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // set up the name
  name[0] = 'Z';
  name[1] = 'e';
  name[2] = 'd';
  name[3] = '\0';

  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
	 numbers[0], numbers[1],
	 numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
	 name[0], name[1],
	 name[2], name[3]);

  // big endian
  for(i = 0; i < 4; i++)
    {
      val = (val << 8) + name[i];
    }

  // little endian
  // can't quite figure out what's going wrong here
  int *n;
  n = &name;

  printf("big endian val: %d, little endian val: %d\n", val, *n);

  // print the name like a string
  printf("name: %s\n", name);

  // another way to use the name
  char *another = "Zed";

  printf("another: %s\n", another);

  printf("another each: %c %c %c %c\n",
	 another[0], another[1],
	 another[2], another[3]);

  return 0;
}
