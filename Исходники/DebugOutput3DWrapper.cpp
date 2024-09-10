void DebugOutput3DWrapper::publishTrackedFrame(Frame* kf)
{
	KeyFrameMessage fMsg;


	fMsg.id = kf->id();
	fMsg.time = kf->timestamp();
	fMsg.isKeyframe = false;


	memcpy(fMsg.camToWorld.data(),kf->getScaledCamToWorld().cast<float>().data(),sizeof(float)*7);
	fMsg.fx = kf->fx(publishLvl);
	fMsg.fy = kf->fy(publishLvl);
	fMsg.cx = kf->cx(publishLvl);
	fMsg.cy = kf->cy(publishLvl);
	fMsg.width = kf->width(publishLvl);
	fMsg.height = kf->height(publishLvl);

	/*fMsg.pointcloud.clear();

	liveframe_publisher.publish(fMsg);*/


	SE3 camToWorld = se3FromSim3(kf->getScaledCamToWorld());

	/*geometry_msgs::PoseStamped pMsg;

	pMsg.pose.position.x = camToWorld.translation()[0];
	pMsg.pose.position.y = camToWorld.translation()[1];
	pMsg.pose.position.z = camToWorld.translation()[2];
	pMsg.pose.orientation.x = camToWorld.so3().unit_quaternion().x();
	pMsg.pose.orientation.y = camToWorld.so3().unit_quaternion().y();
	pMsg.pose.orientation.z = camToWorld.so3().unit_quaternion().z();
	pMsg.pose.orientation.w = camToWorld.so3().unit_quaternion().w();

	if (pMsg.pose.orientation.w < 0)
	{
		pMsg.pose.orientation.x *= -1;
		pMsg.pose.orientation.y *= -1;
		pMsg.pose.orientation.z *= -1;
		pMsg.pose.orientation.w *= -1;
	}

	pMsg.header.stamp = ros::Time(kf->timestamp());
	pMsg.header.frame_id = "world";
	pose_publisher.publish(pMsg);*/

	
	cv::circle(tracker_display, cv::Point(320+camToWorld.translation()[0]*640, -240 + camToWorld.translation()[1]*480), 2, cv::Scalar(255, 0, 0),4);
	cv::imshow("Tracking_output", tracker_display);
	std::cout << "PublishTrackedKeyframe: " << camToWorld.translation()[0] << " " << camToWorld.translation()[1] << "  " << camToWorld.translation()[2] << std::endl;
}