double magnitude (Matrix<double> vd){

  double mag = 0;
  Matrix<double> vdt = vd.transpose();
  
  vdt = vd * vdt;
  mag = vdt[0][0];
  mag = sqrt(mag);
  return mag;
}