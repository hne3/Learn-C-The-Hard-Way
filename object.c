#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destroy(void *self)
{
  Obj *obj = self;

  // If obj != NULL
  if(obj)
    {
      // If obj->description != NULL
      if(obj->description)
	{
	  free(obj->description);
	}
      free(obj);
    }
}

void Object_describe(void *self)
{
  Object *obj = self;
  printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
  // Do nothing really
  // Why?
  return 1;
}

void *Object_move(void *self, Direction direction)
{
  printf("You can't go that direction.\n");
  // Why return if fxn is void?
  return NULL;
}

int Object_attack(void *self, int damage)
{
  printf("You can't attack that.\n");
  return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
  // Set up default fxns in case they aren't set
  if(!proto.init)
    {
      proto.init = Object.init;
    }
  if(!proto.describe)
    {
      proto.describe = Object.describe;
    }
  if(!proto.destroy)
    {
      proto.destroy = Object.destroy;
    }
  if(!proto.attack)
    {
      proto.attack = Object.attack;
    }
  if(!proto.move)
    {
      proto.move = Object.move;
    }

  // This seems weird, but we can make a struct of one size,
  // then point a different pointer at it to "cast" it
  Object *el = calloc(1, size);
  // What is calloc?
  *el = proto;

  // copy the description over
  el->description = strdup(description);

  // initialize it with whatever init we were given
  if(!el->init(el))
    {
      // looks like we didn't init properly
      el->destroy(el);
      return NULL;
    }else
    {
      // all done, we made an object of any type
      return el;
    }
}

