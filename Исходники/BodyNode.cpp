double BodyNode::TransformObjFunc::eval(Eigen::Map<const Eigen::VectorXd>& _x)
{
  assert(mBodyNode->getParentJoint()->getNumGenCoords() == _x.size());

  // Update forward kinematics information with _x
  // We are just insterested in transformation of mBodyNode
  mBodyNode->getParentJoint()->setConfigs(_x, true, false, false);

  // Compute and return the geometric distance between body node transformation
  // and target transformation
  Eigen::Isometry3d bodyT = mBodyNode->getWorldTransform();
  Eigen::Vector6d dist = math::logMap(bodyT.inverse() * mT);
  return dist.dot(dist);
}