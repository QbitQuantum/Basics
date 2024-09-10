bool MyWindow::transformSegmentAtSample(std::string segmentName,
                                        int timeStep)
{

  Eigen::VectorXd segmentConfig;
  if (mInputMotion->getSegmentConfig(timeStep, segmentName, &segmentConfig))
  {
    if (segmentName == "root")
    {

      // Transform Root
      Eigen::Vector6d r_t = segmentConfig;

      // r_t:       head(3)->translation, tail(3)->rotation
      // FreeJoint: head(3)->rotation, tail(3)->translation

      Eigen::Isometry3d tf;
      tf.linear() = dart::math::eulerXYZToMatrix(r_t.tail(3)*deg_to_rad);
      //tf.linear() = dart::math::eulerZYXToMatrix(r_t.tail(3)*deg_to_rad);
      tf.translation() = r_t.head(3)*unit;
      mSkel->getJoint("root_joint")
           ->setPositions(dart::dynamics::FreeJoint::convertToPositions(tf));
      return true;
    }
    else
    {
      // other bones
      // prepare reference frame
      Eigen::Vector3d segmentAxes;
      if (mAsfData->getSegmentAxes(segmentName, &segmentAxes))
      {
        Eigen::Matrix3d refFrame = dart::math::eulerXYZToMatrix(segmentAxes*deg_to_rad);
        //Eigen::Matrix3d refFrame = dart::math::eulerZYXToMatrix(segmentAxes*deg_to_rad);
        // calculate motion transformation
        Eigen::Matrix3d motionRot = dart::math::eulerXYZToMatrix(segmentConfig*deg_to_rad);
        //Eigen::Matrix3d motionRot = dart::math::eulerZYXToMatrix(segmentConfig*deg_to_rad);
        Eigen::Isometry3d finalTF;
        //finalTF.linear() = refFrame.inverse() * motionRot * refFrame;
        finalTF.linear() = refFrame * motionRot * refFrame.inverse();
        //finalTF.linear() = motionRot;

        // transform
        mSkel->getBodyNode(segmentName)->getParentBodyNode()->getParentJoint()
             ->setPositions(dart::dynamics::BallJoint::convertToPositions(finalTF.linear()));


        std::cout << segmentName << std::endl;
        std::cout << mSkel->getBodyNode(segmentName)->getParentJoint()
            ->getName() << std::endl;
        std::cout << mSkel->getBodyNode(segmentName)->getRelativeTransform().linear()
                  << std::endl;


        std::cout << mSkel->getJoint(segmentName+"_joint")->getPositions() << std::endl;

        return true;

      }
      std::cout << "segment transform fail" << std::endl;
      return false;
    }
  }
  return false;
}