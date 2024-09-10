/**
 * @function setRootTransform
 * @brief Set q (SCREW) from pose <x,y,z,r,p,y> 
 */
void InspectorTab::setRootTransform( dart::dynamics::Skeleton* robot, 
				     const Eigen::Matrix<double, 6, 1>& pose ) {
  dart::dynamics::Joint* joint = robot->getRootBodyNode()->getParentJoint();

  if(dynamic_cast<dart::dynamics::FreeJoint*>(joint)) {
    Matrix<double, 6, 1> q;
    Eigen::Isometry3d transform = Eigen::Isometry3d::Identity();
    transform.translation() = pose.head<3>();
    transform.linear() = dart::math::eulerXYZToMatrix(pose.tail<3>());
    q = dart::math::logMap(transform);
    joint->set_q( q );
  
  }
  else {
    Eigen::Isometry3d transform;
    transform.makeAffine();
    transform.linear() = dart::math::eulerXYZToMatrix(pose.tail<3>());
    transform.translation() = pose.head<3>();
    joint->setTransformFromParentBodyNode(transform);
  }
  
  for (int i = 0; i < robot->getNumBodyNodes(); ++i) {
    robot->getBodyNode(i)->updateTransform();
  }
}