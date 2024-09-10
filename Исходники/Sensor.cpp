/**
 * @brief Sensor::getInplaneTransform
 * @param pt
 * @param normal
 * @param pose
 */
void Sensor::getInplaneTransform(const Eigen::Vector3f &pt, const Eigen::Vector3f &normal, Eigen::Matrix4f &pose)
{
  pose.setIdentity();

  Eigen::Vector3f px, py;
  Eigen::Vector3f pz = normal;

  if (pt.dot(pz) > 0) pz *= -1;
  px = (Eigen::Vector3f(1,0,0).cross(pz)).normalized();
  py = (pz.cross(px)).normalized();

  pose.block<3,1>(0,0) = px;
  pose.block<3,1>(0,1) = py;
  pose.block<3,1>(0,2) = pz;
  pose.block<3,1>(0,3) = pt;

//  std::vector<Eigen::Vector3f> pts0(4), pts1(4);
//  std::vector<int> indices(4,0);
//  indices[1] = 1, indices[2] = 2, indices[3] = 3;
//  pts0[0] = Eigen::Vector3f(0,0,0), pts0[1] = Eigen::Vector3f(1,0,0);
//  pts0[2] = Eigen::Vector3f(0,1,0), pts0[3] = Eigen::Vector3f(0,0,1);

//  pts1[0] = pt;
//  pts1[3] = normal.normalized();

//  if (pts1[0].dot(pts1[3]) > 0)
//    pts1[3] *= -1;

//  pts1[1] = (pts0[1].cross(pts1[3])).normalized();
//  pts1[2] = (pts1[3].cross(pts1[1])).normalized();

//  pts1[1]+=pts1[0];
//  pts1[2]+=pts1[0];
//  pts1[3]+=pts1[0];

//  v4r::RigidTransformationRANSAC rt;
//  rt.estimateRigidTransformationSVD(pts0, indices, pts1, indices, pose);
}