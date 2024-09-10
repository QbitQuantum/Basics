TEST_F(FclCollisionDetectionTester, ContactReporting)
{
  collision_detection::CollisionRequest req;
  req.contacts = true;
  req.max_contacts = 1;

  robot_state::RobotState kstate(kmodel_);
  kstate.setToDefaultValues();
  kstate.update();

  Eigen::Affine3d offset = Eigen::Affine3d::Identity();
  offset.translation().x() = .01;

  //  kstate.getLinkState("base_link")->updateGivenGlobalLinkTransform(Eigen::Affine3d::Identity());
  //  kstate.getLinkState("base_bellow_link")->updateGivenGlobalLinkTransform(offset);
  //  kstate.getLinkState("r_gripper_palm_link")->updateGivenGlobalLinkTransform(Eigen::Affine3d::Identity());
  //  kstate.getLinkState("l_gripper_palm_link")->updateGivenGlobalLinkTransform(offset);

  kstate.updateStateWithLinkAt("base_link", Eigen::Affine3d::Identity());
  kstate.updateStateWithLinkAt("base_bellow_link", offset);
  kstate.updateStateWithLinkAt("r_gripper_palm_link", Eigen::Affine3d::Identity());
  kstate.updateStateWithLinkAt("l_gripper_palm_link", offset);
  kstate.update();

  acm_->setEntry("base_link", "base_bellow_link", false);
  acm_->setEntry("r_gripper_palm_link", "l_gripper_palm_link", false);

  collision_detection::CollisionResult res;
  crobot_->checkSelfCollision(req, res, kstate, *acm_);
  ASSERT_TRUE(res.collision);
  EXPECT_EQ(res.contacts.size(),1);
  EXPECT_EQ(res.contacts.begin()->second.size(),1);

  res.clear();
  req.max_contacts = 2;
  req.max_contacts_per_pair = 1;
  //  req.verbose = true;
  crobot_->checkSelfCollision(req, res, kstate, *acm_);
  ASSERT_TRUE(res.collision);
  EXPECT_EQ(res.contacts.size(), 2);
  EXPECT_EQ(res.contacts.begin()->second.size(),1);

  res.contacts.clear();
  res.contact_count = 0;

  req.max_contacts = 10;
  req.max_contacts_per_pair = 2;
  acm_.reset(new collision_detection::AllowedCollisionMatrix(kmodel_->getLinkModelNames(), false));
  crobot_->checkSelfCollision(req, res, kstate, *acm_);
  ASSERT_TRUE(res.collision);
  EXPECT_LE(res.contacts.size(), 10);
  EXPECT_LE(res.contact_count, 10);
}