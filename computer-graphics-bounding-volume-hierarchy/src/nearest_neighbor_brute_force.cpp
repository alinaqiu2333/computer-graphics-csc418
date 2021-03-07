#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  I = -1;
  double temp = std::numeric_limits<double>::infinity();
  for (int i = 0; i < points.rows(); i++){
    double x, y, z;
    x = query[0] - points(i, 0);
    y = query[1] - points(i, 1);
    z = query[2] - points(i, 2);
    double s = pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0);
    if (s <= temp){
      temp = s;
      I = i;
    }
  }
  sqrD = temp;
}
