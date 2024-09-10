//==============================================================================
void DynamicsTest::compareAccelerations(const std::string& _fileName)
{
  using namespace std;
  using namespace Eigen;
  using namespace dart;
  using namespace math;
  using namespace dynamics;
  using namespace simulation;
  using namespace utils;

  //----------------------------- Settings -------------------------------------
  const double TOLERANCE = 1.0e-2;
#ifndef NDEBUG  // Debug mode
  int nRandomItr = 2;
#else
  int nRandomItr = 10;
#endif
  double qLB   = -0.5 * DART_PI;
  double qUB   =  0.5 * DART_PI;
  double dqLB  = -0.5 * DART_PI;
  double dqUB  =  0.5 * DART_PI;
  double ddqLB = -0.5 * DART_PI;
  double ddqUB =  0.5 * DART_PI;
  Vector3d gravity(0.0, -9.81, 0.0);
  double timeStep = 1.0e-6;

  // load skeleton
  World* world = SkelParser::readWorld(_fileName);
  assert(world != NULL);
  world->setGravity(gravity);
  world->setTimeStep(timeStep);

  //------------------------------ Tests ---------------------------------------
  for (int i = 0; i < world->getNumSkeletons(); ++i)
  {
    Skeleton* skeleton = world->getSkeleton(i);
    assert(skeleton != NULL);
    int dof = skeleton->getNumGenCoords();

    for (int j = 0; j < nRandomItr; ++j)
    {
      // Generate a random state and ddq
      VectorXd q   = VectorXd(dof);
      VectorXd dq  = VectorXd(dof);
      VectorXd ddq = VectorXd(dof);
      for (int k = 0; k < dof; ++k)
      {
        q[k]   = math::random(qLB,   qUB);
        dq[k]  = math::random(dqLB,  dqUB);
        ddq[k] = math::random(ddqLB, ddqUB);

//        q[k]   = 0.0;
//        dq[k]  = 0.0;
//        ddq[k] = 0.0;
      }
      VectorXd x = VectorXd::Zero(dof * 2);
      x << q, dq;
      skeleton->setState(x, true, true, false);
      skeleton->setGenAccs(ddq, true);

      // Integrate state
      skeleton->integrateConfigs(timeStep);
      skeleton->integrateGenVels(timeStep);
      VectorXd qNext  = skeleton->getConfigs();
      VectorXd dqNext = skeleton->getGenVels();
      VectorXd xNext  = VectorXd::Zero(dof * 2);
      xNext << qNext, dqNext;

      // For each body node
      for (int k = 0; k < skeleton->getNumBodyNodes(); ++k)
      {
        BodyNode* bn = skeleton->getBodyNode(k);
        int nDepGenCoord = bn->getNumDependentGenCoords();

        // Calculation of velocities and Jacobian at k-th time step
        skeleton->setState(x, true, true, false);
        skeleton->setGenAccs(ddq, true);
        Vector6d vBody1  = bn->getBodyVelocity();
        Vector6d vWorld1 = bn->getWorldVelocity();
        MatrixXd JBody1  = bn->getBodyJacobian();
        MatrixXd JWorld1 = bn->getWorldJacobian();
        Isometry3d T1    = bn->getWorldTransform();

        // Get accelerations and time derivatives of Jacobians at k-th time step
        Vector6d aBody1   = bn->getBodyAcceleration();
        Vector6d aWorld1  = bn->getWorldAcceleration();
        MatrixXd dJBody1  = bn->getBodyJacobianTimeDeriv();
        MatrixXd dJWorld1 = bn->getWorldJacobianTimeDeriv();

        // Calculation of velocities and Jacobian at (k+1)-th time step
        skeleton->setState(xNext, true, true, false);
        skeleton->setGenAccs(ddq, true);
        Vector6d vBody2  = bn->getBodyVelocity();
        Vector6d vWorld2 = bn->getWorldVelocity();
        MatrixXd JBody2  = bn->getBodyJacobian();
        MatrixXd JWorld2 = bn->getWorldJacobian();
        Isometry3d T2    = bn->getWorldTransform();

        // Get accelerations and time derivatives of Jacobians at k-th time step
        Vector6d aBody2   = bn->getBodyAcceleration();
        Vector6d aWorld2  = bn->getWorldAcceleration();
        MatrixXd dJBody2  = bn->getBodyJacobianTimeDeriv();
        MatrixXd dJWorld2 = bn->getWorldJacobianTimeDeriv();

        // Calculation of approximated accelerations and time derivatives of
        // Jacobians
        Vector6d aBodyApprox   = (vBody2  - vBody1)  / timeStep;
        Vector6d aWorldApprox  = (vWorld2 - vWorld1) / timeStep;

        // TODO(JS): Finite difference of Jacobian test is not implemented yet.
//        MatrixXd dJBodyApprox  = (JBody2  - JBody1)  / timeStep;
//        MatrixXd dJWorldApprox = (JWorld2 - JWorld1) / timeStep;
//        MatrixXd dJBodyApprox  = MatrixXd::Zero(6, nDepGenCoord);
//        MatrixXd dJWorldApprox = MatrixXd::Zero(6, nDepGenCoord);

//        for (int l = 0; l < nDepGenCoord; ++l)
//        {
//          skeleton->setConfig(q);
//          Jacobian JBody_a = bn->getBodyJacobian();

//          int idx = bn->getDependentGenCoordIndex(l);
//          VectorXd qGrad = q;
//          qGrad[idx] = qNext[idx];
//          skeleton->setConfig(qGrad);
//          Jacobian JBody_b = bn->getBodyJacobian();

//          Jacobian dJBody_dq = (JBody_b - JBody_a) / (qNext[idx] - q[idx]);

//          dJBodyApprox += dJBody_dq * dq[idx];
//        }

        // Comparing two velocities
        EXPECT_TRUE(equals(aBody1,   aBodyApprox,   TOLERANCE));
        EXPECT_TRUE(equals(aBody2,   aBodyApprox,   TOLERANCE));
        EXPECT_TRUE(equals(aWorld1,  aWorldApprox,  TOLERANCE));
        EXPECT_TRUE(equals(aWorld2,  aWorldApprox,  TOLERANCE));
//        EXPECT_TRUE(equals(dJBody1,  dJBodyApprox,  TOLERANCE));
//        EXPECT_TRUE(equals(dJBody2,  dJBodyApprox,  TOLERANCE));
//        EXPECT_TRUE(equals(dJWorld1, dJWorldApprox, TOLERANCE));
//        EXPECT_TRUE(equals(dJWorld2, dJWorldApprox, TOLERANCE));

        // Debugging code
        if (!equals(aBody1, aBodyApprox, TOLERANCE))
        {
          cout << "aBody1     :" << aBody1.transpose()      << endl;
          cout << "aBodyApprox:" << aBodyApprox.transpose() << endl;
        }
        if (!equals(aBody2, aBodyApprox, TOLERANCE))
        {
          cout << "aBody2     :" << aBody2.transpose()      << endl;
          cout << "aBodyApprox:" << aBodyApprox.transpose() << endl;
        }
        if (!equals(aWorld1, aWorldApprox, TOLERANCE))
        {
          cout << "aWorld1     :" << aWorld1.transpose()      << endl;
          cout << "aWorldApprox:" << aWorldApprox.transpose() << endl;
        }
        if (!equals(aWorld2, aWorldApprox, TOLERANCE))
        {
          cout << "aWorld2     :" << aWorld2.transpose()      << endl;
          cout << "aWorldApprox:" << aWorldApprox.transpose() << endl;
        }
//        if (!equals(dJBody1, dJBodyApprox, TOLERANCE))
//        {
//          cout << "Name        :" << bn->getName()        << endl;
//          cout << "dJBody1     :" << endl << dJBody1      << endl;
//          cout << "dJBodyApprox:" << endl << dJBodyApprox << endl;
//        }
//        if (!equals(dJBody2, dJBodyApprox, TOLERANCE))
//        {
//          cout << "dJBody2:"      << endl << dJBody2.transpose()      << endl;
//          cout << "dJBodyApprox:" << endl << dJBodyApprox.transpose() << endl;
//        }
//        if (!equals(dJWorld1, dJWorldApprox, TOLERANCE))
//        {
//          cout << "dJWorld1     :" << endl << dJWorld1      << endl;
//          cout << "dJWorldApprox:" << endl << dJWorldApprox << endl;
//        }
//        if (!equals(dJWorld2, dJWorldApprox, TOLERANCE))
//        {
//          cout << "dJWorld2     :" << endl << dJWorld2      << endl;
//          cout << "dJWorldApprox:" << endl << dJWorldApprox << endl;
//        }
      }
    }
  }

  delete world;
}