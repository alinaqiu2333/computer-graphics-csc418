#include "ray_intersect_box.h"
#include <iostream>
void update_min_max(
	const Ray & ray,
	const BoundingBox& box,
	const int xyz,
	double & updated_min,
	double & updated_max)
{
	double xyz_e = ray.origin[xyz];
	double xyz_d = ray.direction[xyz];
	double xyz_a = 1/xyz_d;
	double temp_smallest = box.min_corner[xyz];
	double temp_largest = box.max_corner[xyz];
	if (xyz_a >= 0){
		updated_min = xyz_a * (temp_smallest - xyz_e);
		updated_max = xyz_a * (temp_largest - xyz_e);
	}
	else{
		updated_min = xyz_a * (temp_largest - xyz_e);
		updated_max = xyz_a * (temp_smallest - xyz_e);
	}
}


bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  double largest_in_min, smallest_in_max, smallest_in_min, largest_in_max;
  double x_min, x_max, y_min, y_max, z_min, z_max;
  update_min_max(ray, box, 0, x_min, x_max);
  update_min_max(ray, box, 1, y_min, y_max);
  update_min_max(ray, box, 2, z_min, z_max);
  largest_in_min = fmax(fmax(x_min, y_min), z_min);
  smallest_in_max = fmin(fmin(x_max, y_max), z_max);
  largest_in_max = fmax(fmax(x_max, y_max), z_max);
  smallest_in_min = fmin(fmin(x_min, y_min), z_min);
  if (largest_in_min <= smallest_in_max){
  	return true;
  }
  return false;
}