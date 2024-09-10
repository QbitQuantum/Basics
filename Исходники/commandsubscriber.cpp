bool CommandSubscriber::getForcedTfFrame(Eigen::Affine3f & result) const
  {
  tf::StampedTransform transform;
  try
    {
    m_tf_listener.lookupTransform(m_forced_tf_frame_reference,m_forced_tf_frame_name,ros::Time(0),transform);
    }
    catch (tf::TransformException ex)
      {
      ROS_ERROR("kinfu: hint was forced by TF, but retrieval failed because: %s",ex.what());
      return false;
      }

  Eigen::Vector3f vec;
  vec.x() = transform.getOrigin().x();
  vec.y() = transform.getOrigin().y();
  vec.z() = transform.getOrigin().z();
  Eigen::Quaternionf quat;
  quat.x() = transform.getRotation().x();
  quat.y() = transform.getRotation().y();
  quat.z() = transform.getRotation().z();
  quat.w() = transform.getRotation().w();

  result.linear() = Eigen::AngleAxisf(quat).matrix();
  result.translation() = vec;
  return true;
  }