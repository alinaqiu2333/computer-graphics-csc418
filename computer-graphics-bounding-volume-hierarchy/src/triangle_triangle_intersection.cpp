#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include "Ray.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  //referenced https://stackoverflow.com/questions/7113344/find-whether-two-triangles-intersect-or-not
  //
  Eigen::RowVector3d origin, direction;
  Eigen::RowVector3d v0, v1, v2;
  double min_t, max_t;
  double t;

  origin = A0;
  direction = A1-A0;
  min_t = 0.0;
  max_t = (A1-A0).norm();
  v0 = B0;
  v1 = B1;
  v2 = B2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }
  origin = A1;
  direction = A2-A1;
  min_t = 0.0;
  max_t = (A2-A1).norm();
  v0 = B0;
  v1 = B1;
  v2 = B2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }
  origin = A2;
  direction = A0-A2;
  min_t = 0.0;
  max_t = (A0-A2).norm();
  v0 = B0;
  v1 = B1;
  v2 = B2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }
  
  origin = B0;
  direction = B1-B0;
  min_t = 0.0;
  max_t = (B1-B0).norm();
  v0 = A0;
  v1 = A1;
  v2 = A2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }

  origin = B1;
  direction = B2-B1;
  min_t = 0.0;
  max_t = (B2-B1).norm();
  v0 = A0;
  v1 = A1;
  v2 = A2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }

  origin = B2;
  direction = B0-B2;
  min_t = 0.0;
  max_t = (B0-B2).norm();
  v0 = A0;
  v1 = A1;
  v2 = A2;
  if (ray_intersect_triangle(Ray(origin, direction), v0, v1, v2, min_t, max_t, t)){
      return true;
  }

  return false;
}
