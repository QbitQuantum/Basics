bool
pcl::EnsensoGrabber::estimateCalibrationPatternPose (Eigen::Affine3d &pattern_pose) const
{
  if (!device_open_)
    return (false);

  if (running_)
    return (false);

  try
  {
    NxLibCommand estimate_pattern_pose (cmdEstimatePatternPose);
    estimate_pattern_pose.execute ();
    NxLibItem tf = estimate_pattern_pose.result ()[itmPatternPose];
    // Convert tf into a matrix
    if (!jsonTransformationToMatrix (tf.asJson (), pattern_pose))
      return (false);
    pattern_pose.translation () /= 1000.0;  // Convert translation in meters (Ensenso API returns milimeters)
    return (true);
  }
  catch (NxLibException &ex)
  {
    ensensoExceptionHandling (ex, "estimateCalibrationPatternPoses");
    return (false);
  }
}