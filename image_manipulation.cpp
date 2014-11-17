#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_struc.h"
#include "image_manipulation.h"

//============================================================================
//                           Function definitions
//============================================================================
void ppm_write_to_file(image my_image, const char* file_name)
{
  FILE* file = fopen(file_name, "wb");

  // Write header
  fprintf(file, "P6\n%d %d\n255\n", my_image.width, my_image.height);

  // Write pixels
  fwrite(my_image.data, 3,my_image.width*my_image.height, file);

  fclose(file);
}

void ppm_read_from_file(image& my_image, const char* file_name)
{
  FILE* file = fopen(file_name, "rb");
  
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", &my_image.width, &my_image.height);

  // Allocate memory according to width and height
  my_image.data = new u_char [3 * (my_image.width) * (my_image.height)];

  // Read the actual image data
  fread(my_image.data, 3, (my_image.width) * (my_image.height), file);

  fclose(file);
}