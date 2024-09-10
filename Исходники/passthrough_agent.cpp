void dynamicReconfigureCallback(pcl_filters::passthroughConfig &config, uint32_t level) 
{
	ros::NodeHandle nh("~");
	if (axis_.compare(config.filteration_axis.c_str()) != 0)
	{
		axis_ = config.filteration_axis.c_str();
	}
	if (min_range_ != config.min_range)
	{
		min_range_ = config.min_range;
	}
	if (max_range_ != config.max_range)
	{
		max_range_ = config.max_range;
	}
	
	std::string temp_str = config.passthrough_sub.c_str();
	if (!config.passthrough_sub.empty() && passthrough_sub_.compare(temp_str) != 0)
	{
		sub_.shutdown();
		passthrough_sub_ = config.passthrough_sub.c_str();
		sub_ = nh.subscribe (passthrough_sub_, 1, cloudCallback);
	}
	ROS_INFO("Reconfigure Request: %s %f %f",axis_.c_str(), min_range_,max_range_);
}