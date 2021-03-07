#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>
#include "Ray.h"

bool ray_intersect_plane(
  const Ray & ray, 
  const double min_t,
  const double max_t,
  double & t, 
  Eigen::Vector3d normal,
  Eigen::Vector3d destination)
{
  double t_temp = (destination.dot(normal) - normal.dot(ray.origin)) / (normal.dot(ray.direction));
  if (t_temp > min_t && t_temp < max_t && normal.dot(ray.direction) != 0){
    t = t_temp;
    return true;
  }
  return false;
}

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  Eigen::RowVector3d AB = B - A;
  Eigen::RowVector3d AC = C - A;
  Eigen::RowVector3d p_normal = AB.cross(AC).normalized();
  bool if_intersect = ray_intersect_plane(ray, min_t, max_t, t, p_normal, A);
  if (if_intersect){
      Eigen::RowVector3d edge_0 = B - A;
      Eigen::RowVector3d edge_1 = C - B;
      Eigen::RowVector3d edge_2 = A - C;
      Eigen::RowVector3d P = ray.origin + t * ray.direction;
      Eigen::RowVector3d vec_0 = P - A;
      Eigen::RowVector3d vec_1 = P - B;
      Eigen::RowVector3d vec_2 = P - C;
      if (p_normal.dot(edge_0.cross(vec_0)) > 0 &&
        p_normal.dot(edge_1.cross(vec_1)) > 0 &&
        p_normal.dot(edge_2.cross(vec_2)) > 0){
        return true;
      }   
  }
  return false;
}







