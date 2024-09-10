double Tetrahedra<ConcreteShape>::estimatedElementRadius() {
  Matrix3d invJ;
  double detJ;

  std::tie(invJ, detJ) = ConcreteShape::inverseJacobian(mVtxCrd);
  Matrix3d J = invJ.inverse();
  VectorXcd eivals = J.eigenvalues();

  // get minimum h (smallest direction)
  Vector3d eivals_norm;
  for(int i=0;i<3;i++) {
    eivals_norm(i) = std::norm(eivals[i]);
  }
  return eivals_norm.minCoeff();
  
}