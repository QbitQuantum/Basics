// --------- deprecated --------------
void OptSO3::rectifyRotation(Matrix3f& R)
{
  float detR = R.determinant();
  if (abs(detR-1.0) <1e-6) return;
  // use projection of R onto SO3 to rectify the rotation matrix

  //cout<<"det(R)="<<R.determinant()<<endl<<R<<endl;

  Matrix3f M = R.transpose()*R;
  EigenSolver<Matrix3f> eig(M);
  Matrix3cf U = eig.eigenvectors();
  Vector3cf d = eig.eigenvalues();
  if (d(2).real() > 1e-6)
  {
    // http://lcvmwww.epfl.ch/new/publications/data/articles/63/simaxpaper.pdf
    // Eq. (3.7)
    // Moakher M (2002). "Means and averaging in the group of rotations."
    d = ((d.array().sqrt()).array().inverse());
    Matrix3cf D = d.asDiagonal();
    D(2,2) *= detR>0.0?1.0f:-1.0f;
    R = R*(U*D*U.transpose()).real();
  }else{
    //http://www.ti.inf.ethz.ch/ew/courses/GCMB07/material/lecture03/HornOrthonormal.pdf
    //Horn; Closed-FormSolutionofAbsoluteOrientation UsingOrthonormalMatrices
    d = ((d.array().sqrt()).array().inverse());
    d(2) = 0.0f;
    Matrix3cf Sp = d.asDiagonal(); 
    JacobiSVD<Matrix3f> svd(R*Sp.real());
    R = R*Sp.real() + (detR>0.0?1.0f:-1.0f)*svd.matrixU().col(2)*svd.matrixV().col(2).transpose();
  }
  //    Matrix3d M = (R.transpose()*R).cast<double>();
  //    EigenSolver<Matrix3d> eig(M);
  //    MatrixXd U = eig.eigenvectors();
  //    Matrix3d D = eig.eigenvalues();

  //cout<<"det(R)="<<R.determinant()<<endl<<R<<endl;

  //      R.col(0).normalize();
  //      R.col(2) = R.col(0).cross(R.col(1));
  //      R.col(2).normalize();
  //      R.col(1) = R.col(2).cross(R.col(0));
  //cout<<"det(R)="<<R.determinant()<<endl<<R<<endl;
} 