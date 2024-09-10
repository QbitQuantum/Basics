void MotionCombinator::update(JointRequest& jointRequest)
{
  specialActionOdometry += theSpecialActionsOutput.odometryOffset;

  const JointRequest* jointRequests[MotionRequest::numOfMotions];
  jointRequests[MotionRequest::walk] = &theWalkingEngineOutput;
  jointRequests[MotionRequest::kick] = &theKickEngineOutput;
  jointRequests[MotionRequest::specialAction] = &theSpecialActionsOutput;
  jointRequests[MotionRequest::stand] = &theStandOutput;
  jointRequests[MotionRequest::getUp] = &theGetUpEngineOutput;
  jointRequests[MotionRequest::dmpKick] = &theDmpKickEngineOutput;

  const JointRequest* armJointRequests[ArmMotionRequest::numOfArmMotions];
  armJointRequests[ArmMotionRequest::none] = &theNonArmeMotionEngineOutput;
  armJointRequests[ArmMotionRequest::keyFrame] = &theArmKeyFrameEngineOutput;

  jointRequest.angles[Joints::headYaw] = theHeadJointRequest.pan;
  jointRequest.angles[Joints::headPitch] = theHeadJointRequest.tilt;

  copy(*jointRequests[theMotionSelection.targetMotion], jointRequest);

  ASSERT(jointRequest.isValid());

  // Find fully active motion and set MotionInfo
  if(theMotionSelection.ratios[theMotionSelection.targetMotion] == 1.f)
  {
    Pose2f odometryOffset;
    // default values
    motionInfo.motion = theMotionSelection.targetMotion;
    motionInfo.isMotionStable = true;
    motionInfo.upcomingOdometryOffset = Pose2f();

    lastJointAngles = theJointAngles;

    switch(theMotionSelection.targetMotion)
    {
      case MotionRequest::walk:
        odometryOffset = theWalkingEngineOutput.odometryOffset;
        motionInfo.walkRequest = theWalkingEngineOutput.executedWalk;
        motionInfo.upcomingOdometryOffset = theWalkingEngineOutput.upcomingOdometryOffset;
        break;
      case MotionRequest::kick:
        odometryOffset = theKickEngineOutput.odometryOffset;
        motionInfo.kickRequest = theKickEngineOutput.executedKickRequest;
        motionInfo.isMotionStable = theKickEngineOutput.isStable;
        break;
      case MotionRequest::specialAction:
        odometryOffset = specialActionOdometry;
        specialActionOdometry = Pose2f();
        motionInfo.specialActionRequest = theSpecialActionsOutput.executedSpecialAction;
        motionInfo.isMotionStable = theSpecialActionsOutput.isMotionStable;
        break;
      case MotionRequest::getUp:
        motionInfo.isMotionStable = false;
        odometryOffset = theGetUpEngineOutput.odometryOffset;
        break;
      case MotionRequest::stand:
      case MotionRequest::dmpKick:
      default:
        break;
    }

    if(theRobotInfo.hasFeature(RobotInfo::zGyro) && (theFallDownState.state == FallDownState::upright || theMotionSelection.targetMotion == MotionRequest::getUp))
    {
      Vector3f rotatedGyros = theInertialData.orientation * theInertialData.gyro.cast<float>();
      odometryOffset.rotation = rotatedGyros.z() * theFrameInfo.cycleTime;
    }

    odometryData += odometryOffset;
    ASSERT(jointRequest.isValid());
  }
  else // interpolate motions
  {
    const bool interpolateStiffness = !(theMotionSelection.targetMotion != MotionRequest::specialAction && theMotionSelection.specialActionRequest.specialAction == SpecialActionRequest::playDead &&
                                       theMotionSelection.ratios[MotionRequest::specialAction] > 0.f); // do not interpolate from play_dead
    for(int i = 0; i < MotionRequest::numOfMotions; ++i)
      if(i != theMotionSelection.targetMotion && theMotionSelection.ratios[i] > 0.)
      {
        interpolate(*jointRequests[i], *jointRequests[theMotionSelection.targetMotion], theMotionSelection.ratios[i], jointRequest, interpolateStiffness, Joints::headYaw, Joints::headPitch);
        if(theArmMotionSelection.armRatios[ArmMotionRequest::none] == 1)
          interpolate(*jointRequests[i], *jointRequests[theMotionSelection.targetMotion], theMotionSelection.ratios[i], jointRequest, interpolateStiffness, Joints::lShoulderPitch, Joints::lHand);
        if(theArmMotionSelection.armRatios[theArmMotionSelection.rightArmRatiosOffset + ArmMotionRequest::none] == 1)
          interpolate(*jointRequests[i], *jointRequests[theMotionSelection.targetMotion], theMotionSelection.ratios[i], jointRequest, interpolateStiffness, Joints::rShoulderPitch, Joints::rHand);
        interpolate(*jointRequests[i], *jointRequests[theMotionSelection.targetMotion], theMotionSelection.ratios[i], jointRequest, interpolateStiffness, Joints::lHipYawPitch, Joints::rAnkleRoll);
      }
  }

  ASSERT(jointRequest.isValid());

  auto combinateArmMotions = [&](Arms::Arm const arm)
  {
    const int ratioIndexOffset = arm * theArmMotionSelection.rightArmRatiosOffset;
    const Joints::Joint startJoint = arm == Arms::left ? Joints::lShoulderPitch : Joints::rShoulderPitch;
    const Joints::Joint endJoint = arm == Arms::left ? Joints::lHand : Joints::rHand;

    if(theArmMotionSelection.armRatios[ratioIndexOffset + ArmMotionRequest::none] != 1.f)
    {
      if(theArmMotionSelection.armRatios[ratioIndexOffset + ArmMotionRequest::none] > 0 &&
         ArmMotionRequest::none != theArmMotionSelection.targetArmMotion[arm])
        copy(jointRequest, theNonArmeMotionEngineOutput, startJoint, endJoint);

      if(ArmMotionRequest::none != theArmMotionSelection.targetArmMotion[arm])
        copy(*armJointRequests[theArmMotionSelection.targetArmMotion[arm]], jointRequest, startJoint, endJoint);
    }

    if(theArmMotionSelection.armRatios[ratioIndexOffset + theArmMotionSelection.targetArmMotion[arm]] == 1.f)
    {
      armMotionInfo.armMotion[arm] = theArmMotionSelection.targetArmMotion[arm];

      switch(theArmMotionSelection.targetArmMotion[arm])
      {
        case ArmMotionRequest::keyFrame:
          armMotionInfo.armKeyFrameRequest = theArmMotionSelection.armKeyFrameRequest;
          break;
        case ArmMotionRequest::none:
        default:
          break;
      }
    }
    else
    {
      const bool interpolateStiffness = !(theMotionSelection.targetMotion != MotionRequest::specialAction &&
                                         theMotionSelection.specialActionRequest.specialAction == SpecialActionRequest::playDead &&
                                         theMotionSelection.ratios[MotionRequest::specialAction] > 0.f &&
                                         theArmMotionSelection.armRatios[ratioIndexOffset + ArmMotionRequest::none] > 0);

      const JointRequest toJointRequest = theArmMotionSelection.targetArmMotion[arm] == ArmMotionRequest::none ?
                                          *jointRequests[theMotionSelection.targetMotion] : *armJointRequests[theArmMotionSelection.targetArmMotion[arm]];

      for(int i = 0; i < ArmMotionRequest::numOfArmMotions; ++i)
      {
        if(i != theArmMotionSelection.targetArmMotion[arm] && theArmMotionSelection.armRatios[ratioIndexOffset + i] > 0)
        {
          interpolate(*armJointRequests[i], toJointRequest, theArmMotionSelection.armRatios[ratioIndexOffset + i], jointRequest, interpolateStiffness, startJoint, endJoint);
        }
      }
    }

    ASSERT(jointRequest.isValid());
  };

  combinateArmMotions(Arms::left);
  combinateArmMotions(Arms::right);

  if(emergencyOffEnabled)
  {
    if(theFallDownState.state == FallDownState::falling && motionInfo.motion != MotionRequest::specialAction)
    {
      saveFall(jointRequest);
      centerHead(jointRequest);
      centerArms(jointRequest);
      currentRecoveryTime = 0;

      ASSERT(jointRequest.isValid());
    }
    else if((theFallDownState.state == FallDownState::staggering || theFallDownState.state == FallDownState::onGround) && (motionInfo.motion != MotionRequest::specialAction))
    {
      centerHead(jointRequest);

      ASSERT(jointRequest.isValid());
    }
    else
    {
      if(theFallDownState.state == FallDownState::upright)
      {
        headJawInSavePosition = false;
        headPitchInSavePosition = false;
        isFallingStarted = false;
      }

      if(currentRecoveryTime < recoveryTime)
      {
        currentRecoveryTime += 1;
        float ratio = (1.f / float(recoveryTime)) * currentRecoveryTime;
        for(int i = 0; i < Joints::numOfJoints; i++)
        {
          jointRequest.stiffnessData.stiffnesses[i] = 30 + int(ratio * float(jointRequest.stiffnessData.stiffnesses[i] - 30));
        }
      }
    }
  }

  float sum(0);
  int count(0);
  for(int i = Joints::lHipYawPitch; i < Joints::numOfJoints; i++)
  {
    if(jointRequest.angles[i] != JointAngles::off && jointRequest.angles[i] != JointAngles::ignore && lastJointRequest.angles[i] != JointAngles::off && lastJointRequest.angles[i] != JointAngles::ignore)
    {
      sum += abs(jointRequest.angles[i] - lastJointRequest.angles[i]);
      count++;
    }
  }
  PLOT("module:MotionCombinator:deviations:JointRequest:legsOnly", sum / count);
  for(int i = 0; i < Joints::lHipYawPitch; i++)
  {
    if(jointRequest.angles[i] != JointAngles::off && jointRequest.angles[i] != JointAngles::ignore && lastJointRequest.angles[i] != JointAngles::off && lastJointRequest.angles[i] != JointAngles::ignore)
    {
      sum += abs(jointRequest.angles[i] - lastJointRequest.angles[i]);
      count++;
    }
  }
  PLOT("module:MotionCombinator:deviations:JointRequest:all", sum / count);

  sum = 0;
  count = 0;
  for(int i = Joints::lHipYawPitch; i < Joints::numOfJoints; i++)
  {
    if(lastJointRequest.angles[i] != JointAngles::off && lastJointRequest.angles[i] != JointAngles::ignore)
    {
      sum += abs(lastJointRequest.angles[i] - theJointAngles.angles[i]);
      count++;
    }
  }
  PLOT("module:MotionCombinator:differenceToJointData:legsOnly", sum / count);

  for(int i = 0; i < Joints::lHipYawPitch; i++)
  {
    if(lastJointRequest.angles[i] != JointAngles::off && lastJointRequest.angles[i] != JointAngles::ignore)
    {
      sum += abs(lastJointRequest.angles[i] - theJointAngles.angles[i]);
      count++;
    }
  }
  lastJointRequest = jointRequest;
  PLOT("module:MotionCombinator:differenceToJointData:all", sum / count);

#ifndef NDEBUG
  if(!jointRequest.isValid())
  {
    {
      std::string logDir = "";
#ifdef TARGET_ROBOT
      logDir = "../logs/";
#endif
      OutMapFile stream(logDir + "jointRequest.log");
      stream << jointRequest;
      OutMapFile stream2(logDir + "motionSelection.log");
      stream2 << theMotionSelection;
    }
    ASSERT(false);
  }
#endif
}