bool RosMessageContext::getOdomPose(Eigen::Isometry3d& _trans, double time){
  bool transformFound = true;
  _tfListener->waitForTransform(_odomReferenceFrameId, _baseReferenceFrameId,
				ros::Time(time), ros::Duration(1.0));
  try{
    tf::StampedTransform t;
    _tfListener->lookupTransform(_odomReferenceFrameId, _baseReferenceFrameId,
				 ros::Time(time), t);
    Eigen::Isometry3d transform;
    transform.translation().x()=t.getOrigin().x();
    transform.translation().y()=t.getOrigin().y();
    transform.translation().z()=t.getOrigin().z();
    Eigen::Quaterniond rot;
    rot.x()=t.getRotation().x();
    rot.y()=t.getRotation().y();
    rot.z()=t.getRotation().z();
    rot.w()=t.getRotation().w();
    transform.linear()=rot.toRotationMatrix();
    _trans = transform;
    transformFound = true;
  }
  catch (tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    transformFound = false;
  }
  return transformFound;
}