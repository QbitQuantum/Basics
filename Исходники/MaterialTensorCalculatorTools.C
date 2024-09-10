Real
hoopStress(const SymmTensor & symm_stress,
           const Point & point1,
           const Point & point2,
           const Point & curr_point,
           RealVectorValue & direction)
{
  // Calculate the cross of the normal to the axis of rotation from the current
  // location and the axis of rotation
  Point xp;
  normalPositionVector(point1, point2, curr_point, xp);

  Point axis_rotation = point2 - point1;
  Point yp = axis_rotation / axis_rotation.norm();
  Point zp = xp.cross(yp);

  // Calculate the scalar value of the hoop stress
  Real hoop_stress = 0.0;
  for (unsigned int i = 0; i < 3; ++i)
  {
    for (unsigned int j = 0; j < 3; ++j)
      hoop_stress += zp(j) * symm_stress(j, i) * zp(i);
  }
  direction = zp;
  return hoop_stress;
}