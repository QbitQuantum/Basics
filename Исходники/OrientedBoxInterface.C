OrientedBoxInterface::OrientedBoxInterface(const InputParameters & parameters) :
    _center(parameters.get<Point>("center"))
{
  const std::string & name = parameters.get<std::string>("_object_name");

  // Define the bounding box
  Real xmax = 0.5 * parameters.get<Real>("width");
  Real ymax = 0.5 * parameters.get<Real>("length");
  Real zmax = 0.5 * parameters.get<Real>("height");

  Point bottom_left(-xmax, -ymax, -zmax);
  Point top_right(xmax, ymax, zmax);

  _bounding_box = new MeshTools::BoundingBox(bottom_left, top_right);

  /*
   * now create the rotation matrix that rotates the oriented
   * box's width direction to "x", its length direction to "y"
   * and its height direction to "z"
   */
  RealVectorValue w = parameters.get<RealVectorValue>("width_direction");
  RealVectorValue l = parameters.get<RealVectorValue>("length_direction");

  /*
   * Normalize the width and length directions in readiness for
   * insertion into the rotation matrix
   */
  Real len = w.norm();
  if (len == 0.0)
    mooseError("Length of width_direction vector is zero in " << name);
  w /= len;

  len = l.norm();
  if (len == 0.0)
    mooseError("Length of length_direction vector is zero in " << name);
  l /= len;

  if (w*l > 1E-10)
    mooseError("width_direction and length_direction are not perpendicular in " << name);

  // The rotation matrix!
  _rot_matrix = new RealTensorValue(w, l, w.cross(l));

}