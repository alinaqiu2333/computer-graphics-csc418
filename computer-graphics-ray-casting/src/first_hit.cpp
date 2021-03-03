#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  bool if_hit = false;
  for (int i = 0; i < objects.size(); i ++){
    double result_t;
    Eigen::Vector3d result_n;
    if (objects[i] -> intersect(ray, min_t, result_t, result_n)){
      if(result_t >= min_t){
          if (if_hit == false){
            if_hit = true;
            n = result_n;
            hit_id = i;
            t = result_t;
          }
          else{
            if (result_t < t){
              t = result_t;
              n = result_n;
              hit_id = i;
            }
          }

      }
    }
  }
  return if_hit;
}
