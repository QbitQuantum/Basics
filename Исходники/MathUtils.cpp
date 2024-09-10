double angle_mismatch(const Matrix3d& Q, const Matrix3d& R)
{
  //std::cout << "Q\n" << Q << "\nR\n" << R << std::endl;
  Matrix3d S = Q.transpose()*R;
  //std::cout << "S\n: " << S << std::endl;
  double thecos = (S.trace()-1.0)/2.0;
  thecos = std::max( std::min ( thecos, 1.0), -1.0);
  //std::cout << "thecos: " << thecos << " leads to angle: " << acos(thecos) << " * " << ( S(1,2) < 0.0 ? -1.0 : 1.0) << std::endl;

  return (acos(thecos) * ( S(1,2) < 0.0 ? -1.0 : 1.0));
}