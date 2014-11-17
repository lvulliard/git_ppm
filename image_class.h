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

  // Write the image contained in <my_image.data> (of size <my_image.width>
	// * <my_image.height>) into plain RGB ppm file at <file_name>
	void ppm_write_to_file(const char* file_name);

	// Read the image contained in plain RGB ppm file at <file_name>
	// into <my_image.data> and set <my_image.width> and <my_image.height> 
	// accordingly
	// Warning: data is malloc_ed, don't forget to free it
	void ppm_read_from_file(const char* file_name);
};

#endif