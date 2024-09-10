void SensorPolar2D::backProject(Matrix* M, int* indices, Matrix* T)
{
  Timer t;
  Matrix PoseInv = getTransformation();
  PoseInv.invert();
  if(T)
    PoseInv *= *T;

  Matrix coords2D = Matrix::multiply(PoseInv, *M, false, true);

  const double angularResInv = 1.0 / _angularRes;
  for(unsigned int i=0; i<M->getRows(); i++)
  {
    const double phi = atan2(coords2D(1,i), coords2D(0,i));
    if(phi<=_phiLowerBound) indices[i] = -1;
    else if(phi>=_phiUpperBound) indices[i] = -1;
    else indices[i] = round((phi-_phiMin) * angularResInv);
  }
}