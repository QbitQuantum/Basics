void stoplightCB(std_msgs::Bool)
{
	ROS_INFO("Drag Race Controller got stoplight.");
	racecar_set_speed(14);
	//racecar_set_speed(0);
	stoplight_subscriber.shutdown();
	system("rosnode kill stoplight_watcher &\n");
	system("roslaunch iarrc_launch lane_detection.launch &\n");
	system("roslaunch iarrc_launch race_end_detector.launch &\n");
	race_end_subscriber = nh->subscribe(race_end_topic, 1, wallDetectCB);
}