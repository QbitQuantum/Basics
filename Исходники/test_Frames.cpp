TEST(FRAMES, FORWARD_KINEMATICS_CHAIN)
{
  std::vector<SimpleFrame*> frames;

  double tolerance = 1e-6;

  SimpleFrame A(Frame::World(), "A");
  frames.push_back(&A);
  SimpleFrame B(&A, "B");
  frames.push_back(&B);
  SimpleFrame C(&B, "C");
  frames.push_back(&C);
  SimpleFrame D(&C, "D");
  frames.push_back(&D);

  // -- Test Position --------------------------------------------------------
  EXPECT_TRUE( equals(D.getTransform().matrix(),
                      Eigen::Isometry3d::Identity().matrix(),
                      tolerance));

  Eigen::aligned_vector<Eigen::Isometry3d> tfs;
  tfs.resize(frames.size(), Eigen::Isometry3d::Identity());

  randomize_transforms(tfs);

  for(std::size_t i=0; i<frames.size(); ++i)
  {
    SimpleFrame* F = frames[i];
    F->setRelativeTransform(tfs[i]);
  }

  for(std::size_t i=0; i<frames.size(); ++i)
  {
    Frame* F = frames[i];
    Eigen::Isometry3d expectation(Eigen::Isometry3d::Identity());
    for(std::size_t j=0; j<=i; ++j)
    {
      expectation = expectation * tfs[j];
    }

    Eigen::Isometry3d actual = F->getTransform();
    EXPECT_TRUE( equals(actual.matrix(), expectation.matrix(), tolerance));
  }

  randomize_transforms(tfs);
  for(std::size_t i=0; i<frames.size(); ++i)
  {
    SimpleFrame* F = frames[i];
    F->setRelativeTransform(tfs[i]);
  }

  Eigen::Isometry3d expectation(Eigen::Isometry3d::Identity());
  for(std::size_t j=0; j<frames.size(); ++j)
    expectation = expectation * tfs[j];

  EXPECT_TRUE( equals(frames.back()->getTransform().matrix(),
                      expectation.matrix(),
                      tolerance) );


  // -- Test Velocity --------------------------------------------------------

  // Basic forward spatial velocity propagation
  { // The brackets are to allow reusing variable names
    Eigen::aligned_vector<Eigen::Vector6d> v_rels(frames.size());
    Eigen::aligned_vector<Eigen::Vector6d> v_total(frames.size());

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      v_rels[i] = random_vec<6>();

      SimpleFrame* F = frames[i];
      F->setRelativeSpatialVelocity(v_rels[i]);

      if(i>0)
        compute_spatial_velocity(v_total[i-1], v_rels[i],
            F->getRelativeTransform(), v_total[i]);
      else
        compute_spatial_velocity(Eigen::Vector6d::Zero(), v_rels[i],
                                 F->getRelativeTransform(), v_total[i]);
    }

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      SimpleFrame* F = frames[i];

      Eigen::Vector6d v_actual = F->getSpatialVelocity();

      EXPECT_TRUE( equals(v_total[i], v_actual) );
    }
  }

  // Testing conversion beteween spatial and classical velocities
  {
    std::vector<Eigen::Vector3d> v_rels(frames.size());
    std::vector<Eigen::Vector3d> w_rels(frames.size());

    std::vector<Eigen::Vector3d> v_total(frames.size());
    std::vector<Eigen::Vector3d> w_total(frames.size());

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      v_rels[i] = random_vec<3>();
      w_rels[i] = random_vec<3>();

      SimpleFrame* F = frames[i];
      F->setClassicDerivatives(v_rels[i], w_rels[i]);

      Eigen::Vector3d offset = F->getRelativeTransform().translation();

      Eigen::Isometry3d tf = i>0? frames[i-1]->getTransform() :
          Eigen::Isometry3d::Identity();

      if(i>0)
        compute_velocity(v_total[i-1], w_total[i-1], v_rels[i], w_rels[i],
            offset, tf, v_total[i], w_total[i]);
      else
        compute_velocity(Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                         v_rels[i], w_rels[i],
                         offset, tf, v_total[i], w_total[i]);
    }

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      SimpleFrame* F = frames[i];
      Eigen::Vector3d v_actual = F->getLinearVelocity();
      Eigen::Vector3d w_actual = F->getAngularVelocity();

      EXPECT_TRUE( equals(v_total[i], v_actual, tolerance) );
      EXPECT_TRUE( equals(w_total[i], w_actual, tolerance) );
    }
  }

  // -- Acceleration ---------------------------------------------------------

  // Basic forward spatial acceleration propagation
  {
    Eigen::aligned_vector<Eigen::Vector6d> v_rels(frames.size());
    Eigen::aligned_vector<Eigen::Vector6d> a_rels(frames.size());

    Eigen::aligned_vector<Eigen::Vector6d> v_total(frames.size());
    Eigen::aligned_vector<Eigen::Vector6d> a_total(frames.size());


    for(std::size_t i=0; i<frames.size(); ++i)
    {
      v_rels[i] = random_vec<6>();
      a_rels[i] = random_vec<6>();

      SimpleFrame* F = frames[i];
      F->setRelativeSpatialVelocity(v_rels[i]);
      F->setRelativeSpatialAcceleration(a_rels[i]);
      Eigen::Isometry3d tf = F->getRelativeTransform();

      if(i>0)
      {
        compute_spatial_velocity(v_total[i-1], v_rels[i], tf, v_total[i]);
        compute_spatial_acceleration(a_total[i-1], a_rels[i], v_total[i],
            v_rels[i], tf, a_total[i]);
      }
      else
      {
        compute_spatial_velocity(Eigen::Vector6d::Zero(), v_rels[i],
                                 tf, v_total[i]);
        compute_spatial_acceleration(Eigen::Vector6d::Zero(), a_rels[i],
                                     v_total[i], v_rels[i], tf, a_total[i]);
      }
    }

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      SimpleFrame* F = frames[i];

      Eigen::Vector6d a_actual = F->getSpatialAcceleration();

      EXPECT_TRUE( equals(a_total[i], a_actual) );
    }

    // Test relative computations
    for(std::size_t i=0; i<frames.size(); ++i)
    {
      Frame* F = frames[i];
      Frame* P = F->getParentFrame();

      Eigen::Vector6d v_rel = F->getSpatialVelocity(P, F);
      Eigen::Vector6d a_rel = F->getSpatialAcceleration(P, F);

      EXPECT_TRUE( equals(v_rels[i], v_rel, tolerance) );
      EXPECT_TRUE( equals(a_rels[i], a_rel, tolerance) );
    }

    // Test offset computations
    for(std::size_t i=0; i<frames.size(); ++i)
    {
      Eigen::Vector3d offset = random_vec<3>();
      Frame* F = frames[i];

      Eigen::Vector3d v_actual = F->getLinearVelocity(offset);
      Eigen::Vector3d w_actual = F->getAngularVelocity();
      Eigen::Vector3d v_expect, w_expect;
      compute_velocity(F->getLinearVelocity(), F->getAngularVelocity(),
                       Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                       offset, F->getWorldTransform(), v_expect, w_expect);

      EXPECT_TRUE( equals( v_expect, v_actual) );
      EXPECT_TRUE( equals( w_expect, w_actual) );

      Eigen::Vector3d a_actual = F->getLinearAcceleration(offset);
      Eigen::Vector3d alpha_actual = F->getAngularAcceleration();
      Eigen::Vector3d a_expect, alpha_expect;
      compute_acceleration(F->getLinearAcceleration(),
                           F->getAngularAcceleration(), F->getAngularVelocity(),
                           Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                           Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                           offset, F->getWorldTransform(),
                           a_expect, alpha_expect);

      EXPECT_TRUE( equals( a_expect, a_actual) );
      EXPECT_TRUE( equals( alpha_expect, alpha_actual) );
    }
  }

  // Testing conversion between spatial and classical accelerations
  {
    std::vector<Eigen::Vector3d> v_rels(frames.size());
    std::vector<Eigen::Vector3d> w_rels(frames.size());
    std::vector<Eigen::Vector3d> a_rels(frames.size());
    std::vector<Eigen::Vector3d> alpha_rels(frames.size());

    std::vector<Eigen::Vector3d> v_total(frames.size());
    std::vector<Eigen::Vector3d> w_total(frames.size());
    std::vector<Eigen::Vector3d> a_total(frames.size());
    std::vector<Eigen::Vector3d> alpha_total(frames.size());

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      v_rels[i] = random_vec<3>();
      w_rels[i] = random_vec<3>();
      a_rels[i] = random_vec<3>();
      alpha_rels[i] = random_vec<3>();

      SimpleFrame* F = frames[i];
      Eigen::Isometry3d rel_tf;
      randomize_transform(rel_tf);
      F->setRelativeTransform(rel_tf);
      F->setClassicDerivatives(v_rels[i], w_rels[i], a_rels[i], alpha_rels[i]);

      Eigen::Vector3d offset = F->getRelativeTransform().translation();

      Eigen::Isometry3d tf = i>0? frames[i-1]->getTransform() :
          Eigen::Isometry3d::Identity();

      if(i>0)
      {
        compute_velocity(v_total[i-1], w_total[i-1], v_rels[i], w_rels[i],
            offset, tf, v_total[i], w_total[i]);
        compute_acceleration(a_total[i-1], alpha_total[i-1], w_total[i-1],
            a_rels[i], alpha_rels[i], v_rels[i], w_rels[i], offset, tf,
            a_total[i], alpha_total[i]);
      }
      else
      {
        compute_velocity(Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                         v_rels[i], w_rels[i], offset, tf,
                         v_total[i], w_total[i]);
        compute_acceleration(Eigen::Vector3d::Zero(), Eigen::Vector3d::Zero(),
                             Eigen::Vector3d::Zero(), a_rels[i], alpha_rels[i],
                             v_rels[i], w_rels[i], offset, tf,
                             a_total[i], alpha_total[i]);
      }
    }

    for(std::size_t i=0; i<frames.size(); ++i)
    {
      SimpleFrame* F = frames[i];
      Eigen::Vector3d v_actual = F->getLinearVelocity();
      Eigen::Vector3d w_actual = F->getAngularVelocity();
      Eigen::Vector3d a_actual = F->getLinearAcceleration();
      Eigen::Vector3d alpha_actual = F->getAngularAcceleration();

      EXPECT_TRUE( equals(v_total[i], v_actual, tolerance) );
      EXPECT_TRUE( equals(w_total[i], w_actual, tolerance) );
      EXPECT_TRUE( equals(a_total[i], a_actual, tolerance) );
      EXPECT_TRUE( equals(alpha_total[i], alpha_actual, tolerance) );
    }

    // Test relative computations
    for(std::size_t i=0; i<frames.size(); ++i)
    {
      SimpleFrame* F = frames[i];
      Frame* P = F->getParentFrame();
      Eigen::Vector3d v_rel = F->getLinearVelocity(P, P);
      Eigen::Vector3d w_rel = F->getAngularVelocity(P, P);
      Eigen::Vector3d a_rel = F->getLinearAcceleration(P, P);
      Eigen::Vector3d alpha_rel = F->getAngularAcceleration(P, P);

      EXPECT_TRUE( equals(v_rels[i], v_rel, tolerance) );
      EXPECT_TRUE( equals(w_rels[i], w_rel, tolerance) );
      EXPECT_TRUE( equals(a_rels[i], a_rel, tolerance) );
      EXPECT_TRUE( equals(alpha_rels[i], alpha_rel, tolerance) );
    }
  }
}