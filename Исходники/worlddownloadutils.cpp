  Eigen::Affine3f WorldDownloadManager::toEigenAffine(const T1 & linear,const T2 & translation)
{
  Eigen::Matrix3f l;
  Eigen::Vector3f t;

  for (uint r = 0; r < 3; r++)
    for (uint c = 0; c < 3; c++)
      l(r,c) = linear[r * 3 + c];

  for (uint r = 0; r < 3; r++)
    t[r] = translation[r];

  Eigen::Affine3f result;
  result.linear() = l;
  result.translation() = t;
  return result;
}