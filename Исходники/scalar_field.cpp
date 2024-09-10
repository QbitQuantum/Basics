/*
 * float get_value_interp(x,y,z)
 *
 * Grabs a value from the 3D scalar field. Calculate the value
 * by using a trilinear interpolation.
 *
 * The trilinear interpolation algorithm has been extracted from:
 * http://paulbourke.net/miscellaneous/interpolation/
 *
 * Future algorithm can make use of a cubic interpolation.
 *
 */
float ScalarField::get_value_interp(const float &x, const float &y, const float &z) {
  // cast the input to the nearest grid point
  XYZ r = this->realspace_to_grid(x,y,z);
  XYZ d = this->realspace_to_direct(x,y,z);

  // to test whether the point is inside the box, we cast the point back
  // to the direct grid and check if it is for each cartesian coordinate
  // within the domain [0,1]
  if(d.x < 0 || d.x > 1.0) {
    return 0.0;
  }
  if(d.y < 0 || d.y > 1.0) {
    return 0.0;
  }
  if(d.z < 0 || d.z > 1.0) {
    return 0.0;
  }

  // calculate value using trilinear interpolation
  float xd = remainderf(r.x, 1.0);
  float yd = remainderf(r.y, 1.0);
  float zd = remainderf(r.z, 1.0);

  if(xd < 0) xd += 1.0;
  if(yd < 0) yd += 1.0;
  if(zd < 0) zd += 1.0;

  float x0 = floor(r.x);
  float x1 = ceil(r.x);
  float y0 = floor(r.y);
  float y1 = ceil(r.y);
  float z0 = floor(r.z);
  float z1 = ceil(r.z);

  return
  this->get_value(x0, y0, z0) * (1.0 - xd) * (1.0 - yd) * (1.0 - zd) +
  this->get_value(x1, y0, z0) * xd         * (1.0 - yd) * (1.0 - zd) +
  this->get_value(x0, y1, z0) * (1.0 - xd) * yd         * (1.0 - zd) +
  this->get_value(x0, y0, z1) * (1.0 - xd) * (1.0 - yd) * zd         +
  this->get_value(x1, y0, z1) * xd         * (1.0 - yd) * zd         +
  this->get_value(x0, y1, z1) * (1.0 - xd) * yd         * zd         +
  this->get_value(x1, y1, z0) * xd         * yd         * (1.0 - zd) +
  this->get_value(x1, y1, z1) * xd         * yd         * zd;
}