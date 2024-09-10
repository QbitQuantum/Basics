Matrix3S StrainEneNeo::getdPdx(const Matrix3S & F,const Matrix3S & dF)
{
  Matrix3S dP = Matrix3S();
  cfgScalar JJ = std::log(F.determinant());
  Matrix3S Finv = F.inverse();
  Matrix3S FinvT = Finv.transpose();
  cfgScalar mu = param[0],lambda=param[1];
  dP = mu*dF;
  cfgScalar c1 = mu-lambda * JJ;
  dP += c1 * FinvT*dF.transpose()*FinvT;
  dP += lambda*(Finv*dF).trace()*FinvT;
  return dP;
}