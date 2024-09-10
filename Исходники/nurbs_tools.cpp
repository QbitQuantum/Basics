void
NurbsTools::pca (const vector_vec3d &data, Eigen::Vector3d &mean, Eigen::Matrix3d &eigenvectors,
                 Eigen::Vector3d &eigenvalues)
{
  if (data.empty ())
  {
    printf ("[NurbsTools::pca] Error, data is empty\n");
    abort ();
  }

  mean = computeMean (data);

  unsigned s = unsigned (data.size ());

  Eigen::MatrixXd Q (3, s);

  for (unsigned i = 0; i < s; i++)
    Q.col (i) << (data[i] - mean);

  Eigen::Matrix3d C = Q * Q.transpose ();

  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver (C);
  if (eigensolver.info () != Success)
  {
    printf ("[NurbsTools::pca] Can not find eigenvalues.\n");
    abort ();
  }

  for (int i = 0; i < 3; ++i)
  {
    eigenvalues (i) = eigensolver.eigenvalues () (2 - i);
    if (i == 2)
      eigenvectors.col (2) = eigenvectors.col (0).cross (eigenvectors.col (1));
    else
      eigenvectors.col (i) = eigensolver.eigenvectors ().col (2 - i);
  }
}