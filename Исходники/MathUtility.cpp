EigenTypes::Matrix3x3f MathUtility::RotationMatrixLinearInterpolation(const EigenTypes::Matrix3x3f& A0, const EigenTypes::Matrix3x3f& A1, float t) {
  EigenTypes::Vector3f dA = RotationMatrixToVector(A0.transpose()*A1);
  float angle = std::fmod(t*dA.norm(), (float)M_PI);
  EigenTypes::Matrix3x3f At = A0*RotationVectorToMatrix(angle*dA.normalized());
  return At;
}