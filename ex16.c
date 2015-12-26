// For printf
#include <stdio.h>
// For assertions to make sure input is good
#include <assert.h>
// For malloc
#include <stdlib.h>
// For strdup
#include <string.h>

// Defines what constitutes a person
// Person will be a "compound data type"
// If using a pointer, use who->property
// If using an actual object, use who.property
struct Person
{
  char *name;
  int age;
  int height;
  int weight;
};

// Function to make creating a person easy
// Returns a pointer to the person created, not the person itself
struct Person *Person_create(char *name, int age, int height, int weight)
{
  struct Person *who = malloc(sizeof(struct Person));
  // Ensure malloc didn't return a null pointer
  assert(who != NULL);
  // Duplicate the string to make sure the struct actually owns it
  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
};

// For cleaning up
void Person_destroy(struct Person *who)
{
  // Ensure you're passing in a valid person
  assert(who != NULL);
  // Free up the chunks of memory we've used to store the values of the person
  // Need to seperately free name because we copied it with strdup
  free(who->name);
  free(who);
}

// Just prints out the properties of a person
// Should probably ensure you're passing in a valid person as well
void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  // make two people structures
  struct Person *joe = Person_create(
				     "Joe Alex", 32, 64, 140);

  struct Person *frank = Person_create(
				       "Frank Blank", 20, 72, 180);

  // Tells us where Joe's values are stored and prints out his properties
  printf("Joe is at memory location %p:\n", joe);
  Person_print(joe);
  // Same for Frank
  printf("Frank is at memory location %p:\n", frank);
  Person_print(frank);
  // Ages both of them and prints again
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
