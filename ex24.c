#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor
  {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
  } EyeColor;

const char *EYE_COLOR_NAMES[] =
  {
    "Blue", "Green", "Brown",
    "Black", "Other"
  };

typedef struct Person
{
  int age;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
  EyeColor eyes;
  float income;
} Person;

int main(int argc, char *argv[])
{
  Person you = {.age = 0};
  
  // Extra credit: take everything as arguments
  if(argc != 6)
    {
      log_err("USAGE: ex24 firstname lastname age eyecolor income");
      return 1;
    }
  check(argv[1] != NULL, "Failed to read first name.");
  check(sizeof(argv[1]) < sizeof(char) * MAX_DATA, "First name too long.");
  strcpy(you.first_name, argv[1]);

  check(argv[2] != NULL, "Failed to read last name.");
  check(sizeof(argv[2]) < sizeof(char) * MAX_DATA, "Last name too long.");
  strcpy(you.last_name, argv[2]);
  
  check(atoi(argv[3]) > 0, "You must enter an age.");
  you.age = atoi(argv[3]);

  check(atoi(argv[4]) > 0, "You must enter an integer value 1 - 5.");
  check(atoi(argv[4]) <= OTHER_EYES, "You must enter an integer value 1 - 5."); 
  you.eyes = atoi(argv[4]) - 1;

  check(atof(argv[5]) > 0, "You must enter a salary.");
  you.income = atof(argv[5]);
  /*char *in = NULL;

  printf("What's your first name? ");
  in = fgets(you.first_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read first name.");

  printf("What's your last name? ");
  in = fgets(you.last_name, MAX_DATA - 1, stdin);
  check(in != NULL, "Failed to read last name.");

  printf("How old are you? ");
  // fscanf must take a pointer to you.age
  // This is a good example of using a pointer as an "out parameter"
  int rc = fscanf(stdin, "%d", &you.age);
  check(rc > 0, "You have to enter a number.");

  printf("What color are your eyes?\n");
  // Below can be done because enums have a number value
  for(i = 0; i <= OTHER_EYES; i++)
    {
      printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
  printf("> ");

  int eyes = -1;
  rc = fscanf(stdin, "%d", &eyes);
  check(rc > 0, "You have to enter a number.");

  you.eyes = eyes - 1;
  check(you.eyes <= OTHER_EYES && you.eyes >= 0, "That's not a valid number.");

  printf("How much do you make per hour? ");
  rc = fscanf(stdin, "%f", &you.income);
  check(rc > 0, "Enter a floating point number.");*/

  printf("---- RESULTS ----\n");

  printf("First Name: %s\n", you.first_name);
  printf("Last Name: %s\n", you.last_name);
  printf("Age: %d\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %f\n", you.income);

  return 0;

 error:

  return -1;
}
