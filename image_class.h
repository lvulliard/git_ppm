#ifndef CLASS_INCLUDED
#define CLASS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//============================================================================
//                           Class declaration
//============================================================================
class Image
{
public:
  u_char* data;
  int width;
  int height;
};

#endif