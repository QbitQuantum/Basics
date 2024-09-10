double Triangle<ConcreteShape>::estimatedElementRadius() {
  Matrix2d invJ;
  double detJ;

  std::tie(invJ, detJ) = ConcreteShape::inverseJacobian(mVtxCrd);
  Matrix2d J = invJ.inverse();
  VectorXcd eivals = J.eigenvalues();

  // get minimum h (smallest direction)
  Vector2d eivals_norm;
  for(int i=0;i<2;i++) {
    eivals_norm(i) = std::norm(eivals[i]);
  }
  return eivals_norm.minCoeff();
  
}