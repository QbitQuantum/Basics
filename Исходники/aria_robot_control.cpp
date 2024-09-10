bool AriaRobotControl::wait_until_stopped(ros::Duration wait, int  max_iterations)
{
  wait.sleep();
  int count = 0;
  //get the state of the robot
  while(!get_state_client.call(get_state_srv));
  
  //std::cout << "IS STOPPED: " <<  get_state_srv.response.isStopped << std::endl; 
  //wait until the robot has stopped moving to issue a move command
  while((!(get_state_srv.response.isStopped) || !(get_state_srv.response.isHeadingDone) \
        || !(get_state_srv.response.isMoveDone)) && count < max_iterations)
  {
    ROS_INFO("ROBOT STILL moving");
    wait.sleep();
    while(!get_state_client.call(get_state_srv)){
      ROS_INFO("failed service call!");
    }
    count++;
  } 
  if(get_state_srv.response.isStopped)
  {
    return true;
  } 
  else
  {
    return false;
  }
}//end is robot stopped