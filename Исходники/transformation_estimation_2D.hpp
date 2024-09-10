template <typename PointSource, typename PointTarget, typename Scalar> void
pcl::registration::TransformationEstimation2D<PointSource, PointTarget, Scalar>::getTransformationFromCorrelation (
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> &cloud_src_demean,
    const Eigen::Matrix<Scalar, 4, 1> &centroid_src,
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> &cloud_tgt_demean,
    const Eigen::Matrix<Scalar, 4, 1> &centroid_tgt,
    Matrix4 &transformation_matrix) const
{
  transformation_matrix.setIdentity ();

  // Assemble the correlation matrix H = source * target'
  Eigen::Matrix<Scalar, 3, 3> H = (cloud_src_demean * cloud_tgt_demean.transpose ()).topLeftCorner (3, 3);
  
  float angle = atan2 ((H (0, 1) - H (1, 0)), (H(0, 0) + H (1, 1)));
  
  Eigen::Matrix<Scalar, 3, 3> R (Eigen::Matrix<Scalar, 3, 3>::Identity ());
  R (0, 0) = R (1, 1) = cos (angle);
  R (0, 1) = -sin (angle);
  R (1, 0) = sin (angle);

  // Return the correct transformation
  transformation_matrix.topLeftCorner (3, 3).matrix () = R;
  const Eigen::Matrix<Scalar, 3, 1> Rc (R * centroid_src.head (3).matrix ());
  transformation_matrix.block (0, 3, 3, 1).matrix () = centroid_tgt.head (3) - Rc;
}