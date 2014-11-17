#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_class.h"

//============================================================================
//                           Function definitions
//============================================================================
void Image::ppm_write_to_file(const char* file_name)
{
  FILE* file = fopen(file_name, "wb");

  // Write header
  fprintf(file, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3,width*height, file);

  fclose(file);
}

void Image::ppm_read_from_file(const char* file_name)
{
  FILE* file = fopen(file_name, "rb");
  
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", &width, &height);

  // Allocate memory according to width and height
  data = new u_char [3 * (width) * (height)];

  // Read the actual image data
  fread(data, 3, (width) * (height), file);

  fclose(file);
}