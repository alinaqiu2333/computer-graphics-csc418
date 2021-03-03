#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  std::ofstream file(filename);
  try{
    if (not file.is_open()){
      return false;
    }
    if (num_channels == 3){
      file << "P3" << std::endl << width << " " << height << std::endl << "255" << std::endl;
    }
    else{
      file << "P2" << std::endl << width << " " << height << std::endl << "255" << std::endl;
    }
    int pixel_index;
    for (int i = 0; i < height; i ++){
      for (int j = 0; j < width; j ++){
        pixel_index = num_channels * (width * i + j);
        if (num_channels == 3){
          file << (double) data[pixel_index] << " " << (double) data[pixel_index + 1] << " " << (double) data[pixel_index + 2] << " ";
        }
        else{
          file << (double) data[pixel_index] << " ";
        }
      }
      if (num_channels == 3){
        file << std::endl;
      }
    }
    file.close();
    return true;  
  }
  catch (int a){
    if (file.is_open()){
      file.close();
      return false;
    } 
  }
}

















