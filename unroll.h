#ifndef __unroll_h__
#define __unroll_h__

#define DUFF(x, y) \
  case ((x ## y) + 1) : *to++ = *from++

#define SEVEN_AT_ONCE(x) \
  DUFF(x, 6);					\
  DUFF(x, 5);					\
  DUFF(x, 4);					\
  DUFF(x, 3);					\
  DUFF(x, 2);					\
  DUFF(x, 1);					\
  DUFF(x, 0)
  
#define EIGHT_AT_ONCE(x) \
  DUFF(x,7); \
  SEVEN_AT_ONCE(x)

#endif
