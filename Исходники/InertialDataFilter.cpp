void InertialDataFilter::update(InertialData& inertialData)
{
  DECLARE_PLOT("module:InertialDataFilter:expectedAccX");
  DECLARE_PLOT("module:InertialDataFilter:accX");
  DECLARE_PLOT("module:InertialDataFilter:expectedAccY");
  DECLARE_PLOT("module:InertialDataFilter:accY");
  DECLARE_PLOT("module:InertialDataFilter:expectedAccZ");
  DECLARE_PLOT("module:InertialDataFilter:accZ");

  // check whether the filter shall be reset
  if(!lastTime || theFrameInfo.time <= lastTime)
  {
    if(theFrameInfo.time == lastTime)
      return; // weird log file replaying?
    reset();
  }

  if(theMotionInfo.motion == MotionRequest::specialAction && theMotionInfo.specialActionRequest.specialAction == SpecialActionRequest::playDead)
  {
    reset();
  }

  // get foot positions
  Pose3f leftFoot = theRobotModel.limbs[Limbs::footLeft];
  Pose3f rightFoot = theRobotModel.limbs[Limbs::footRight];
  leftFoot.translate(0.f, 0.f, -theRobotDimensions.footHeight);
  rightFoot.translate(0.f, 0.f, -theRobotDimensions.footHeight);
  const Pose3f leftFootInvert(leftFoot.inverse());
  const Pose3f rightFootInvert(rightFoot.inverse());

  // calculate rotation and position offset using the robot model (joint data)
  const Pose3f leftOffset(lastLeftFoot.translation.z() != 0.f ? Pose3f(lastLeftFoot).conc(leftFootInvert) : Pose3f());
  const Pose3f rightOffset(lastRightFoot.translation.z() != 0.f ? Pose3f(lastRightFoot).conc(rightFootInvert) : Pose3f());

  // detect the foot that is on ground
  bool useLeft = true;
  if(theMotionInfo.motion == MotionRequest::walk && theWalkingEngineOutput.speed.translation.x() != 0)
  {
    useLeft = theWalkingEngineOutput.speed.translation.x() > 0 ?
              (leftOffset.translation.x() > rightOffset.translation.x()) :
              (leftOffset.translation.x() < rightOffset.translation.x());
  }
  else
  {
    Pose3f left(mean.rotation);
    Pose3f right(mean.rotation);
    left.conc(leftFoot);
    right.conc(rightFoot);
    useLeft = left.translation.z() < right.translation.z();
  }

  // update the filter
  const float timeScale = theFrameInfo.cycleTime;
  predict(RotationMatrix::fromEulerAngles(theInertialSensorData.gyro.x() * timeScale,
                                          theInertialSensorData.gyro.y() * timeScale, 0));

  // insert calculated rotation
  safeRawAngle = theInertialSensorData.angle.head<2>().cast<float>();
  bool useFeet = true;
  MODIFY("module:InertialDataFilter:useFeet", useFeet);
  if(useFeet &&
     (theMotionInfo.motion == MotionRequest::walk || theMotionInfo.motion == MotionRequest::stand ||
      (theMotionInfo.motion == MotionRequest::specialAction && theMotionInfo.specialActionRequest.specialAction == SpecialActionRequest::standHigh)) &&
     std::abs(safeRawAngle.x()) < calculatedAccLimit.x() && std::abs(safeRawAngle.y()) < calculatedAccLimit.y())
  {
    const RotationMatrix& usedRotation(useLeft ? leftFootInvert.rotation : rightFootInvert.rotation);
    Vector3f accGravOnly(usedRotation.col(0).z(), usedRotation.col(1).z(), usedRotation.col(2).z());
    accGravOnly *= Constants::g_1000;
    readingUpdate(accGravOnly);
  }
  else // insert acceleration sensor values
    readingUpdate(theInertialSensorData.acc);

  // fill the representation
  inertialData.angle = Vector2a(std::atan2(mean.rotation.col(1).z(), mean.rotation.col(2).z()), std::atan2(-mean.rotation.col(0).z(), mean.rotation.col(2).z()));

  inertialData.acc = theInertialSensorData.acc;
  inertialData.gyro = theInertialSensorData.gyro;

  inertialData.orientation = Rotation::removeZRotation(Quaternionf(mean.rotation));

  // this  keeps the rotation matrix orthogonal
  mean.rotation.normalize();

  // store some data for the next iteration
  lastLeftFoot = leftFoot;
  lastRightFoot = rightFoot;
  lastTime = theFrameInfo.time;

  // plots
  Vector3f angleAxisVec = Rotation::AngleAxis::pack(AngleAxisf(inertialData.orientation));
  PLOT("module:InertialDataFilter:angleX", toDegrees(angleAxisVec.x()));
  PLOT("module:InertialDataFilter:angleY", toDegrees(angleAxisVec.y()));
  PLOT("module:InertialDataFilter:angleZ", toDegrees(angleAxisVec.z()));
  PLOT("module:InertialDataFilter:unfilteredAngleX", theInertialSensorData.angle.x().toDegrees());
  PLOT("module:InertialDataFilter:unfilteredAngleY", theInertialSensorData.angle.y().toDegrees());

  angleAxisVec = Rotation::AngleAxis::pack(AngleAxisf(mean.rotation));
  PLOT("module:InertialDataFilter:interlanAngleX", toDegrees(angleAxisVec.x()));
  PLOT("module:InertialDataFilter:interlanAngleY", toDegrees(angleAxisVec.y()));
  PLOT("module:InertialDataFilter:interlanAngleZ", toDegrees(angleAxisVec.z()));
}