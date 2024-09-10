 virtual void Jacobian(const Vector& dxddx,Matrix& J) {
   J.resize(3,6);
   J.setZero();
   for(int i=0;i<3;i++)
     J(i,i+3) = 1.0;
 }