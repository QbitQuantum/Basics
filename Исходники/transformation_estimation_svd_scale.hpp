template <typename PointSource, typename PointTarget, typename Scalar> void
pcl::registration::TransformationEstimationSVDScale<PointSource, PointTarget, Scalar>::getTransformationFromCorrelation (
    const Eigen::MatrixXf &cloud_src_demean,
    const Eigen::Vector4f &centroid_src,
    const Eigen::MatrixXf &cloud_tgt_demean,
    const Eigen::Vector4f &centroid_tgt,
    Matrix4 &transformation_matrix) const
{
  transformation_matrix.setIdentity ();

  // Assemble the correlation matrix H = source * target'
  Eigen::Matrix<Scalar, 3, 3> H = (cloud_src_demean.cast<Scalar> () * cloud_tgt_demean.cast<Scalar> ().transpose ()).topLeftCorner (3, 3);

  // Compute the Singular Value Decomposition
  Eigen::JacobiSVD<Eigen::Matrix<Scalar, 3, 3> > svd (H, Eigen::ComputeFullU | Eigen::ComputeFullV);
  Eigen::Matrix<Scalar, 3, 3> u = svd.matrixU ();
  Eigen::Matrix<Scalar, 3, 3> v = svd.matrixV ();

  // Compute R = V * U'
  if (u.determinant () * v.determinant () < 0)
  {
    for (int x = 0; x < 3; ++x)
      v (x, 2) *= -1;
  }

  Eigen::Matrix<Scalar, 3, 3> R = v * u.transpose ();

  // rotated cloud
  Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> src_ = R * cloud_src_demean.cast<Scalar> ();
  
  float scale1, scale2;
  double sum_ss = 0.0f, sum_tt = 0.0f, sum_tt_ = 0.0f;
  for (unsigned corrIdx = 0; corrIdx < cloud_src_demean.cols (); ++corrIdx)
  {
    sum_ss += cloud_src_demean (0, corrIdx) * cloud_src_demean (0, corrIdx);
    sum_ss += cloud_src_demean (1, corrIdx) * cloud_src_demean (1, corrIdx);
    sum_ss += cloud_src_demean (2, corrIdx) * cloud_src_demean (2, corrIdx);
    
    sum_tt += cloud_tgt_demean (0, corrIdx) * cloud_tgt_demean (0, corrIdx);
    sum_tt += cloud_tgt_demean (1, corrIdx) * cloud_tgt_demean (1, corrIdx);
    sum_tt += cloud_tgt_demean (2, corrIdx) * cloud_tgt_demean (2, corrIdx);
    
    sum_tt_ += cloud_tgt_demean (0, corrIdx) * src_ (0, corrIdx);
    sum_tt_ += cloud_tgt_demean (1, corrIdx) * src_ (1, corrIdx);
    sum_tt_ += cloud_tgt_demean (2, corrIdx) * src_ (2, corrIdx);
  }
  
  scale1 = sqrt (sum_tt / sum_ss);
  scale2 = sum_tt_ / sum_ss;
  float scale = scale2;
  transformation_matrix.topLeftCorner (3, 3) = scale * R;
  const Eigen::Matrix<Scalar, 3, 1> Rc (R * centroid_src.cast<Scalar> ().head (3));
  transformation_matrix.block (0, 3, 3, 1) = centroid_tgt.cast<Scalar> (). head (3) - Rc;
}