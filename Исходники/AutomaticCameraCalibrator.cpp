void AutomaticCameraCalibrator::optimize()
{
  if(optimizer == nullptr)
  {
    // since the parameters for the robot pose are correction parameters,
    // an empty RobotPose is used instead of theRobotPose
    optimizationParameters = pack(theCameraCalibration, Pose2f());
    optimizer = new GaussNewtonOptimizer<numOfParameterTranslations>(functor);
    successiveConvergations = 0;
    framesToWait = 0;
  }
  else
  {
    // only do an iteration after some frames have passed
    if(framesToWait <= 0)
    {
      framesToWait = numOfFramesToWait;
      const float delta = optimizer->iterate(optimizationParameters, Parameters::Constant(0.0001f));
      if(!std::isfinite(delta))
      {
        OUTPUT_TEXT("Restart optimize! An optimization error occured!");
        delete optimizer;
        optimizer = nullptr;
        state = Accumulate;
      }
      OUTPUT_TEXT("AutomaticCameraCalibrator: delta = " << delta);

      // the camera calibration is refreshed from the current optimizer state
      Pose2f robotPoseCorrection;
      unpack(optimizationParameters, nextCameraCalibration, robotPoseCorrection);

      if(std::abs(delta) < terminationCriterion)
        ++successiveConvergations;
      else
        successiveConvergations = 0;
      if(successiveConvergations >= minSuccessiveConvergations)
      {
        OUTPUT_TEXT("AutomaticCameraCalibrator: converged!");
        OUTPUT_TEXT("RobotPoseCorrection: " << robotPoseCorrection.translation.x() * 1000.0f
                    << " " << robotPoseCorrection.translation.y() * 1000.0f
                    << " " << robotPoseCorrection.rotation.toDegrees() << "deg");
        currentRobotPose.translation.x() += robotPoseCorrection.translation.x() * 1000.0f;
        currentRobotPose.translation.y() += robotPoseCorrection.translation.y() * 1000.0f;
        currentRobotPose.rotation = Angle::normalize(currentRobotPose.rotation + robotPoseCorrection.rotation);
        abort();

        if(setJointOffsets)
          invert(theCameraCalibration);
      }
    }
    --framesToWait;
  }
}