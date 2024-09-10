int main(int argc, char** argv)
{
	ros::init(argc, argv, "squirtle_localization_node");

	ROS_INFO("Squirtle Localization for ROS v0.1");

    ros::NodeHandle n;
	ros::NodeHandle pn("~");

	double rate;
	pn.param("rate", rate, 2.0);

    pn.param("true_north_compensation", true_north_compensation, 0.0499164166);
    
	pn.param<std::string>("global_frame_id", global_frame_id, "/world");
    pn.param<std::string>("odom_frame_id", odom_frame_id, "odom");
	
	tf_listener = new tf::TransformListener();

	message_filters::Subscriber<sensor_msgs::Imu> * imu_sub = new message_filters::Subscriber<sensor_msgs::Imu>();
	imu_sub->subscribe(n, "imu/data", 20);
    tf::MessageFilter<sensor_msgs::Imu> * tf_filter_imu = new tf::MessageFilter<sensor_msgs::Imu>(*imu_sub, *tf_listener, odom_frame_id, 20);
    tf_filter_imu->registerCallback( boost::bind(imuCallback, _1) );

	message_filters::Subscriber<sensor_msgs::NavSatFix> * gps_sub = new message_filters::Subscriber<sensor_msgs::NavSatFix>();
	gps_sub->subscribe(n, "gps/fix", 20);
    tf::MessageFilter<sensor_msgs::NavSatFix> * tf_filter_gps = new tf::MessageFilter<sensor_msgs::NavSatFix>(*gps_sub, *tf_listener, odom_frame_id, 20);
    tf_filter_gps->registerCallback( boost::bind(gpsCallback, _1) );

	/*message_filters::Subscriber<nav_msgs::Odometry> * odom_sub = new message_filters::Subscriber<nav_msgs::Odometry>();
	odom_sub->subscribe(n, "odom", 20);
    tf::MessageFilter<nav_msgs::Odometry> * tf_filter = new tf::MessageFilter<nav_msgs::Odometry>(*odom_sub, *tf_listener, base_footprint_frame_id, 20);
    tf_filter->registerCallback( boost::bind(odomCallback, _1) );*/

    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("global_odom", 10);

	static tf::TransformBroadcaster tf_broadcaster;

	ros::Rate r(rate);
	while(n.ok())
	{
        tf::Transform t_world_odom_rotation = t_world_imu * t_odom_imu.inverse();
        tf::Transform t_world_odom_translation = t_world_gps * t_odom_gps.inverse();

        tf::Transform t_world_odom;
        t_world_odom.setOrigin(t_world_odom_translation.getOrigin());
        t_world_odom.setRotation((t_world_odom_rotation.getRotation()).normalized());

        tf_broadcaster.sendTransform(tf::StampedTransform(t_world_odom, ros::Time::now(), global_frame_id, odom_frame_id));

        // Odometry header
        nav_msgs::Odometry odom_msg;
        odom_msg.header.frame_id = global_frame_id;
        odom_msg.header.stamp = ros::Time::now();

        // Odometry position
        tf::Vector3 position = t_world_odom_translation.getOrigin();
        odom_msg.pose.pose.position.x = position.getX();
        odom_msg.pose.pose.position.y = position.getY();
        odom_msg.pose.pose.position.z = position.getZ();

        // Odometry orientation
        tf::quaternionTFToMsg((t_world_odom_rotation.getRotation()).normalized(), odom_msg.pose.pose.orientation);

        // TODO: Finish this, add covariance...
        //odom_msg.pose.covariance...

        ros::Duration delta_t = odom_msg.header.stamp - last_odom.header.stamp;

        if(delta_t.toSec() < 1.0)
        {
            // Odometry linear velocity
            odom_msg.twist.twist.linear.x = (odom_msg.pose.pose.position.x - last_odom.pose.pose.position.x)/delta_t.toSec();
            odom_msg.twist.twist.linear.y = (odom_msg.pose.pose.position.y - last_odom.pose.pose.position.y)/delta_t.toSec();
            odom_msg.twist.twist.linear.z = (odom_msg.pose.pose.position.z - last_odom.pose.pose.position.z)/delta_t.toSec();

            // TODO: Fix this... We are assuming that the robot cannot rotate fast enought, so shortest_angular_distance might work.
            // Odometry angular velocity
            odom_msg.twist.twist.angular.x = 0.0;
            odom_msg.twist.twist.angular.y = 0.0;
            odom_msg.twist.twist.angular.z = (angles::shortest_angular_distance(tf::getYaw(odom_msg.pose.pose.orientation), tf::getYaw(last_odom.pose.pose.orientation)))/delta_t.toSec();

            // TODO: Finish this, add covariance...
            //odom_msg.twist.covariance...

            odom_pub.publish(odom_msg);
        }

        last_odom = odom_msg;

		ros::spinOnce();
		r.sleep();
	}
	
	return 0;
}