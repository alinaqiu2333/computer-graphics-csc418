#include <Eigen/Geometry>
#include "Triangle.h"
#include "Plane.h"
#include "Ray.h"

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    Eigen::Vector3d a = std::get<0>(corners);
    Eigen::Vector3d b = std::get<1>(corners);
    Eigen::Vector3d c = std::get<2>(corners);
    Eigen::Vector3d ab = b - a;
    Eigen::Vector3d ac = c - a;
    Eigen::Vector3d p_normal = ab.cross(ac).normalized();
    auto new_plane = new Plane();
    new_plane -> point = a;
    new_plane -> normal = p_normal;
    Eigen::Vector3d temp_n;
    if (new_plane -> intersect(ray, min_t, t, temp_n)){
    	Eigen::Vector3d edge_0 = b - a;
    	Eigen::Vector3d edge_1 = c - b;
    	Eigen::Vector3d edge_2 = a - c;
    	Eigen::Vector3d P = ray.origin + t * ray.direction;
    	Eigen::Vector3d vec_0 = P - a;
    	Eigen::Vector3d vec_1 = P - b;
    	Eigen::Vector3d vec_2 = P - c;
    	n = temp_n;
    	if (p_normal.dot(edge_0.cross(vec_0)) > 0 &&
    		p_normal.dot(edge_1.cross(vec_1)) > 0 &&
    		p_normal.dot(edge_2.cross(vec_2)) > 0){
    		delete new_plane;
    		return true;
    	}
    delete new_plane;
    return false;
	}

}
