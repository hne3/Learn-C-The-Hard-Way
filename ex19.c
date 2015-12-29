#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"
#include <assert.h>

int Monster_attack(void *self, int damage)
{
  assert(self != NULL);
  Monster *monster = self;

  printf("You attack %s!\n", monster->_(description));

  monster->hit_points -= damage;

  if(monster->hit_points > 0)
    {
      printf("It is still alive!\n");
      return 0;
    }else
    {
      printf("It is dead!\n");
      return 1;
    }
}

int Monster_init(void *self)
{
  assert(self != NULL);
  Monster *monster = self;
  monster->hit_points = 10;
  return 1;
}

Object MonsterProto =
  {
    .init = Monster_init,
    .attack = Monster_attack
  };

void *Room_move(void *self, Direction direction)
{
  assert(self != NULL);
  Room *room = self;
  Room *next = NULL;

  if(direction == NORTH && room->north)
    {
      printf("You go north, into:\n");
      next = room->north;
    }else if(direction == SOUTH && room->south)
    {
      printf("You go south, into:\n");
      next = room->south;
    }else if(direction == EAST && room->east)
    {
      printf("You go east, into:\n");
      next = room->east;
    }else if(direction == WEST && room->west)
    {
      printf("You go west, into:\n");
      next = room->west;
    }else
    {
      printf("You can't go that direction.\n");
      next = NULL;
    }

  if(next)
    {
      next->_(describe)(next);
    }else
    {
      printf("No next room to be heard of!\n");
    }

  return next;
}

int Room_attack(void *self, int damage)
{
  assert(self != NULL);
  Room *room = self;
  Monster *monster = room->bad_guy;

  if(monster)
    {
      monster->_(attack)(monster, damage);
      return 1;
    }else
    {
      printf("You flail in the air at nothing.\n");
      return 0;
    }
}

Object RoomProto =
  {
    .move = Room_move,
    .attack = Room_attack
  };

void *Map_move(void *self, Direction direction)
{
  assert(self != NULL);
  Map *map = self;
  Room *location = map->location;
  Room *next = NULL;

  next = location->_(move)(location, direction);

  if(next)
    {
      map->location = next;
    }else
    {
      printf("No next location to be heard of!\n");
    }

  return next;
}

int Map_attack(void *self, int damage)
{
  Map *map = self;
  Room *location = map->location;

  return location->_(attack)(location, damage);
}

int Map_init(void *self)
{
  assert(self != NULL);
  Map *map = self;

  //make some rooms for a small map
  Room *hall = NEW(Room, "The Great Hall");
  assert(hall != NULL);
  
  Room *throne = NEW(Room, "The Throne Room");
  assert(throne != NULL);
  
  Room *arena = NEW(Room, "The Arena, w/Minotaur");
  assert(arena != NULL);
  
  Room *kitchen = NEW(Room, "The Kitchen, w/knife");
  assert(kitchen != NULL);

  // put bad guy in arena
  arena->bad_guy = NEW(Monster, "The evil minotaur");
  assert(arena->bad_guy != NULL);

  // setup the map rooms
  hall->north = throne;

  throne->west = arena;
  throne->east = kitchen;
  throne->south = hall;

  arena->east = throne;
  kitchen->west = throne;

  // start the map and the character off in the hall
  map->start = hall;
  map->location = hall;

  return 1;
}

Object MapProto =
  {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
  };

int process_input(Map *game)
{
  assert(game != NULL);
  printf("\n> ");

  char ch = getchar();
  getchar(); // ENTER

  // Why this magic number?
  int damage = rand() % 4;

  switch(ch)
    {
    case -1:
      printf("Giving up already?\n");
      return 0;
      break;

    case 'n':
      game->_(move)(game, NORTH);
      break;

    case 's':
      game->_(move)(game, SOUTH);
      break;

    case 'e':
      game->_(move)(game, EAST);
      break;

    case 'w':
      game->_(move)(game, WEST);
      break;

    case 'a':
      game->_(attack)(game, damage);
      break;

    case 'l':
      printf("You can:\n");
      if(game->location->north)
	{
	  printf("go NORTH\n");
	}
      if(game->location->south)
	{
	  printf("go SOUTH\n");
	}
      if(game->location->east)
	{
	  printf("go EAST\n");
	}
      if(game->location->west)
	{
	  printf("go WEST\n");
	}
      break;

    default:
      printf("What?: %d\n", ch);
    }

  return 1;
}

int main(int argc, char *argv[])
{
  // simple way to set up the randomness
  srand(time(NULL));

  // make our map to work with
  // CPP expands below line as a macro into Objet_new(
  // sizeof(Map), MapProto, "The Hall of the Minotaur.")
  // This runs inside Object_new. Allocates a piece of
  // memory of size sizeof(Map), but I point an Object
  // pointer at it.
  // Uses Object pointer to set the contents of the
  // memory correctly.
  // Now, we can init or destroy the Object.
  Map *game = NEW(Map, "The Hall of the Minotaur");

  printf("You enter the ");
  game->location->_(describe)(game->location);

  while(process_input(game))
    {
    }

  return 0;
}
