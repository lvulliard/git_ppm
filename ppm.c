
#include <assert.h>
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

//============================================================================
//                           Function declarations
//============================================================================
// Write the image contained in <my_image.data> (of size <my_image.width>
// * <my_image.height>) into plain RGB ppm file at <file_name>
void ppm_write_to_file(image my_image, char* file_name);

// Read the image contained in plain RGB ppm file at <file_name>
// into <my_image.data> and set <my_image.width> and <my_image.height> 
// accordingly
// Warning: data is malloc_ed, don't forget to free it
void ppm_read_from_file(image* my_image, char* file_name);
 
// Desaturate (transform to B&W) <my_image>
void ppm_desaturate(image my_image);

// Shrink image (of original size <my_image.width> * <my_image.height>)
// by factor <factor> (<my_image> updated accordingly)
void ppm_shrink(image* my_image, int factor);

//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{
  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  image my_image;

  ppm_read_from_file(&my_image, "gargouille.ppm");


  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  image my_bw_image = my_image;
  my_bw_image.data = (u_char*) malloc(3 * my_image.width * my_image.height * sizeof(*my_bw_image.data));
  memcpy(my_bw_image.data, my_image.data, 3 * my_image.width * my_image.height * sizeof(*my_bw_image.data));

  // Desaturate image_bw
  ppm_desaturate(my_bw_image);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(my_bw_image, "gargouille_BW.ppm");

  // Free the desaturated image
  free(my_bw_image.data);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  image my_small_image = my_image;
  my_small_image.data = (u_char*) malloc(3 * my_image.width * my_image.height * sizeof(*my_bw_image.data));
  memcpy(my_small_image.data, my_image.data, 3 * my_image.width * my_image.height * sizeof(*my_small_image.data));

  // Shrink image_sm&all size 2-fold
  ppm_shrink(&my_small_image, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(my_small_image,"gargouille_small.ppm");

  // Free the not yet freed images
  free(my_image.data);
  free(my_small_image.data);

  return 0;
}



//============================================================================
//                           Function definitions
//============================================================================
void ppm_write_to_file(image my_image, char* file_name)
{
  FILE* file = fopen(file_name, "wb");
  
  // Write header
  fprintf(file, "P6\n%d %d\n255\n", my_image.width, my_image.height);

  // Write pixels
  fwrite(my_image.data, 3,my_image.width*my_image.height, file);

  fclose(file);
}

void ppm_read_from_file(image* my_image, char* file_name)
{
  int* width = &((*my_image).width);
  int* height = &((*my_image).height);
  u_char** data = &((*my_image).data);
  FILE* file = fopen(file_name, "rb");
  
  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", width, height);

  // Allocate memory according to width and height
  *data = (u_char*) malloc(3 * (*width) * (*height) * sizeof(**data));

  // Read the actual image data
  fread(*data, 3, (*width) * (*height), file);

  fclose(file);
}

void ppm_desaturate(image my_image)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < my_image.width ; x++)
  {
    for (y = 0 ; y < my_image.height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += my_image.data[ 3 * (y * my_image.width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&my_image.data[3 * (y * my_image.width + x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(image* my_image, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = ((*my_image).width) / factor;
  int new_height  = ((*my_image).height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * ((*my_image).width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * ((*my_image).width) + dx);

          // Accumulate RGB values
          red   += ((*my_image).data)[i0+delta_i];
          green += ((*my_image).data)[i0+delta_i+1];
          blue  += ((*my_image).data)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  (*my_image).width  = new_width;
  (*my_image).height = new_height;

  // Update image
  free((*my_image).data);
  (*my_image).data = new_image;
}

































