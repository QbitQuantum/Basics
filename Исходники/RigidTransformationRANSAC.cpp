/**
 * estimateRigidTransformationSVD
 */
void RigidTransformationRANSAC::estimateRigidTransformationSVD(
      const std::vector<Eigen::Vector3f > &srcPts,
      const std::vector<int> &srcIndices,
      const std::vector<Eigen::Vector3f > &tgtPts,
      const std::vector<int> &tgtIndices,
      Eigen::Matrix4f &transform)
{
  Eigen::Vector3f srcCentroid, tgtCentroid;

  // compute the centroids of source, target
  ComputeCentroid (srcPts, srcIndices, srcCentroid);
  ComputeCentroid (tgtPts, tgtIndices, tgtCentroid);

  // Subtract the centroids from source, target
  Eigen::MatrixXf srcPtsDemean;
  DemeanPoints(srcPts, srcIndices, srcCentroid, srcPtsDemean);

  Eigen::MatrixXf tgtPtsDemean;
  DemeanPoints(tgtPts, tgtIndices, tgtCentroid, tgtPtsDemean);

  // Assemble the correlation matrix H = source * target'
  Eigen::Matrix3f H = (srcPtsDemean * tgtPtsDemean.transpose ()).topLeftCorner<3, 3>();

  // Singular Value Decomposition
  Eigen::JacobiSVD<Eigen::Matrix3f> svd (H, Eigen::ComputeFullU | Eigen::ComputeFullV);
  Eigen::Matrix3f u = svd.matrixU ();
  Eigen::Matrix3f v = svd.matrixV ();

  // Compute R = V * U'
  if (u.determinant () * v.determinant () < 0)
  {
    for (int x = 0; x < 3; ++x)
      v (x, 2) *= -1;
  }

  // Return the transformation
  Eigen::Matrix3f R = v * u.transpose ();
  Eigen::Vector3f t = tgtCentroid - R * srcCentroid;

  // set rotation
  transform.block(0,0,3,3) = R;
  // set translation
  transform.block(0,3,3,1) = t;
  transform.block(3, 0, 1, 3).setZero();  
  transform(3,3) = 1.;
}