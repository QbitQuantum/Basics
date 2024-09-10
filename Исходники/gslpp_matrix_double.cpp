 vector<complex> operator*(const vector<complex>& v, matrix<double> m)
 {
   return m.transpose() * v;
 }