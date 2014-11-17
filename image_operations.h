#ifndef OPER_INCLUDED
#define OPER_INCLUDED

#include "image_struc.h"

//============================================================================
//                           Function declarations
//============================================================================ 
// Desaturate (transform to B&W) <my_image>
void ppm_desaturate(image my_image);

// Shrink image (of original size <my_image.width> * <my_image.height>)
// by factor <factor> (<my_image> updated accordingly)
void ppm_shrink(image& my_image, int factor);

#endif