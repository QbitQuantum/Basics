        // overloading constructor
        ProcessLaserScan(ros::NodeHandle& nh,Eigen::Matrix3d initialPose, Eigen::Matrix3d neighborIP,std::string laserTopic)
        {
            nh_ = nh;
            
            // initialize subscriber and publisher
            scanSub_ = nh_.subscribe<sensor_msgs::LaserScan>(laserTopic, 1000, &ProcessLaserScan::laserScanCallback,this); 
            Eigen::Matrix3d relPose;

            relPose = initialPose.inverse()*neighborIP;

            minAngle = atan2(relPose(2-1,1-1),relPose(2-1,2-1));

            minRange = sqrt(pow(relPose(1-1,3-1),2)+pow(relPose(2-1,3-1),2));
        }