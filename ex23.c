#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include "unroll.h"
#include <time.h>

int normal_copy(char *from, char *to, int count)
{
  clock_t start = clock(), diff;
  int i = 0;

  for(i = 0; i < count; i++)
    {
      to[i] = from[i];
    }

  diff = clock() - start;
  printf("Normal copy time: %ld ms\n", diff * 1000 / CLOCKS_PER_SEC);
  return i;
}

int duffs_device(char *from, char *to, int count)
{
  clock_t start = clock();
  clock_t diff;
  {
    int n = (count + 7) / 8;

    switch(count % 8)
      {
      case 0:
	do
	  {
	    *to++ = *from++;
	  case 7: *to++ = *from++;
	  case 6: *to++ = *from++;
	  case 5: *to++ = *from++;
	  case 4: *to++ = *from++;
	  case 3: *to++ = *from++;
	  case 2: *to++ = *from++;
	  case 1: *to++ = *from++;
	  } while(--n > 0);
      }
  }

  diff = clock() - start;
  printf("Duff's device time: %ld ms\n", diff * 1000 / CLOCKS_PER_SEC);
  
  return count;
}

int zeds_device(char *from, char *to, int count)
{
  clock_t start = clock();
  clock_t diff;
  {
    int n = (count + 7) / 8;

    switch(count % 8)
      {
      case 0:
      again: *to++ = *from++;

      case 7: *to++ = *from++;
      case 6: *to++ = *from++;
      case 5: *to++ = *from++;
      case 4: *to++ = *from++;
      case 3: *to++ = *from++;
      case 2: *to++ = *from++;
      case 1: *to++ = *from++;
	if(--n > 0) goto again;
      }
  }
  diff = clock() - start;
  printf("Zed's device time: %ld ms\n", (1000 * diff) / CLOCKS_PER_SEC);
  return count;
}

int valid_copy(char *data, int count, char expects)
{
  int i = 0;
  for(i = 0; i < count; i++)
    {
      if(data[i] != expects)
	{
	  log_err("[%d] %c != %c", i, data[i], expects);
	  return 0;
	}
    }
  return 1;
}

int duffs_device_32(char *from, char *to, int count)
{
  clock_t start = clock();
  clock_t diff;
  {
    int n = (count + 31) / 32;

    switch(count % 32)
      {
      case 0:
	do
	  {
	    *to++ = *from++;
	    SEVEN_AT_ONCE(3);
	    EIGHT_AT_ONCE(2);
	    EIGHT_AT_ONCE(1);
	    EIGHT_AT_ONCE(0);
	  } while(--n > 0);
      }
  }
  diff = clock() - start;
  printf("Duff's 32 device time: %ld ms\n", diff * 1000 / CLOCKS_PER_SEC);
  return count;
}

int main(int argc, char *argv[])
{
  char from[1000] = {'a'};
  char to[1000] = {'c'};
  int rc = 0;

  // setup from to have some stuff
  memset(from, 'x', 1000);
  // set it to a failure mode
  memset(to, 'y', 1000);
  check(valid_copy(to, 1000, 'y'), "Not initialized right.");

  // use normal copy
  rc = normal_copy(from, to, 1000);
  check(rc == 1000, "Normal copy failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Normal copy failed.");

  // reset
  memset(to, 'y', 1000);

  // duffs version
  rc = duffs_device(from, to, 1000);
  check(rc == 1000, "Duff's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's device failed copy.");

  // zeds version
  rc = zeds_device(from, to, 1000);
  check(rc == 1000, "Zed's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Zed's device failed copy.");

  // 32 version
  rc = duffs_device_32(from, to, 1000);
  check(rc == 1000, "Duff's 32 failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's 32 device failed copy.");
  
  return 0;

 error:
  return 1;
}
