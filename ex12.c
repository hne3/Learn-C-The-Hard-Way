#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  if(argc == 1)
    {
      printf("You only have one argument!\n");
    }else if(argc > 1 && argc < 4)
    {
      printf("Here's your arguments:\n");

      // Fancy use of ; learned in previous example
      // EDIT: This does not work
      // Fancy use of for loop structure learned in
      // previous example
      for(i = 0; i < argc; i++)
	{
	  printf("%s\n", argv[i]);
	}

      printf("\n");
    }else
    {
      printf("You have too many arguments :(\n");
    }

  return 0;
}
