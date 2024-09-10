Real utl::Jacobian (matrix<Real>& J, Vec3& n, matrix<Real>& dNdX,
                    const matrix<Real>& X, const matrix<Real>& dNdu,
                    size_t t1, size_t t2)
{
  // Compute the Jacobian matrix, J = [dXdu]
  J.multiply(X,dNdu); // J = X * dNdu

  Real dS;
  if (J.cols() == 2)
  {
    // Compute the face normal
    Vec3 v1(J.getColumn(t1));
    Vec3 v2(J.getColumn(t2));
    Vec3 v3(v1,v2); // v3 = v1 x v2
    // Compute the curve dilation (dS) and the in-plane edge normal (n)
    dS = v2.normalize(); // dA = |v2|
    v3.normalize();
    n.cross(v2,v3); // n = v2 x v3 / (|v2|*|v3|)
  }
  else
  {
    // Compute the face normal (n) and surface dilation (dS)
    n.cross(J.getColumn(t1),J.getColumn(t2)); // n = t1 x t2
    dS = n.normalize(); // dS = |n|
  }

  // Compute the Jacobian inverse
  if (J.inverse(epsZ) == Real(0))
  {
    dS = Real(0);
    dNdX.clear();
  }
  else
    // Compute the first order derivatives of the basis function, w.r.t. X
    dNdX.multiply(dNdu,J); // dNdX = dNdu * J^-1

  return dS;
}