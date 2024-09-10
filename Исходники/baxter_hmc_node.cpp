int main (int argc, char **argv)
{

	selectScenario();
	srand(time(0)); 
	
	//! Initialized the node, setup the NodeHandle
	//! for handling the communication with the ROS system
	ros::init(argc, argv, "hmc_sub");
	ros::NodeHandle nh;

	//! Define the subscriber to the person's gesture
	ros::Subscriber sub = nh.subscribe
	("/swgesture", 1, baxterCallback);

	//! Define the publisher to send the desired robot's gesture
	pub = nh.advertise<std_msgs::Int32> ("/bxpoint_d", 1);
	ros::spin();

return 0;
}