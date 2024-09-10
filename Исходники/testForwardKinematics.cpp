//==============================================================================
TEST(FORWARD_KINEMATICS, YAW_ROLL)
{
  // Checks forward kinematics for two DoF arm manipulators.
  // NOTE: The following is the reference frame description of the world
  //       frame. The x-axis is into the page, z-axis is to the top of the
  //       page and the y-axis is to the left. At the zero angle, the links
  //       are parallel to the z-axis and face the +x-axis.

  // Create the world
  const double l1 = 1.5, l2 = 1.0;
  SkeletonPtr robot = createTwoLinkRobot(Vector3d(0.3, 0.3, l1), DOF_YAW,
                                         Vector3d(0.3, 0.3, l2), DOF_ROLL);

  // Set the test cases with the joint values and the expected end-effector
  // positions
  const std::size_t numTests = 2;
  double temp = sqrt(0.5*l2*l2);
  Vector2d joints [numTests] = { Vector2d( constantsd::pi()/4.0,  constantsd::pi()/2.0),
                                 Vector2d(-constantsd::pi()/4.0, -constantsd::pi()/4.0) };
  Vector3d expectedPos [numTests] = { Vector3d(temp, -temp, l1),
                                      Vector3d(temp / sqrt(2.0),
                                      temp / sqrt(2.0), l1+temp) };

  // Check each case by setting the joint values and obtaining the end-effector
  // position
  for (std::size_t i = 0; i < numTests; i++)
  {
    robot->setPositions(Eigen::VectorXd(joints[i]));
    BodyNode* bn = robot->getBodyNode("ee");
    Vector3d actual = bn->getTransform().translation();
    bool equality = equals(actual, expectedPos[i], 1e-3);
    EXPECT_TRUE(equality);
    if(!equality)
    {
      std::cout << "Joint values: " << joints[i].transpose() << std::endl;
      std::cout << "Actual pos: " << actual.transpose() << std::endl;
      std::cout << "Expected pos: " <<  expectedPos[i].transpose() << std::endl;
    }
  }
}