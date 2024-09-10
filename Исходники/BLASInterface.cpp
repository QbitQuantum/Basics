void BLASInterface::Mul(const fMatrix& A,const fVector& x,fVector& out)
{
  out.resize(A.m);
  out.setZero();
  Madd(A,x,out);
}