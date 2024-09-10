template <typename PointInT, typename PointNT, typename PointOutT, typename IntensitySelectorT> void
pcl::IntensityGradientEstimation <PointInT, PointNT, PointOutT, IntensitySelectorT>::computePointIntensityGradient (
  const pcl::PointCloud <PointInT> &cloud, const std::vector <int> &indices,
  const Eigen::Vector3f &point, float mean_intensity, const Eigen::Vector3f &normal, Eigen::Vector3f &gradient)
{
  if (indices.size () < 3)
  {
    gradient[0] = gradient[1] = gradient[2] = std::numeric_limits<float>::quiet_NaN ();
    return;
  }

  Eigen::Matrix3f A = Eigen::Matrix3f::Zero ();
  Eigen::Vector3f b = Eigen::Vector3f::Zero ();

  for (size_t i_point = 0; i_point < indices.size (); ++i_point)
  {
    PointInT p = cloud.points[indices[i_point]];
    if (!pcl_isfinite (p.x) ||
        !pcl_isfinite (p.y) ||
        !pcl_isfinite (p.z) ||
        !pcl_isfinite (intensity_ (p)))
      continue;

    p.x -= point[0];
    p.y -= point[1];
    p.z -= point[2];
    intensity_.demean (p, mean_intensity);

    A (0, 0) += p.x * p.x;
    A (0, 1) += p.x * p.y;
    A (0, 2) += p.x * p.z;

    A (1, 1) += p.y * p.y;
    A (1, 2) += p.y * p.z;

    A (2, 2) += p.z * p.z;

    b[0] += p.x * intensity_ (p);
    b[1] += p.y * intensity_ (p);
    b[2] += p.z * intensity_ (p);
  }
  // Fill in the lower triangle of A
  A (1, 0) = A (0, 1);
  A (2, 0) = A (0, 2);
  A (2, 1) = A (1, 2);

//*
  Eigen::Vector3f x = A.colPivHouseholderQr ().solve (b);
/*/

  Eigen::Vector3f eigen_values;
  Eigen::Matrix3f eigen_vectors;
  eigen33 (A, eigen_vectors, eigen_values);

  b = eigen_vectors.transpose () * b;

  if ( eigen_values (0) != 0)
    b (0) /= eigen_values (0);
  else
    b (0) = 0;

  if ( eigen_values (1) != 0)
    b (1) /= eigen_values (1);
  else
    b (1) = 0;

  if ( eigen_values (2) != 0)
    b (2) /= eigen_values (2);
  else
    b (2) = 0;


  Eigen::Vector3f x = eigen_vectors * b;

//  if (A.col (0).squaredNorm () != 0)
//    x [0] /= A.col (0).squaredNorm ();
//  b -= x [0] * A.col (0);
//
//
//  if (A.col (1).squaredNorm ()  != 0)
//    x [1] /= A.col (1).squaredNorm ();
//  b -= x[1] * A.col (1);
//
//  x [2] = b.dot (A.col (2));
//  if (A.col (2).squaredNorm () != 0)
//    x[2] /= A.col (2).squaredNorm ();
  // Fit a hyperplane to the data

//*/
//  std::cout << A << "\n*\n" << bb << "\n=\n" << x << "\nvs.\n" << x2 << "\n\n";
//  std::cout << A * x << "\nvs.\n" << A * x2 << "\n\n------\n";
  // Project the gradient vector, x, onto the tangent plane
  gradient = (Eigen::Matrix3f::Identity () - normal*normal.transpose ()) * x;
}