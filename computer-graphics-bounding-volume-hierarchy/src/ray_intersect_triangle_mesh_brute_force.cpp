#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  hit_f = -1;
  double inf = std::numeric_limits<double>::infinity();
  for (int i = 0; i < F.rows(); i++){
    //find three vertices of this triangle
    Eigen::RowVector3d A = V.row(F(i,0));
    Eigen::RowVector3d B = V.row(F(i,1));
    Eigen::RowVector3d C = V.row(F(i,2));
    double triangle_temp_t;
    bool if_triangle_intersect = ray_intersect_triangle(ray, A, B, C, min_t, max_t, triangle_temp_t);
    if (if_triangle_intersect && triangle_temp_t < inf){
      inf = triangle_temp_t;
      hit_f = i;
    }
  }
  if (isinf(inf)){
    return false;
  }
  hit_t = inf;
  return true;
}


