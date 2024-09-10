void ArmContactModelProvider::update(ArmContactModel& model)
{
  MODIFY("module:ArmContactModelProvider:parameters", p);
  DECLARE_PLOT("module:ArmContactModelProvider:errorLeftX");
  DECLARE_PLOT("module:ArmContactModelProvider:errorRightX");
  DECLARE_PLOT("module:ArmContactModelProvider:errorLeftY");
  DECLARE_PLOT("module:ArmContactModelProvider:errorRightY");
  DECLARE_PLOT("module:ArmContactModelProvider:errorDurationLeft");
  DECLARE_PLOT("module:ArmContactModelProvider:errorDurationRight");
  DECLARE_PLOT("module:ArmContactModelProvider:errorYThreshold");
  DECLARE_PLOT("module:ArmContactModelProvider:errorXThreshold");
  DECLARE_PLOT("module:ArmContactModelProvider:contactLeft");
  DECLARE_PLOT("module:ArmContactModelProvider:contactRight");

  DECLARE_DEBUG_DRAWING("module:ArmContactModelProvider:armContact", "drawingOnField");

  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 200, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);
  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 400, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);
  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 600, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);
  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 800, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);
  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 1000, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);
  CIRCLE("module:ArmContactModelProvider:armContact", 0, 0, 1200, 30, Drawings::ps_solid, ColorClasses::blue, Drawings::ps_null, ColorClasses::blue);


  /* Buffer arm angles */
  struct ArmAngles angles;
  angles.leftX = theJointRequest.angles[JointData::LShoulderPitch];
  angles.leftY = theJointRequest.angles[JointData::LShoulderRoll];
  angles.rightX = theJointRequest.angles[JointData::RShoulderPitch];
  angles.rightY = theJointRequest.angles[JointData::RShoulderRoll];
  angleBuffer.add(angles);
  
  /* Reset in case of a fall or penalty */
  if(theFallDownState.state == FallDownState::onGround || theRobotInfo.penalty != PENALTY_NONE)
  {
    leftErrorBuffer.init();
    rightErrorBuffer.init();
  }

  Pose2D odometryOffset = theOdometryData - lastOdometry;
  lastOdometry = theOdometryData;
  
  const Vector3<>& leftHandPos3D = theRobotModel.limbs[MassCalibration::foreArmLeft].translation;
  Vector2<> leftHandPos(leftHandPos3D.x, leftHandPos3D.y);
  Vector2<> leftHandSpeed = (odometryOffset + Pose2D(leftHandPos) - Pose2D(lastLeftHandPos)).translation / theFrameInfo.cycleTime;
  float leftFactor = std::max(0.f, 1.f - leftHandSpeed.abs() / p.speedBasedErrorReduction);
  lastLeftHandPos = leftHandPos;

  const Vector3<>& rightHandPos3D = theRobotModel.limbs[MassCalibration::foreArmRight].translation;
  Vector2<> rightHandPos(rightHandPos3D.x, rightHandPos3D.y);
  Vector2<> rightHandSpeed = (odometryOffset + Pose2D(rightHandPos) - Pose2D(lastRightHandPos)).translation / theFrameInfo.cycleTime;
  float rightFactor = std::max(0.f, 1.f - rightHandSpeed.abs() / p.speedBasedErrorReduction);
  lastRightHandPos = rightHandPos;
  
  /* Check for arm contact */
  // motion types to take into account: stand, walk (if the robot is upright)
  if((theMotionInfo.motion == MotionInfo::stand || theMotionInfo.motion == MotionInfo::walk) &&
     (theFallDownState.state == FallDownState::upright || theFallDownState.state == FallDownState::staggering) &&
     (theGameInfo.state == STATE_PLAYING || theGameInfo.state == STATE_READY) &&
     (theRobotInfo.penalty == PENALTY_NONE)) // TICKET 897: ArmContact only if robot is not penalized
  {
    checkArm(LEFT, leftFactor);
    checkArm(RIGHT, rightFactor);

    //left and right are projections of the 3 dimensional shoulder-joint vector
    //onto the x-y plane.
    Vector2f left = leftErrorBuffer.getAverageFloat();
    Vector2f right = rightErrorBuffer.getAverageFloat();

    
    //Determine if we are being pushed or not
    bool leftX  = fabs(left.x) > fromDegrees(p.errorXThreshold);
    bool leftY  = fabs(left.y) > fromDegrees(p.errorYThreshold);
    bool rightX = fabs(right.x)> fromDegrees(p.errorXThreshold);
    bool rightY = fabs(right.y)> fromDegrees(p.errorYThreshold);

    // update the model
    model.contactLeft  = leftX || leftY;
    model.contactRight = rightX || rightY;

    // The duration of the contact is counted upwards as long as the error
    //remains. Otherwise it is reseted to 0.
    model.durationLeft  = model.contactLeft  ? model.durationLeft + 1 : 0;
    model.durationRight = model.contactRight ? model.durationRight + 1 : 0;

    model.contactLeft &= model.durationLeft < p.malfunctionThreshold;
    model.contactRight &= model.durationRight < p.malfunctionThreshold;


    if(model.contactLeft)
    {
      model.timeOfLastContactLeft = theFrameInfo.time;
    }
    if(model.contactRight)
    {
      model.timeOfLastContactRight = theFrameInfo.time;
    }
    
    model.pushDirectionLeft = getDirection(LEFT, leftX, leftY, left);
    model.pushDirectionRight = getDirection(RIGHT, rightX, rightY, right);

    model.lastPushDirectionLeft = model.pushDirectionLeft != ArmContactModel::NONE ? model.pushDirectionLeft : model.lastPushDirectionLeft;
    model.lastPushDirectionRight = model.pushDirectionRight != ArmContactModel::NONE ? model.pushDirectionRight : model.lastPushDirectionRight;

    PLOT("module:ArmContactModelProvider:errorLeftX",         toDegrees(left.x));
    PLOT("module:ArmContactModelProvider:errorRightX",        toDegrees(right.x));
    PLOT("module:ArmContactModelProvider:errorLeftY",         toDegrees(left.y));
    PLOT("module:ArmContactModelProvider:errorRightY",        toDegrees(right.y));
    PLOT("module:ArmContactModelProvider:errorDurationLeft",  model.durationLeft);
    PLOT("module:ArmContactModelProvider:errorDurationRight", model.durationRight);
    PLOT("module:ArmContactModelProvider:errorYThreshold",    toDegrees(p.errorYThreshold));
    PLOT("module:ArmContactModelProvider:errorXThreshold",    toDegrees(p.errorXThreshold));
    PLOT("module:ArmContactModelProvider:contactLeft",        model.contactLeft ? 10.0 : 0.0);
    PLOT("module:ArmContactModelProvider:contactRight",       model.contactRight ? 10.0 : 0.0);

    ARROW("module:ArmContactModelProvider:armContact", 0, 0, -(toDegrees(left.y) * SCALE), toDegrees(left.x) * SCALE, 20, Drawings::ps_solid, ColorClasses::green);
    ARROW("module:ArmContactModelProvider:armContact", 0, 0, toDegrees(right.y) * SCALE, toDegrees(right.x) * SCALE, 20, Drawings::ps_solid, ColorClasses::red);

    COMPLEX_DRAWING("module:ArmContactModelProvider:armContact",
    {
      DRAWTEXT("module:ArmContactModelProvider:armContact", -2300, 1300, 20, ColorClasses::black, "LEFT");
      DRAWTEXT("module:ArmContactModelProvider:armContact", -2300, 1100, 20, ColorClasses::black, "ErrorX: " << toDegrees(left.x));
      DRAWTEXT("module:ArmContactModelProvider:armContact", -2300, 900, 20, ColorClasses::black,  "ErrorY: " << toDegrees(left.y));
      DRAWTEXT("module:ArmContactModelProvider:armContact", -2300, 500, 20, ColorClasses::black,  ArmContactModel::getName(model.pushDirectionLeft));
      DRAWTEXT("module:ArmContactModelProvider:armContact", -2300, 300, 20, ColorClasses::black,  "Time: " << model.timeOfLastContactLeft);

      DRAWTEXT("module:ArmContactModelProvider:armContact", 1300, 1300, 20, ColorClasses::black, "RIGHT");
      DRAWTEXT("module:ArmContactModelProvider:armContact", 1300, 1100, 20, ColorClasses::black, "ErrorX: " << toDegrees(right.x));
      DRAWTEXT("module:ArmContactModelProvider:armContact", 1300, 900, 20, ColorClasses::black,  "ErrorY: " << toDegrees(right.y));
      DRAWTEXT("module:ArmContactModelProvider:armContact", 1300, 500, 20, ColorClasses::black,  ArmContactModel::getName(model.pushDirectionRight));
      DRAWTEXT("module:ArmContactModelProvider:armContact", 1300, 300, 20, ColorClasses::black,  "Time: " << model.timeOfLastContactRight);

      if (model.contactLeft)
      {
        CROSS("module:ArmContactModelProvider:armContact", -2000, 0, 100, 20, Drawings::ps_solid, ColorClasses::red);
      }
      if (model.contactRight)
      {
        CROSS("module:ArmContactModelProvider:armContact", 2000, 0, 100, 20, Drawings::ps_solid, ColorClasses::red);
      }
  });