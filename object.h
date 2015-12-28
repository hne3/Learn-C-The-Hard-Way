// If object is not already defined, here's the definition
#ifndef _object_h
#define _object_h

typedef enum
  {
    NORTH, SOUTH,
    EAST, WEST
  } Direction;

typedef struct
{
  char *description;
  int (*init)(void *self);
  void (*describe)(void *self);
  void (*destroy)(void *self);
  void *(*move)(void *self, Direction direction);
  int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
void Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

// Makes a macro to work like a template fxn that spits out code on the right
// This one makes a short version of Object_new
// T##Proto says "concat Proto at the end of T", so you end up with TProto
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
// Lets you write obj->proto.thing as obj->_(thing)
#define _(N) proto.N

#endif
