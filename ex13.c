#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc != 2)
    {
      printf("ERROR: You need one argument.\n");
      // this is how you abort a program
      return 1;
    }

  int i = 0;
  for(i = 0; argv[1][i] != '\0'; i++)
    {
      char letter = argv[1][i];
      // Compiler marks where switch statement starts
      // We call this location Y
      // Evaluates switch(letter) to come up with number (argv[1][i])
      switch(letter)
	{
	  // Compiler translates these case switches into faraway locations
	  // So this is located at location Y + 'A'
	  // If too far, adjusts to Y + default
	  // Then jumps to that location and execuutes code
	  // This is why we use break
	  // When it hits break, it exits the switch statement
	case 'a':
	case 'A':
	  printf("%d: 'A'\n", i);
	  break;

	case 'e':
	case 'E':
	  printf("%d: 'E'\n", i);
	  break;

	case 'i':
	case 'I':
	  printf("%d: 'I'\n", i);
	  break;

	case 'o':
	case 'O':
	  printf("%d: 'O'\n", i);
	  break;

	case 'u':
	case 'U':
	  printf("%d: 'U'\n", i);
	  break;

	case 'y':
	case 'Y':
	  if(i > 2)
	    {
	      // It's only sometimes y
	      printf("%d: 'Y'\n", i);
	    }
	  break;

	default:
	  printf("%d: %c is not a vowel\n", i, letter);
	}
    }

  return 0;
}
