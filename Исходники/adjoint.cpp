void
Adjoint::construct(const Rotation& R, const Translation& T)
{
  _data = arma::zeros<arma::mat>(6, 6);
  arma::colvec::fixed<3> v;

  v(0) = T.at(0); v(1) = T.at(1); v(2) = T.at(2);
  Skew S(v);
  arma::mat::fixed<3, 3> R2 = S._data*R._data;

  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j)
    {
      _data(i, j + 3) = R2(i, j);
      _data(i, j) = _data(i + 3, j + 3) = R.at(i, j);
    }
  _R = R;
  _T = T;
}