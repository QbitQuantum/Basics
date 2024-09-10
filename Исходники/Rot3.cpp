/* ************************************************************************* */
Rot3 Rot3::AlignPair(const Unit3& axis, const Unit3& a_p, const Unit3& b_p) {
  // if a_p is already aligned with b_p, return the identity rotation
  if (std::abs(a_p.dot(b_p)) > 0.999999999) {
    return Rot3();
  }

  // Check axis was not degenerate cross product
  const Vector3 z = axis.unitVector();
  if (z.hasNaN())
    throw std::runtime_error("AlignSinglePair: axis has Nans");

  // Now, calculate rotation that takes b_p to a_p
  const Matrix3 P = I_3x3 - z * z.transpose();  // orthogonal projector
  const Vector3 a_po = P * a_p.unitVector();    // point in a orthogonal to axis
  const Vector3 b_po = P * b_p.unitVector();    // point in b orthogonal to axis
  const Vector3 x = a_po.normalized();          // x-axis in axis-orthogonal plane, along a_p vector
  const Vector3 y = z.cross(x);                 // y-axis in axis-orthogonal plane
  const double u = x.dot(b_po);                 // x-coordinate for b_po
  const double v = y.dot(b_po);                 // y-coordinate for b_po
  double angle = std::atan2(v, u);
  return Rot3::AxisAngle(z, -angle);
}