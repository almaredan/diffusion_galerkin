#include "vector3d.h"

tensor3D  operator*  (const tensor3D &t, const real& d)
{
  tensor3D t_tmp(t);
  t_tmp *= d;

  return t_tmp;
}

tensor3D  operator*  (const real& d, const tensor3D &t)
{
  return t*d;
}

