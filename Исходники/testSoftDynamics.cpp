//==============================================================================
void SoftDynamicsTest::compareEquationsOfMotion(const std::string& _fileName)
{
  using namespace std;
  using namespace Eigen;
  using namespace dart;
  using namespace math;
  using namespace dynamics;
  using namespace simulation;
  using namespace utils;

  //---------------------------- Settings --------------------------------------
  // Number of random state tests for each skeletons
#ifndef NDEBUG  // Debug mode
  size_t nRandomItr = 1;
#else
  size_t nRandomItr = 1;
#endif

  // Lower and upper bound of configuration for system
  double lb = -1.5 * DART_PI;
  double ub =  1.5 * DART_PI;

  // Lower and upper bound of joint damping and stiffness
  double lbD =  0.0;
  double ubD = 10.0;
  double lbK =  0.0;
  double ubK = 10.0;

  simulation::World* myWorld = NULL;

  //----------------------------- Tests ----------------------------------------
  // Check whether multiplication of mass matrix and its inverse is identity
  // matrix.
  myWorld = utils::SkelParser::readWorld(_fileName);
  EXPECT_TRUE(myWorld != NULL);

  for (size_t i = 0; i < myWorld->getNumSkeletons(); ++i)
  {
    dynamics::Skeleton* skel = myWorld->getSkeleton(i);
    dynamics::Skeleton* softSkel
        = dynamic_cast<dynamics::Skeleton*>(skel);

    int dof            = skel->getNumDofs();
//    int nBodyNodes     = skel->getNumBodyNodes();
    int nSoftBodyNodes = 0;
    if (softSkel != NULL)
      nSoftBodyNodes = softSkel->getNumSoftBodyNodes();

    if (dof == 0)
    {
      dtmsg << "Skeleton [" << skel->getName() << "] is skipped since it has "
           << "0 DOF." << endl;
      continue;
    }

    for (size_t j = 0; j < nRandomItr; ++j)
    {
      // Random joint stiffness and damping coefficient
      for (size_t k = 0; k < skel->getNumBodyNodes(); ++k)
      {
        BodyNode* body     = skel->getBodyNode(k);
        Joint*    joint    = body->getParentJoint();
        int       localDof = joint->getNumDofs();

        for (int l = 0; l < localDof; ++l)
        {
          joint->setDampingCoefficient(l, random(lbD,  ubD));
          joint->setSpringStiffness   (l, random(lbK,  ubK));

          double lbRP = joint->getPositionLowerLimit(l);
          double ubRP = joint->getPositionUpperLimit(l);
          joint->setRestPosition      (l, random(lbRP, ubRP));
        }
      }

      // Set random states
      VectorXd x = skel->getState();
      for (int k = 0; k < x.size(); ++k)
        x[k] = random(lb, ub);
      skel->setState(x);
      skel->computeForwardKinematics(true, true, false);

      //------------------------ Mass Matrix Test ----------------------------
      // Get matrices
      MatrixXd M      = skel->getMassMatrix();
      MatrixXd M2     = getMassMatrix(skel);
      MatrixXd InvM   = skel->getInvMassMatrix();
      MatrixXd M_InvM = M * InvM;
      MatrixXd InvM_M = InvM * M;

      MatrixXd AugM         = skel->getAugMassMatrix();
      MatrixXd AugM2        = getAugMassMatrix(skel);
      MatrixXd InvAugM      = skel->getInvAugMassMatrix();
      MatrixXd AugM_InvAugM = AugM * InvAugM;
      MatrixXd InvAugM_AugM = InvAugM * AugM;

      MatrixXd I        = MatrixXd::Identity(dof, dof);

      // Check if the number of generalized coordinates and dimension of mass
      // matrix are same.
      EXPECT_EQ(M.rows(), dof);
      EXPECT_EQ(M.cols(), dof);

      // Check mass matrix
      EXPECT_TRUE(equals(M, M2, 1e-6));
      if (!equals(M, M2, 1e-6))
      {
        cout << "M :" << endl << M  << endl << endl;
        cout << "M2:" << endl << M2 << endl << endl;
      }

      // Check augmented mass matrix
      EXPECT_TRUE(equals(AugM, AugM2, 1e-6));
      if (!equals(AugM, AugM2, 1e-6))
      {
        cout << "AugM :" << endl << AugM  << endl << endl;
        cout << "AugM2:" << endl << AugM2 << endl << endl;
      }

      // Check if both of (M * InvM) and (InvM * M) are identity.
      EXPECT_TRUE(equals(M_InvM, I, 1e-6));
      if (!equals(M_InvM, I, 1e-6))
      {
        cout << "InvM  :" << endl << InvM << endl << endl;
      }
      EXPECT_TRUE(equals(InvM_M, I, 1e-6));
      if (!equals(InvM_M, I, 1e-6))
      {
        cout << "InvM_M:" << endl << InvM_M << endl << endl;
      }

      // Check if both of (M * InvM) and (InvM * M) are identity.
      EXPECT_TRUE(equals(AugM_InvAugM, I, 1e-6));
      if (!equals(AugM_InvAugM, I, 1e-6))
      {
        cout << "InvAugM  :" << endl << InvAugM << endl << endl;
        cout << "InvAugM2  :" << endl << AugM.inverse() << endl << endl;
        cout << "AugM_InvAugM  :" << endl << AugM_InvAugM << endl << endl;
      }
      EXPECT_TRUE(equals(InvAugM_AugM, I, 1e-6));
      if (!equals(InvAugM_AugM, I, 1e-6))
      {
        cout << "InvAugM_AugM:" << endl << InvAugM_AugM << endl << endl;
      }

      //------- Coriolis Force Vector and Combined Force Vector Tests --------
      // Get C1, Coriolis force vector using recursive method
      VectorXd C  = skel->getCoriolisForces();
      VectorXd Cg = skel->getCoriolisAndGravityForces();

      // Get C2, Coriolis force vector using inverse dynamics algorithm
      Vector3d oldGravity = skel->getGravity();
      VectorXd oldTau     = skel->getForces();
      VectorXd oldDdq     = skel->getAccelerations();
      // TODO(JS): Save external forces of body nodes
      vector<double> oldKv(nSoftBodyNodes, 0.0);
      vector<double> oldKe(nSoftBodyNodes, 0.0);
      vector<double>  oldD(nSoftBodyNodes, 0.0);
      for (int k = 0; k < nSoftBodyNodes; ++k)
      {
        assert(softSkel != NULL);
        dynamics::SoftBodyNode* sbn = softSkel->getSoftBodyNode(k);
        oldKv[k] = sbn->getVertexSpringStiffness();
        oldKe[k] = sbn->getEdgeSpringStiffness();
        oldD[k]  = sbn->getDampingCoefficient();
      }

      skel->resetForces();
      skel->clearExternalForces();
      skel->setAccelerations(VectorXd::Zero(dof));
      for (int k = 0; k < nSoftBodyNodes; ++k)
      {
        assert(softSkel != NULL);
        dynamics::SoftBodyNode* sbn = softSkel->getSoftBodyNode(k);
        sbn->setVertexSpringStiffness(0.0);
        sbn->setEdgeSpringStiffness(0.0);
        sbn->setDampingCoefficient(0.0);
      }

      EXPECT_TRUE(skel->getForces()         == VectorXd::Zero(dof));
      EXPECT_TRUE(skel->getExternalForces() == VectorXd::Zero(dof));
      EXPECT_TRUE(skel->getAccelerations()  == VectorXd::Zero(dof));

      skel->setGravity(Vector3d::Zero());
      EXPECT_TRUE(skel->getGravity() == Vector3d::Zero());
      skel->computeInverseDynamics(false, false);
      VectorXd C2 = skel->getForces();

      skel->setGravity(oldGravity);
      EXPECT_TRUE(skel->getGravity() == oldGravity);
      skel->computeInverseDynamics(false, false);
      VectorXd Cg2 = skel->getForces();

      EXPECT_TRUE(equals(C, C2, 1e-6));
      if (!equals(C, C2, 1e-6))
      {
        cout << "C :" << C.transpose()  << endl;
        cout << "C2:" << C2.transpose() << endl;
      }

      EXPECT_TRUE(equals(Cg, Cg2, 1e-6));
      if (!equals(Cg, Cg2, 1e-6))
      {
        cout << "Cg :" << Cg.transpose()  << endl;
        cout << "Cg2:" << Cg2.transpose() << endl;
      }

      skel->setForces(oldTau);
      skel->setAccelerations(oldDdq);
      // TODO(JS): Restore external forces of body nodes
    }
  }

  delete myWorld;
}