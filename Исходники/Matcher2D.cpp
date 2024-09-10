// refine the plane given set of inlier points
gtsam::Pose2 PoseEstimator::refine(const Datums& ps, const Mask& mask,
    boost::optional<Model> bestModel) {

  // filter inlier
  std::vector<Point2Pair> putatives;
  for (size_t i = 0; i < ps.size(); i++) {
    if (!mask[i]) continue;
    putatives.push_back(ps[i]);
  }

  // check inlier size
  if (putatives.size() < 2)
    throw std::runtime_error("minimal pose solver must have input inlier size >= 2");

  // method of 'A Method for Registration of 3­D Shapes', by Besl and McKay, 1992
  // TODO: not sure this is correct in 2D
  // 1. find centroids of each dataset
  Vector2 cent1 = zero(2);
  Vector2 cent2 = zero(2);
  for (size_t i = 0; i < putatives.size(); i++) {
    cent1 += putatives[i].first.vector();
    cent2 += putatives[i].second.vector();
  }
  cent1 = cent1 / static_cast<double>(putatives.size());
  cent2 = cent2 / static_cast<double>(putatives.size());

  // 2. SVD
  Matrix H = zeros(2,2);
  for (size_t i = 0; i < putatives.size(); i++)
    H = H + (putatives[i].first.vector() - cent1) *
        (putatives[i].second.vector() - cent1).transpose();

  Matrix U,V;
  Vector S;
  svd(H, U, S, V);

  // 3. get rotation matrix
  Matrix R = V * U.transpose();
  if (R.determinant() < 0) {
    V(0,1) = -V(0,1);
    V(1,1) = -V(1,1);
    R = V * U.transpose();
  }

  // 4. translation
  Vector2 t = -R * cent1 + cent2;
  return Pose2(Rot2(atan2(R(1,0), R(0,0))), Point2(t));
}