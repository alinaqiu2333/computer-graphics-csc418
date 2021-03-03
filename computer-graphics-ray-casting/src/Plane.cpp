#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
	const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
	Eigen::Vector3d normal = this -> normal;
	Eigen::Vector3d e = ray.origin;
	Eigen::Vector3d d = ray.direction;
	Eigen::Vector3d p0 = this -> point;
	double t_temp = - normal.dot(e - p0) / (normal.dot(d));
	if (t_temp > min_t){
		t = t_temp;
		n = normal;
		return true;
	}
	n = normal;
	return false;
}

