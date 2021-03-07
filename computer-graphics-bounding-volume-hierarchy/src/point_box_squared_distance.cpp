#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  //referencing from `https://stackoverflow.com/questions/5254838/calculating-distance-between-a-point-and-a-rectangular-box-nearest-point
  double x, y, z;
  x = fmax(fmax(box.min_corner[0] - query[0], 0) , query[0] - box.max_corner[0]);
  y = fmax(fmax(box.min_corner[1] - query[1], 0) , query[1] - box.max_corner[1]);
  z = fmax(fmax(box.min_corner[2] - query[2], 0) , query[2] - box.max_corner[2]);
  return x*x + y*y + z*z;
}