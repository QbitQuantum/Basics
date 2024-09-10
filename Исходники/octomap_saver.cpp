void octomapCallback(const octomap_msgs::Octomap::ConstPtr& msg)
{
	octomap_msg = msg;
	octomap_sub.shutdown();
}