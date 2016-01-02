/** WARNING: This code is fresh and potentially isn't correct yet. */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer)
{
  *out_string = calloc(1, max_buffer + 1);
  check_mem(*out_string);

  char *result = fgets(*out_string, max_buffer, stdin);
  check(result != NULL, "Input error.");

  return 0;

 error:
  if(*out_string)
    {
      free(*out_string);
    }
  // Why do we need to set this to null if we freed the memory already?
  *out_string = NULL;
  return -1;
}

int read_int(int *out_int)
{
  char *input = NULL;
  int rc = read_string(&input, MAX_DATA);
  check(rc == 0, "Failed to read number.");

  *out_int = atoi(input);

  free(input);
  return 0;

 error:
  if(input)
    {
      free(input);
    }
  return -1;
}

int print_custom(const char *fmt, ...)
{
  int i = 0;
  int counter = 0;
  
  char *final_string = calloc(1, MAX_DATA);
  char *segments = calloc(1, MAX_DATA);
  char *tmp = calloc(1, MAX_DATA);

  strcpy(tmp, fmt);
  segments = strtok(tmp, '%');
  tmp = NULL;
  
  va_list argp;
  va_start(argp, fmt);

  for(i = 0; fmt[i] != '\0'; i++)
    {
      if(fmt[i] == '%')
	{
	  i++;
	  switch(fmt[i])
	    {
	    case 'd':
	      strncpy(final_string, segments[counter], MAX_DATA);
	      sprintf(tmp, "%d", *va_arg(argp, int *));
	      strncat(final_string, tmp, MAX_DATA);
	    break;
	    case 's':
	      strncpy(final_string, segments[counter], MAX_DATA);
	      strncat(final_string, **va_arg(argp, char **), MAX_DATA);
	      break;
	    case 'c':
	      strncpy(final_string, segments[counter], MAX_DATA);
	      sprintf(tmp, "%c", *va_arg(argp, char *));
	      strncat(final_string, tmp, MAX_DATA);
	      break;
	    default:
	      log_err("Not a valid format.");
	      return 1;
	    }
	  counter++;
	}
      strncpy(final_string, segments[counter], MAX_DATA);
    }
  return 0;
}
int read_scan(const char *fmt, ...)
{
  int i = 0;
  int rc = 0;
  int *out_int = NULL;
  char *out_char = NULL;
  char **out_string = NULL;
  int max_buffer = 0;

  va_list argp;
  va_start(argp, fmt);

  for(i = 0; fmt[i] != '\0'; i++)
    {
      if(fmt[i] == '%')
	{
	  i++;
	  switch(fmt[i])
	    {
	    case '\0':
	      sentinel("Invalid format, you ended with %%.");
	      break;

	    case 'd':
	      out_int = va_arg(argp, int *);
	      rc = read_int(out_int);
	      check(rc == 0, "Failed to read int.");
	      break;

	    case 'c':
	      out_char = va_arg(argp, char *);
	      // What? Why do we need to get a char pointer from stdin?
	      *out_char = fgetc(stdin);
	      break;

	    case 's':
	      // Why not int *?
	      max_buffer = va_arg(argp, int);
	      out_string = va_arg(argp, char **);
	      rc = read_string(out_string, max_buffer);
	      check(rc == 0, "Failed to read string.");
	      break;

	    default:
	      sentinel("Invalid format.");
	    }
	} else
	{
	  fgetc(stdin);
	}
      // What does feof check for?
      check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

  va_end(argp);
  return 0;

 error:
  va_end(argp);
  return -1;
}

int main(int argc, char *argv[])
{
  char *first_name = NULL;
  char initial = ' ';
  char *last_name = NULL;
  int age = 0;

  printf("What's your first name? ");
  int rc = read_scan("%s", MAX_DATA, &first_name);
  check(rc == 0, "Failed to read first name.");

  printf("What's your initial? ");
  rc = read_scan("%c\n", &initial);
  check(rc == 0, "Failed to read initial.");

  printf("What's your last name? ");
  rc = read_scan("%s", MAX_DATA, &last_name);
  check(rc == 0, "Failed to read last name.");

  printf("How old are you? ");
  rc = read_scan("%d", &age);
  // Why don't we check here?

  printf("---- RESULTS ----\n");
  printf("First name: %s", first_name);
  printf("Initial: '%c'\n", initial);
  printf("Last name: %s", last_name);
  printf("Age: %d\n", age);
  print_custom("Hello\n");
  print_custom("Int test: %d\n", 2);
  print_custom("Char test: %c\n", 'c');
  print_custom("String test: %s\n", "hello");

  free(first_name);
  free(last_name);
  return 0;

 error:
  return -1;
}
