#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  double l = - camera.width/2;
  double t = camera.height/2;
  double frame_u = l + camera.width * (j + 0.5) / width;
  double frame_v = t - camera.height * (i + 0.5) / height;
  double frame_d = camera.d;

  ray.origin = camera.e;
  ray.direction = (-1)*(frame_d * camera.w) + (camera.u * frame_u) + (camera.v * frame_v);
}

