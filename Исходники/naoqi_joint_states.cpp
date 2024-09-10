void NaoqiJointStates::run()
{
   ros::Rate r(m_rate);
   ros::Time stamp1;
   ros::Time stamp2;
   ros::Time stamp;

   std::vector<float> odomData;
   float odomX, odomY, odomZ, odomWX, odomWY, odomWZ;

   std::vector<float> memData;

   std::vector<float> positionData;

   ROS_INFO("Staring main loop. ros::ok() is %d nh.ok() is %d",ros::ok(),m_nh.ok());
   while(ros::ok() )
   {
      r.sleep();
      ros::spinOnce();
      stamp1 = ros::Time::now();
      try
      {
         memData = m_memoryProxy->getListData(m_dataNamesList);
         // {SPACE_TORSO = 0, SPACE_WORLD = 1, SPACE_NAO = 2}. (second argument)
         odomData = m_motionProxy->getPosition("Torso", 1, true);
         positionData = m_motionProxy->getAngles("Body", true);
      }
      catch (const AL::ALError & e)
      {
         ROS_ERROR( "Error accessing ALMemory, exiting...");
         ROS_ERROR( "%s", e.what() );
         //ros.signal_shutdown("No NaoQI available anymore");
      }
      stamp2 = ros::Time::now();
      //ROS_DEBUG("dt is %f",(stamp2-stamp1).toSec()); % dt is typically around 1/1000 sec
      // TODO: Something smarter than this..
      stamp = stamp1 + ros::Duration((stamp2-stamp1).toSec()/2.0);

      /******************************************************************
       *                              IMU
       *****************************************************************/
      if (memData.size() != m_dataNamesList.getSize())
      {
         ROS_ERROR("memData length %zu does not match expected length %u",memData.size(),m_dataNamesList.getSize() );
         continue;
      }
      // IMU data:
      m_torsoIMU.header.stamp = stamp;

      float angleX = memData[1];
      float angleY = memData[2];
      float angleZ = memData[3];
      float gyroX = memData[4];
      float gyroY = memData[5];
      float gyroZ = memData[6];
      float accX = memData[7];
      float accY = memData[8];
      float accZ = memData[9];

      m_torsoIMU.orientation = tf::createQuaternionMsgFromRollPitchYaw(
                                angleX,
                                angleY,
                                angleZ); // yaw currently always 0

      m_torsoIMU.angular_velocity.x = gyroX;
      m_torsoIMU.angular_velocity.y = gyroY;
      m_torsoIMU.angular_velocity.z = gyroZ; // currently always 0

      m_torsoIMU.linear_acceleration.x = accX;
      m_torsoIMU.linear_acceleration.y = accY;
      m_torsoIMU.linear_acceleration.z = accZ;

      // covariances unknown
      // cf http://www.ros.org/doc/api/sensor_msgs/html/msg/Imu.html
      m_torsoIMU.orientation_covariance[0] = -1;
      m_torsoIMU.angular_velocity_covariance[0] = -1;
      m_torsoIMU.linear_acceleration_covariance[0] = -1;

      m_torsoIMUPub.publish(m_torsoIMU);


      /******************************************************************
       *                            Joint state
       *****************************************************************/
      m_jointState.header.stamp = stamp;
      m_jointState.header.frame_id = m_baseFrameId;
      m_jointState.position.resize(positionData.size());
      for(unsigned i = 0; i<positionData.size(); ++i)
      {
         m_jointState.position[i] = positionData[i];
      }

      // simulated model misses some joints, we need to fill:
      if (m_jointState.position.size() == 22)
      {
         m_jointState.position.insert(m_jointState.position.begin()+6,0.0);
         m_jointState.position.insert(m_jointState.position.begin()+7,0.0);
         m_jointState.position.push_back(0.0);
         m_jointState.position.push_back(0.0);
      }

      m_jointStatePub.publish(m_jointState);


        /******************************************************************
        *                            Odometry
        *****************************************************************/
        if (!m_paused) {

        // apply offset transformation:
        tf::Pose transformedPose;


        if (odomData.size()!=6)
        {
            ROS_ERROR( "Error getting odom data. length is %zu",odomData.size() );
            continue;
        }

        double dt = (stamp.toSec() - m_lastOdomTime);

        odomX = odomData[0];
        odomY = odomData[1];
        odomZ = odomData[2];
        odomWX = odomData[3];
        odomWY = odomData[4];
        odomWZ = odomData[5];

        tf::Quaternion q;
        // roll and pitch from IMU, yaw from odometry:
        if (m_useIMUAngles)
            q.setRPY(angleX, angleY, odomWZ);
        else
            q.setRPY(odomWX, odomWY, odomWZ);

        m_odomPose.setOrigin(tf::Vector3(odomX, odomY, odomZ));
        m_odomPose.setRotation(q);

        if(m_mustUpdateOffset) {
            if(!m_isInitialized) {
                if(m_initializeFromIMU) {
                    // Initialization from IMU: Take x, y, z, yaw from odometry, roll and pitch from IMU
                    m_targetPose.setOrigin(m_odomPose.getOrigin());
                    m_targetPose.setRotation(tf::createQuaternionFromRPY(angleX, angleY, odomWZ));
                } else if(m_initializeFromOdometry) {
                    m_targetPose.setOrigin(m_odomPose.getOrigin());
                    m_targetPose.setRotation(tf::createQuaternionFromRPY(odomWX, odomWY, odomWZ));
                }
                m_isInitialized = true;
            } else {
                // Overwrite target pitch and roll angles with IMU data
                const double target_yaw = tf::getYaw(m_targetPose.getRotation());
                if(m_initializeFromIMU) {
                    m_targetPose.setRotation(tf::createQuaternionFromRPY(angleX, angleY, target_yaw));
                } else if(m_initializeFromOdometry){
                    m_targetPose.setRotation(tf::createQuaternionFromRPY(odomWX, odomWY, target_yaw));
                }
            }
            m_odomOffset = m_targetPose * m_odomPose.inverse();
            transformedPose = m_targetPose;
            m_mustUpdateOffset = false;
        } else {
            transformedPose = m_odomOffset * m_odomPose;
        }

        //
        // publish the transform over tf first
        //
        m_odomTransformMsg.header.stamp = stamp;
        tf::transformTFToMsg(transformedPose, m_odomTransformMsg.transform);
        m_transformBroadcaster.sendTransform(m_odomTransformMsg);


        //
        // Fill the Odometry msg
        //
        m_odom.header.stamp = stamp;
        //set the velocity first (old values still valid)
        m_odom.twist.twist.linear.x = (odomX - m_odom.pose.pose.position.x) / dt;
        m_odom.twist.twist.linear.y = (odomY - m_odom.pose.pose.position.y) / dt;
        m_odom.twist.twist.linear.z = (odomZ - m_odom.pose.pose.position.z) / dt;

        // TODO: calc angular velocity!
        //	m_odom.twist.twist.angular.z = vth; ??

        //set the position from the above calculated transform
        m_odom.pose.pose.orientation = m_odomTransformMsg.transform.rotation;
        m_odom.pose.pose.position.x = m_odomTransformMsg.transform.translation.x;
        m_odom.pose.pose.position.y = m_odomTransformMsg.transform.translation.y;
        m_odom.pose.pose.position.z = m_odomTransformMsg.transform.translation.z;


        m_odomPub.publish(m_odom);


        m_lastOdomTime = stamp.toSec();

        }
    }
    ROS_INFO("naoqi_sensors stopped.");

}