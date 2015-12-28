#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Our old friend from ex17
void die(const char *message)
{
  if(errno)
    {
      perror(message);
    }else
    {
      printf("ERROR: %s\n", message);
    }

  exit(1);
}

// A typedef creates a fake type, in this case for a fxn pointer
typedef int (*compare_cb)(int a, int b);

// A classic bubble sort fxn uses the compare_cb to do the sorting.

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
  int temp = 0;
  int i = 0;
  int j = 0;
  int *target = malloc(count * sizeof(int));

  // If pointer to target is NULL
  if(!target)
    {
      die("Memory error.");
    }

  memcpy(target, numbers, count * sizeof(int));

  for(i = 0; i < count; i++)
    {
      for(j = 0; j < count - 1; j++)
	{
	  // What? We haven't even defned an output for cmp
	  if(cmp(target[j], target[j + 1]) > 0)
	    {
	      // Swap target[j] and target[j + 1]
	      temp = target[j + 1];
	      target[j + 1] = target[j];
	      target[j] = temp;
	    }
	}
    }

  return target;
}

// Why not int pointers?
// These are all of type compare_cb
int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strage_order(int a, int b)
{
  if(a == 0 || b == 0)
    {
      return 0;
    }else
    {
      return a % b;
    }
}

// Used to test that we are sorting things correctly
void test_sorting(int *numbers, int count, compare_cb cmp)
{
  int i = 0;
  int *sorted = bubble_sort(numbers, count, cmp);

  // If sorted == NULL
  if(!sorted)
    {
      die("Failed to sort as requested.");
    }

  for(i = 0; i < count; i++)
    {
      printf("%d ", sorted[i]);
    }

  printf("\n");

  free(sorted);

  unsigned char *data = (unsigned char *)cmp;

  for(i = 0; i < 25; i++)
    {
      printf("%02x:", data[i]);
    }
  
  printf("\n");
}

int main(int argc, char *argv[])
{
  if(argc < 2)
    {
      // This usage message is no bueno
      die("USAGE: ex18 4 3 1 5 6");
    }

  int count = argc - 1;
  int i = 0;
  // What?
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));
  // If numbers == NULL
  if(!numbers)
    {
      die("Memory error.");
    }

  for(i = 0; i < count; i++)
    {
      numbers[i] = atoi(inputs[i]);
    }

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strage_order);

  free(numbers);

  return 0;
}
