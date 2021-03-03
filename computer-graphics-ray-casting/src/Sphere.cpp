#include "Sphere.h"
#include "Ray.h"
#include <cmath>
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = this -> center;
  Eigen::Vector3d d = ray.direction;
  double R = this -> radius;
  double temp = d.dot(e - c);
  double discriminant = pow(temp, 2) - d.dot(d) * ((e-c).dot(e-c) - R*R);
  double negative_b = -1 * (d.dot(e-c));
  double two_a = d.dot(d);
  double t_1;
  double t_2;
  if (discriminant == 0){
  	if (negative_b / two_a > min_t){
  		t = negative_b / two_a;
      n = (e + t * d - c) / R;
  		return true;
  	}
  }
  else if (discriminant > 0){
  		t_1 = (negative_b + sqrt(discriminant))/two_a;
  		t_2 = (negative_b - sqrt(discriminant))/two_a;
  		if (t_2 > min_t){
  			t = t_2;
  			n = (e + t * d - c) / R;
  			return true;
  		}
      else if (t_1 > min_t){
        t = t_1;
        n = (e + t * d - c) / R;
        return true;
      }
  }
  else{
  	return false;
  }


}


