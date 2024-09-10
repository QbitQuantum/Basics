void LoopbackControllerManager::fini()
{
  ROS_DEBUG("calling LoopbackControllerManager::fini");

  //pr2_hardware_interface::ActuatorMap::const_iterator it;
  //for (it = hw_.actuators_.begin(); it != hw_.actuators_.end(); ++it)
  //  delete it->second; // why is this causing double free corrpution?
  cm_->~ControllerManager();
  rosnode_->shutdown();

  ros_spinner_thread_->join();
}