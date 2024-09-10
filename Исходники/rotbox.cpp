template<> RotBox<3> RotBox<3>::toLocalCoords(const Point<3>& origin,
                                              const Quaternion& rotation) const
{
  RotMatrix<3> orient = m_orient;
  return RotBox<3>(m_corner0.toLocalCoords(origin, rotation), m_size, orient.rotate(rotation.inverse()));
}