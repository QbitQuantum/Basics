Eigen::Matrix4f ConsistencyTest::initPose2D( std::map<unsigned, unsigned> &matched_planes )
{
  //Calculate rotation
  Matrix3f normalCovariances = Matrix3f::Zero();
  for(map<unsigned, unsigned>::iterator it = matched_planes.begin(); it != matched_planes.end(); it++)
    normalCovariances += PBMTarget.vPlanes[it->second].v3normal * PBMSource.vPlanes[it->first].v3normal.transpose();
  normalCovariances(1,1) += 100; // Rotation "restricted" to the y axis

  JacobiSVD<MatrixXf> svd(normalCovariances, ComputeThinU | ComputeThinV);
  Matrix3f Rotation = svd.matrixU() * svd.matrixV().transpose();

  if(Rotation.determinant() < 0)
//    Rotation.row(2) *= -1;
    Rotation = -Rotation;

  // Calculate translation
  Vector3f translation;
  Vector3f center_data = Vector3f::Zero(), center_model = Vector3f::Zero();
  Vector3f centerFull_data = Vector3f::Zero(), centerFull_model = Vector3f::Zero();
  unsigned numFull = 0, numNonStruct = 0;
  for(map<unsigned, unsigned>::iterator it = matched_planes.begin(); it != matched_planes.end(); it++)
  {
    if(PBMSource.vPlanes[it->first].bFromStructure) // The certainty in center of structural planes is too low
      continue;

    ++numNonStruct;
    center_data += PBMSource.vPlanes[it->first].v3center;
    center_model += PBMTarget.vPlanes[it->second].v3center;
    if(PBMSource.vPlanes[it->first].bFullExtent)
    {
      centerFull_data += PBMSource.vPlanes[it->first].v3center;
      centerFull_model += PBMTarget.vPlanes[it->second].v3center;
      ++numFull;
    }
  }
  if(numFull > 0)
  {
    translation = (-centerFull_model + Rotation * centerFull_data) / numFull;
  }
  else
  {
    translation = (-center_model + Rotation * center_data) / numNonStruct;
  }

  translation[1] = 0; // Restrict no translation in the y axis

  // Form SE3 transformation matrix. This matrix maps the model into the current data reference frame
  Eigen::Matrix4f rigidTransf;
  rigidTransf.block(0,0,3,3) = Rotation;
  rigidTransf.block(0,3,3,1) = translation;
  rigidTransf.row(3) << 0,0,0,1;
  return rigidTransf;
}