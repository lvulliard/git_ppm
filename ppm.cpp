#include <stdio.h>
#include "image_manipulation.h"
#include "image_operations.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  Image my_image;

  ppm_read_from_file(my_image, "gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  Image my_bw_image = my_image;
  my_bw_image.data = new u_char [3 * my_image.width * my_image.height];
  memcpy(my_bw_image.data, my_image.data, 3 * my_image.width * my_image.height * sizeof(*my_bw_image.data));

  // Desaturate image_bw
  ppm_desaturate(my_bw_image);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(my_bw_image, "gargouille_BW.ppm");

  // Free the desaturated image
  delete [] my_bw_image.data;


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  Image my_small_image = my_image;
  my_small_image.data = new u_char [3 * my_image.width * my_image.height];
  memcpy(my_small_image.data, my_image.data, 3 * my_image.width * my_image.height * sizeof(*my_small_image.data));

  // Shrink image_sm&all size 2-fold
  ppm_shrink(my_small_image, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(my_small_image,"gargouille_small.ppm");

  // Free the not yet freed images
  delete [] my_image.data;
  delete [] my_small_image.data;

  return 0;
}