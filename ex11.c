#include <stdio.h>

int main(int argc, char *argv[])
{
  // go through each string in argv
  int i = argc;
  while(i > 0)
    {
      printf("arg %d: %s\n", argc - i + 1, argv[argc - i]);
      i--;
    }

  // making array of strings
  char *states[] =
    {
      "California", "Oregon",
      "Washington", "Texas"
    };

  int num_states = 4;
  i = num_states; // watch for this
  while(i > 0)
    {
      printf("state %d: %s\n", num_states - i + 1, states[num_states - i]);
      i--;
    }

  return 0;
}
