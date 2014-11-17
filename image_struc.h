#ifndef STRUCT_INCLUDED
#define STRUCT_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//============================================================================
//                           Struct declaration
//============================================================================
typedef struct
{
  u_char* data;
  int width;
  int height;
}image;

#endif
