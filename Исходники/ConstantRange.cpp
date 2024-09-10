/// \brief Subtract the specified range from this range (aka relative complement
/// of the sets).
ConstantRange ConstantRange::difference(const ConstantRange &CR) const {
  return intersectWith(CR.inverse());
}