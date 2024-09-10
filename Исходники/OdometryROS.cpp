void OdometryROS::processData(const SensorData & data, const ros::Time & stamp)
{
	if(odometry_->getPose().isIdentity() &&
	   !groundTruthFrameId_.empty())
	{
		// sync with the first value of the ground truth
		Transform initialPose = getTransform(groundTruthFrameId_, frameId_, stamp);
		if(initialPose.isNull())
		{
			return;
		}

		NODELET_INFO( "Initializing odometry pose to %s (from \"%s\" -> \"%s\")",
				initialPose.prettyPrint().c_str(),
				groundTruthFrameId_.c_str(),
				frameId_.c_str());
		odometry_->reset(initialPose);
	}

	Transform guess;
	if(guessFromTf_)
	{
		Transform previousPose = this->getTransform(odomFrameId_, frameId_, ros::Time(odometry_->previousStamp()));
		Transform pose = this->getTransform(odomFrameId_, frameId_, stamp);
		if(!previousPose.isNull() && !pose.isNull())
		{
			guess = previousPose.inverse() * pose;

			/*if(!odometry_->previousVelocityTransform().isNull())
			{
				float dt = rtabmap_ros::timestampFromROS(stamp) - odometry_->previousStamp();
				float vx,vy,vz, vroll,vpitch,vyaw;
				odometry_->previousVelocityTransform().getTranslationAndEulerAngles(vx,vy,vz, vroll,vpitch,vyaw);
				Transform motionGuess(vx*dt, vy*dt, vz*dt, vroll*dt, vpitch*dt, vyaw*dt);
				NODELET_WARN( "P  Guess %s", motionGuess.prettyPrint().c_str());
			}
			NODELET_WARN( "TF Guess %s", guess.prettyPrint().c_str());*/
		}
	}

	// process data
	ros::WallTime time = ros::WallTime::now();
	rtabmap::OdometryInfo info;
	SensorData dataCpy = data;
	rtabmap::Transform pose = odometry_->process(dataCpy, guess, &info);
	if(!pose.isNull())
	{
		resetCurrentCount_ = resetCountdown_;

		//*********************
		// Update odometry
		//*********************
		geometry_msgs::TransformStamped poseMsg;
		poseMsg.child_frame_id = frameId_;
		poseMsg.header.frame_id = odomFrameId_;
		poseMsg.header.stamp = stamp;
		rtabmap_ros::transformToGeometryMsg(pose, poseMsg.transform);

		if(publishTf_)
		{
			tfBroadcaster_.sendTransform(poseMsg);
		}

		if(odomPub_.getNumSubscribers())
		{
			//next, we'll publish the odometry message over ROS
			nav_msgs::Odometry odom;
			odom.header.stamp = stamp; // use corresponding time stamp to image
			odom.header.frame_id = odomFrameId_;
			odom.child_frame_id = frameId_;

			//set the position
			odom.pose.pose.position.x = poseMsg.transform.translation.x;
			odom.pose.pose.position.y = poseMsg.transform.translation.y;
			odom.pose.pose.position.z = poseMsg.transform.translation.z;
			odom.pose.pose.orientation = poseMsg.transform.rotation;

			//set covariance
			// libviso2 uses approximately vel variance * 2
			odom.pose.covariance.at(0) = info.variance*2;  // xx
			odom.pose.covariance.at(7) = info.variance*2;  // yy
			odom.pose.covariance.at(14) = info.variance*2; // zz
			odom.pose.covariance.at(21) = info.variance*2; // rr
			odom.pose.covariance.at(28) = info.variance*2; // pp
			odom.pose.covariance.at(35) = info.variance*2; // yawyaw

			//set velocity
			bool setTwist = !odometry_->previousVelocityTransform().isNull();
			if(setTwist)
			{
				float x,y,z,roll,pitch,yaw;
				odometry_->previousVelocityTransform().getTranslationAndEulerAngles(x,y,z,roll,pitch,yaw);
				odom.twist.twist.linear.x = x;
				odom.twist.twist.linear.y = y;
				odom.twist.twist.linear.z = z;
				odom.twist.twist.angular.x = roll;
				odom.twist.twist.angular.y = pitch;
				odom.twist.twist.angular.z = yaw;
			}

			odom.twist.covariance.at(0) = setTwist?info.variance:BAD_COVARIANCE;  // xx
			odom.twist.covariance.at(7) = setTwist?info.variance:BAD_COVARIANCE;  // yy
			odom.twist.covariance.at(14) = setTwist?info.variance:BAD_COVARIANCE; // zz
			odom.twist.covariance.at(21) = setTwist?info.variance:BAD_COVARIANCE; // rr
			odom.twist.covariance.at(28) = setTwist?info.variance:BAD_COVARIANCE; // pp
			odom.twist.covariance.at(35) = setTwist?info.variance:BAD_COVARIANCE; // yawyaw

			//publish the message
			odomPub_.publish(odom);
		}

		// local map / reference frame
		if(odomLocalMap_.getNumSubscribers() && dynamic_cast<OdometryF2M*>(odometry_))
		{
			pcl::PointCloud<pcl::PointXYZ> cloud;
			const std::multimap<int, cv::Point3f> & map = ((OdometryF2M*)odometry_)->getMap().getWords3();
			for(std::multimap<int, cv::Point3f>::const_iterator iter=map.begin(); iter!=map.end(); ++iter)
			{
				cloud.push_back(pcl::PointXYZ(iter->second.x, iter->second.y, iter->second.z));
			}
			sensor_msgs::PointCloud2 cloudMsg;
			pcl::toROSMsg(cloud, cloudMsg);
			cloudMsg.header.stamp = stamp; // use corresponding time stamp to image
			cloudMsg.header.frame_id = odomFrameId_;
			odomLocalMap_.publish(cloudMsg);
		}

		if(odomLastFrame_.getNumSubscribers())
		{
			if(dynamic_cast<OdometryF2M*>(odometry_))
			{
				const std::multimap<int, cv::Point3f> & words3  = ((OdometryF2M*)odometry_)->getLastFrame().getWords3();
				if(words3.size())
				{
					pcl::PointCloud<pcl::PointXYZ> cloud;
					for(std::multimap<int, cv::Point3f>::const_iterator iter=words3.begin(); iter!=words3.end(); ++iter)
					{
						// transform to odom frame
						cv::Point3f pt = util3d::transformPoint(iter->second, pose);
						cloud.push_back(pcl::PointXYZ(pt.x, pt.y, pt.z));
					}

					sensor_msgs::PointCloud2 cloudMsg;
					pcl::toROSMsg(cloud, cloudMsg);
					cloudMsg.header.stamp = stamp; // use corresponding time stamp to image
					cloudMsg.header.frame_id = odomFrameId_;
					odomLastFrame_.publish(cloudMsg);
				}
			}
			else
			{
				//Frame to Frame
				const Signature & refFrame = ((OdometryF2F*)odometry_)->getRefFrame();
				if(refFrame.getWords3().size())
				{
					pcl::PointCloud<pcl::PointXYZ> cloud;
					for(std::multimap<int, cv::Point3f>::const_iterator iter=refFrame.getWords3().begin(); iter!=refFrame.getWords3().end(); ++iter)
					{
						// transform to odom frame
						cv::Point3f pt = util3d::transformPoint(iter->second, pose);
						cloud.push_back(pcl::PointXYZ(pt.x, pt.y, pt.z));
					}
					sensor_msgs::PointCloud2 cloudMsg;
					pcl::toROSMsg(cloud, cloudMsg);
					cloudMsg.header.stamp = stamp; // use corresponding time stamp to image
					cloudMsg.header.frame_id = odomFrameId_;
					odomLastFrame_.publish(cloudMsg);
				}
			}
		}
	}
	else if(publishNullWhenLost_)
	{
		//NODELET_WARN( "Odometry lost!");

		//send null pose to notify that odometry is lost
		nav_msgs::Odometry odom;
		odom.header.stamp = stamp; // use corresponding time stamp to image
		odom.header.frame_id = odomFrameId_;
		odom.child_frame_id = frameId_;
		odom.pose.covariance.at(0) = BAD_COVARIANCE;  // xx
		odom.pose.covariance.at(7) = BAD_COVARIANCE;  // yy
		odom.pose.covariance.at(14) = BAD_COVARIANCE; // zz
		odom.pose.covariance.at(21) = BAD_COVARIANCE; // rr
		odom.pose.covariance.at(28) = BAD_COVARIANCE; // pp
		odom.pose.covariance.at(35) = BAD_COVARIANCE; // yawyaw
		odom.twist.covariance.at(0) = BAD_COVARIANCE;  // xx
		odom.twist.covariance.at(7) = BAD_COVARIANCE;  // yy
		odom.twist.covariance.at(14) = BAD_COVARIANCE; // zz
		odom.twist.covariance.at(21) = BAD_COVARIANCE; // rr
		odom.twist.covariance.at(28) = BAD_COVARIANCE; // pp
		odom.twist.covariance.at(35) = BAD_COVARIANCE; // yawyaw

		//publish the message
		odomPub_.publish(odom);
	}

	if(pose.isNull() && resetCurrentCount_ > 0)
	{
		NODELET_WARN( "Odometry lost! Odometry will be reset after next %d consecutive unsuccessful odometry updates...", resetCurrentCount_);

		--resetCurrentCount_;
		if(resetCurrentCount_ == 0)
		{
			// Check TF to see if sensor fusion is used (e.g., the output of robot_localization)
			Transform tfPose = this->getTransform(odomFrameId_, frameId_, stamp);
			if(tfPose.isNull())
			{
				NODELET_WARN( "Odometry automatically reset to latest computed pose!");
				odometry_->reset(odometry_->getPose());
			}
			else
			{
				NODELET_WARN( "Odometry automatically reset to latest odometry pose available from TF (%s->%s)!",
						odomFrameId_.c_str(), frameId_.c_str());
				odometry_->reset(tfPose);
			}

		}
	}

	if(odomInfoPub_.getNumSubscribers())
	{
		rtabmap_ros::OdomInfo infoMsg;
		odomInfoToROS(info, infoMsg);
		infoMsg.header.stamp = stamp; // use corresponding time stamp to image
		infoMsg.header.frame_id = odomFrameId_;
		odomInfoPub_.publish(infoMsg);
	}

	NODELET_INFO( "Odom: quality=%d, std dev=%fm, update time=%fs", info.inliers, pose.isNull()?0.0f:std::sqrt(info.variance), (ros::WallTime::now()-time).toSec());
}