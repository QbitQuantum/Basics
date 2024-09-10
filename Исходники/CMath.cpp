double* CMath::Normal2Euler(double x, double y, double z) {
   double phi = acos(y);// - 3.14159/2;
   double theta = atan(z / x) ;//- 3.14159/2;       
   return MatrixZYZ(-phi, -theta, -phi);
}