void Cylinder::SetRadius( double top_radius, double bottom_radius ) {

  if ( !_finite( bottom_radius ) ) bottom_radius = top_radius;
  this->top_radius = top_radius;
  this->bottom_radius = bottom_radius;

}