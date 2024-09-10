void
publishTfTransform(const Sophus::SE3& T, const ros::Time& stamp,
                   const string& frame_id, const string& child_frame_id,
                   tf::TransformBroadcaster& br)
{
  tf::Transform transform_msg;
  Eigen::Quaterniond q(T.rotationMatrix());
  transform_msg.setOrigin(tf::Vector3(T.translation().x(), T.translation().y(), T.translation().z()));
  tf::Quaternion tf_q; tf_q.setX(q.x()); tf_q.setY(q.y()); tf_q.setZ(q.z()); tf_q.setW(q.w());
  transform_msg.setRotation(tf_q);
  br.sendTransform(tf::StampedTransform(transform_msg, stamp, frame_id, child_frame_id));
}