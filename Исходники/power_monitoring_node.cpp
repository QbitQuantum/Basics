void currentCallback(const std_msgs::Float32::ConstPtr& current){
	last_time = curr_time;
	curr_time = ros::Time::now(); 
	if(last_time.toSec() != 0.0){
		inst_power = current->data*22.0;	
		float inst_coulombs = current->data*(curr_time.toSec() - last_time.toSec());
		//ROS_INFO("inst_coulombs = %f", inst_coulombs);
		//ROS_INFO("curr coulombs, before addition: %f", curr_coulombs);
		curr_coulombs = curr_coulombs + inst_coulombs;
		//ROS_INFO("curr_coulombs, after addition:  %f", curr_coulombs);
	} //else, ignore the first value
}