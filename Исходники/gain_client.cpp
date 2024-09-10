bool GainClient::disablePositionForceControlGains(double transition_duration, bool wait_for_success)
{
  sl_controller_msgs::CartesianGains position_gains;
  setZero(position_gains);
  sl_controller_msgs::CartesianGains force_gains;
  setZero(force_gains);
  return setArmPositionForceControlGains(position_gains, force_gains, transition_duration, wait_for_success);
}