void stateCallback(const nav_msgs::Odometry::ConstPtr& state)
{
  
	
		vel[0] = state->twist.twist.linear.x;
		vel[1] = state->twist.twist.linear.y;
		vel[2] = state->twist.twist.linear.z;
		pos[2] = state->pose.pose.position.z;
    
		//q.x() = state->pose.pose.orientation.x;
		//q.y() = state->pose.pose.orientation.y;
		//q.z() = state->pose.pose.orientation.z;
		//q.w() = state->pose.pose.orientation.w; 
    float q_x = state->pose.pose.orientation.x;
		float q_y = state->pose.pose.orientation.y;
		float q_z = state->pose.pose.orientation.z;
		float q_w = state->pose.pose.orientation.w;

float  yaw = atan2(2*(q_w*q_z+q_x*q_y),1-2*(q_y*q_y+q_z*q_z));
//Eigen::Matrix3d R(q);
	force(0) = offset_x+k_vxy*(vel_des(0)-vel(0))+m*acc_des(0);
	if(pd_control==0)
  force(1) = offset_y+k_vxy*(vel_des(1)-vel(1))+m*acc_des(1);
  else if(pd_control==1)
  {
    pos[1]=state->pose.pose.position.y;
    force(1) = offset_y+k_vxy*(vel_des(1)-vel(1))+k_xy*(0-pos[1])+m*acc_des(1);
  }
	force(2) = (k_z*(pos_des(2)-pos(2))+k_vz*(vel_des(2)-vel(2))+m*g(2)+m*acc_des(2));


  b3 = force.normalized();
  b2 = b3.cross(b1w);
  b1 = b2.cross(b3);
  R_des<<b1[0],b2[0],b3[0],
    b1[1],b2[1],b3[1],
    b1[2],b2[2],b3[2];
  Eigen::Quaternionf q_des(R_des);
  	
  quadrotor_msgs::SO3Command command;
	command.force.x = force[0];
  command.force.y = force[1];
  command.force.z = force[2];
  command.orientation.x = q_des.x();
  command.orientation.y = q_des.y();
  command.orientation.z = q_des.z();
  command.orientation.w = q_des.w();
  command.kR[0] = k_R;
  command.kR[1] = k_R;
  command.kR[2] = k_R;
  command.kOm[0] = k_omg;
  command.kOm[1] = k_omg;
  command.kOm[2] = k_omg;
	command.aux.current_yaw = yaw;
	command.aux.enable_motors = true;
	command.aux.use_external_yaw = true;
  control_pub.publish(command);
}