MatrixXd pointPointDistJac(const Vector3d y11, const Vector3d y21)
{
  MatrixXd J = MatrixXd::Zero(1,6);
  Vector3d a = y11-y21;
  RowVector3d dd_da = a.transpose()/a.norm();
  J.block(0,0,1,3) = dd_da;
  J.block(0,3,1,3) = -dd_da;
  return J;
}