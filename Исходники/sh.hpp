 dmvsh(Type theta_, matrix<Type> Sigma) 
   : theta (theta_) {
   Q = Sigma.inverse();
   detQ = Q.determinant();
 }