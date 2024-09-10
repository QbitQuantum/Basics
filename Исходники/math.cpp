void computeHomographyResidue(MatrixXf pts1, MatrixXf pts2, const Matrix3f &H, MatrixXf &residue){
  // cross residue
  filterPointAtInfinity(pts1, pts2);
  residue.resize(pts1.rows(), 1);
  MatrixXf Hx1 = (H*pts1.transpose()).transpose();
  MatrixXf invHx2 = (H.inverse()*pts2.transpose()).transpose();

  noHomogeneous(Hx1);
  noHomogeneous(invHx2);
  noHomogeneous(pts1);
  noHomogeneous(pts2);

  MatrixXf diffHx1pts2 = Hx1 - pts2;
  MatrixXf diffinvHx2pts1 = invHx2 - pts1;
  residue = diffHx1pts2.rowwise().squaredNorm() + diffinvHx2pts1.rowwise().squaredNorm();
}