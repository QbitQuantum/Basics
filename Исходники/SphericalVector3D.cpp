IMPALGEBRA_BEGIN_NAMESPACE

Vector3D SphericalVector3D::get_cartesian_coordinates() {
  return Vector3D(v_[0] * cos(v_[2]) * sin(v_[1]),
                  v_[0] * sin(v_[2]) * sin(v_[1]), v_[0] * cos(v_[1]));
}