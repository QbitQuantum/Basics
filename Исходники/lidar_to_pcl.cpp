void Match_Filter::scanCB(const sensor_msgs::LaserScan::ConstPtr& scan){		
	sensor_msgs::PointCloud2 cloud_in,cloud_out;
	projector_.transformLaserScanToPointCloud("/lidar_link",*scan,cloud_in,tfListener_);
	rot_tf.header.frame_id = "/ChestLidar";
//	lidar mx28 axis aligned mode
//	rot_tf.transform.rotation.x = enc_tf_.getRotation().x();
//	rot_tf.transform.rotation.y = enc_tf_.getRotation().y();
//	rot_tf.transform.rotation.z = enc_tf_.getRotation().z();
//	rot_tf.transform.rotation.w = enc_tf_.getRotation().w();

//	lidar mx28 axis perpendicular modeg
	tf::Quaternion q1;
	q1.setRPY(-M_PI/2,0,0);
	tf::Transform m1(q1);
	tf::Quaternion q2(enc_tf_.getRotation().x(),enc_tf_.getRotation().y(),enc_tf_.getRotation().z(),enc_tf_.getRotation().w());
	tf::Transform m2(q2);

	tf::Transform m4;
	m4 = m2*m1; // rotate lidar axis and revolute mx28 axis
	rot_tf.transform.rotation.x = m4.getRotation().x();
	rot_tf.transform.rotation.y = m4.getRotation().y();
	rot_tf.transform.rotation.z = m4.getRotation().z();
	rot_tf.transform.rotation.w = m4.getRotation().w();
	
	tf2::doTransform(cloud_in,cloud_out,rot_tf);
	point_cloud_pub_.publish(cloud_out);		
	moving_now.data = dxl_ismove_;
	dxl_ismove_pub_.publish(moving_now);
}