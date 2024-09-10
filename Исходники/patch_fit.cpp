Matrix<double,Dynamic,9>
PatchFit::general_dfda (MatrixXd ql, Matrix3d rr, MatrixXd dfdql, vector<MatrixXd> dqldr)
{
  MatrixXd dfdk (ql.rows(), ql.cols());
  dfdk = ql.array()*ql.array();

  MatrixXd dfdr (ql.rows(), ql.cols());
  dfdr.col(0) = (dfdql.array()*dqldr[0].array()).rowwise().sum();
  dfdr.col(1) = (dfdql.array()*dqldr[1].array()).rowwise().sum();
  dfdr.col(2) = (dfdql.array()*dqldr[2].array()).rowwise().sum();

  MatrixXd dfdc (ql.rows(), ql.cols());
  dfdc = -dfdql*rr.transpose();

  MatrixXd j (ql.rows(), 9);
  j << dfdk, dfdr, dfdc;

  return j;
}