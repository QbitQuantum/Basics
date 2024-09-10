Real Tet4::volume () const
{
  // The volume of a tetrahedron is 1/6 the box product formed
  // by its base and apex vectors
  Point a ( *this->get_node(3) - *this->get_node(0) );

  // b is the vector pointing from 0 to 1
  Point b ( *this->get_node(1) - *this->get_node(0) );

  // c is the vector pointing from 0 to 2
  Point c ( *this->get_node(2) - *this->get_node(0) );

  return (1.0 / 6.0) * (a * (b.cross(c)));
}