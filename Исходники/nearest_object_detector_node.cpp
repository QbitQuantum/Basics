bool stop(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
	if(subscribed_to_topic)
	{
		sub_scan.shutdown();
		subscribed_to_topic = false;
	}

	continues_mode_enabled = false;

	ROS_INFO("nearest object detector DISABLED");
	return true;
}