void SerialCom::velSend(const dlut_move_base::Twist &tw)
{
  char pl[10];
  char pa[10];	

  double vel_linear,vel_angular;
  vel_linear = tw.linear.x;
  vel_angular = tw.angular.z;

  ROS_INFO("linear: [%f] angular: [%f].",vel_linear,vel_angular);

  ROS_INFO("linear: [%s].",gcvt(vel_linear,6,pl));
  ROS_INFO("angular: [%s].",gcvt(vel_angular,6,pa));

  packSend(fd_,'v',pl);//send the value of the velocity
  packSend(fd_,'w',pa);//send the value of the angular velocity
  ROS_INFO("velSend function called!");
}