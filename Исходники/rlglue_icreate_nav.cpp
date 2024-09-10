position_tracker::Position start_environment(ros::Rate loop_rate)
{
  /* see where the robot is.  And then send that position*/
  
  ros::spinOnce();
  loop_rate.sleep();
  
  position_tracker::Position observation= getObservation();
  
  cout << observation.x << " " << observation.y << " " << observation.theta << endl;  
  return observation;
  
}