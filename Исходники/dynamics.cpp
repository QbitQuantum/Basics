/*!
  Creates a 6x6 matrix, \a transformMat, that transforms a wrench expressed
  in one coordinate system to wrench expressed in another.  \a T is the
  transform, and \a p is the new torque origin expressed within the new
  coordinate system.
*/
void buildForceTransform(transf &T,vec3 &p,double *transformMat)
{
  static int j,k;
  static double R[9];
  static double crossMat[9];
  static double Rcross[9];
  static vec3 radius;

  R[0] = T.affine().element(0,0); 
  R[1] = T.affine().element(0,1); 
  R[2] = T.affine().element(0,2); 
  
  R[3] = T.affine().element(1,0); 
  R[4] = T.affine().element(1,1); 
  R[5] = T.affine().element(1,2); 
  
  R[6] = T.affine().element(2,0); 
  R[7] = T.affine().element(2,1); 
  R[8] = T.affine().element(2,2); 
/*
  R[0] = T.affine().element(0,0); 
  R[1] = T.affine().element(1,0); 
  R[2] = T.affine().element(2,0); 
  
  R[3] = T.affine().element(0,1); 
  R[4] = T.affine().element(1,1); 
  R[5] = T.affine().element(2,1); 
  
  R[6] = T.affine().element(0,2); 
  R[7] = T.affine().element(1,2); 
  R[8] = T.affine().element(2,2); 
*/ 

  for (j=0;j<9;j++)
    if (fabs(R[j]) < MACHINE_ZERO) R[j] = 0.0;
    else if (R[j] > 1.0 - MACHINE_ZERO) R[j] = 1.0;
    else if (R[j] < -1.0 + MACHINE_ZERO) R[j] = -1.0;
      
  radius = T.translation() - p;
	
  crossMat[0]=0.0;       crossMat[3]=-radius.z();crossMat[6]=radius.y();
  crossMat[1]=radius.z();crossMat[4]=0.0;        crossMat[7]=-radius.x();
  crossMat[2]=-radius.y();crossMat[5]= radius.x();crossMat[8]=0.0;

  //original graspit
  //dgemm("N","N",3,3,3,1.0,R,3,crossMat,3,0.0,Rcross,3);

  // mtc: new version, I believe this is the correct one
  dgemm("N","N",3,3,3,1.0,crossMat,3,R,3,0.0,Rcross,3);
	
  fillMatrixBlock(R,3,0,0,2,2,transformMat,6);
  for (j=3;j<6;j++)
    for (k=0;k<3;k++) 
      transformMat[6*j+k] = 0.0;
  fillMatrixBlock(Rcross,3,3,0,5,2,transformMat,6);
  fillMatrixBlock(R,3,3,3,5,5,transformMat,6);
}