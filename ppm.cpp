#include <stdio.h>
#include "image_class.h"


//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  Image my_image;

  my_image.ppm_read_from_file("gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  Image my_bw_image(my_image);

  // Desaturate image_bw
  my_bw_image.ppm_desaturate();

  // Write the desaturated image into "gargouille_BW.ppm"
  my_bw_image.ppm_write_to_file("gargouille_BW.ppm");

  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  Image my_small_image(my_image);

  // Shrink image_sm&all size 2-fold
  my_small_image.ppm_shrink(2);

  // Write the desaturated image into "gargouille_small.ppm"
  my_small_image.ppm_write_to_file("gargouille_small.ppm");

  // Objects destructor is caller and free the data memory

  return 0;
}