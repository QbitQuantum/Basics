/**
Convenience method for checking whether or not a vector is aligned
with the along beam vector.
@param v vector to be tested against along beam vector
@return result of whther the along beam and test vector are parallel.
*/
bool ReferenceFrame::isVectorPointingAlongBeam(const V3D &v) const {
  V3D vec = v;
  vec.normalize();

  // Normalized (unit) parallel vectors should produce a scalar product of 1
  return m_vecPointingAlongBeam.scalar_prod(vec) == 1;
}