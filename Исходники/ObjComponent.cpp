/// Rotates a point by the reverse of the component's rotation
const V3D ObjComponent::takeOutRotation(V3D point) const {
  // Get the total rotation of this component and calculate the inverse (reverse
  // rotation)
  Quat unRotate = this->getRotation();
  unRotate.inverse();
  // Now rotate our point by the angle calculated above
  unRotate.rotate(point);

  // Can not Consider scaling factor here as this transform used by solidAngle
  // as well
  // as IsValid etc. While this would work for latter, breaks former

  return point;
}