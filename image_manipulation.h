#ifndef MANIP_INCLUDED
#define MANIP_INCLUDED

#include "image_class.h"

//============================================================================
//                           Function declarations
//============================================================================ 
// Write the image contained in <my_image.data> (of size <my_image.width>
// * <my_image.height>) into plain RGB ppm file at <file_name>
void ppm_write_to_file(Image my_image, const char* file_name);

// Read the image contained in plain RGB ppm file at <file_name>
// into <my_image.data> and set <my_image.width> and <my_image.height> 
// accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(Image& my_image, const char* file_name);

#endif