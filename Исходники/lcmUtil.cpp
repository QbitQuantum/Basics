Eigen::Isometry3d DecodePose(const bot_core::position_3d_t& msg) {
  Isometry3d ret;
  ret.translation() = DecodeVector3d(msg.translation);
  auto quaternion = DecodeQuaternion(msg.rotation);
  ret.linear() = drake::math::quat2rotmat(quaternion);
  ret.makeAffine();
  return ret;
}