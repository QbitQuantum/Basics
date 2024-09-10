geometry_msgs::Pose C_HunoLimbKinematics::ForwardKinematics(const double *thetas_C)
{ 
  geometry_msgs::Pose outLimbPose;
  Eigen::Vector3d rot_axis = Eigen::Vector3d::Zero();
  double rot_angle;

  Eigen::Matrix4d limbTF = Eigen::Matrix4d::Identity();
  Eigen::Matrix4d expXihatTheta = Eigen::Matrix4d::Identity();
  Eigen::Matrix<double, 6, 5> tempJacobian;
  tempJacobian.setZero(); // initialize temporary variable to zeros
  int limbCtr = 0;

  /* Lock jacobian matrix while being formed */
  m_isJacobianLocked = true;

  /* Calculate joint transformation matrices sequentially and populate jacobian */
  for (int jointIdx = 0; jointIdx < m_numJoints; jointIdx++)
  {
    /* use previous expXihatTheta to generate adjoint matrix
       and fill next column of jacobian */
    tempJacobian.col(limbCtr) = AdjointMatrix(expXihatTheta) * m_zetas_M.col(jointIdx);

    /* calculate for next joint */
    expXihatTheta = ExpXihatTheta(jointIdx, (*(thetas_C+jointIdx))*DEG2RAD);
    limbTF *= expXihatTheta;

    /* increment counter */
    limbCtr++; 
  }
  
  if (limbCtr == m_numJoints)
  {
    limbTF *= m_g0Mat_M; // apply configuration matrix 
    m_jacobian_M = tempJacobian.block(0,0, m_numJoints, m_numJoints); // save jacobian
    
    m_isJacobianLocked = false; // unlock jacobian matrix
  }
  else
  { // reset matrices since something didn't add up.
    limbTF.setZero();
    m_jacobian_M.setZero();
  }

  /* save limb transformation matrix into pose message */
  outLimbPose.position.x = limbTF(0,3);
  outLimbPose.position.y = limbTF(1,3);
  outLimbPose.position.z = limbTF(2,3);

  //back out rotation unit vector and angle from rotation matrix
  rot_angle = acos( ( ((limbTF.block<3,3>(0,0)).trace())-1 ) /2 );
  if (sin(rot_angle) != 0)
  {
    rot_axis(0) = (limbTF(2,1)-limbTF(1,2)) / (2*sin(rot_angle));
    rot_axis(1) = (limbTF(0,2)-limbTF(2,0)) / (2*sin(rot_angle));
    rot_axis(2) = (limbTF(1,0)-limbTF(0,1)) / (2*sin(rot_angle));
  }
  // else rot_axis is zeroes

  outLimbPose.orientation.x = rot_axis(0)*sin(rot_angle/2);
  outLimbPose.orientation.y = rot_axis(1)*sin(rot_angle/2);
  outLimbPose.orientation.z = rot_axis(2)*sin(rot_angle/2);
  outLimbPose.orientation.w = cos(rot_angle/2);

  return outLimbPose; 
} // end ForwardKinematics()