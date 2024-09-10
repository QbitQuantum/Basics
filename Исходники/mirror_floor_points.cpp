void callback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
    std::string base_frame("base_link");
    
    geometry_msgs::PointStamped pout;
    geometry_msgs::PointStamped pin;
    pin.header.frame_id = msg->header.frame_id;
    pin.point.x = 0; pin.point.y = 0; pin.point.z = 0;
    geometry_msgs::Vector3Stamped vout;
    geometry_msgs::Vector3Stamped vin;
    vin.header.frame_id = base_frame;
    vin.vector.x = 0; vin.vector.y = 0; vin.vector.z = 1;
    
    float height;
    Eigen::Vector3f normal;
    try {
        listener->transformPoint(base_frame, ros::Time(0), pin, msg->header.frame_id, pout);
        height = pout.point.z;
        listener->transformVector(msg->header.frame_id, ros::Time(0), vin, base_frame, vout);
        normal = Eigen::Vector3f(vout.vector.x, vout.vector.y, vout.vector.z);
    }
    catch (tf::TransformException ex) {
        ROS_INFO("%s",ex.what());
        return;
    }
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::fromROSMsg(*msg, *cloud);
	
	Eigen::Vector3f p = -height*normal; // a point in the floor plane
	float d = -p.dot(normal); // = height, d in the plane equation
	
	obstacle_cloud->points.clear();
	obstacle_cloud->points.reserve(cloud->size());
	floor_cloud->points.clear();
	Eigen::Vector3f temp;
	float floor_dist;
	pcl::PointXYZ point;
	for (size_t i = 0; i < cloud->size(); ++i) {
	    
	    /*temp = cloud->points[i].getVector3fMap(); // DEBUG!
	    
	    if (i%640 < 300 && i%640 > 200 && i < 640*200 && i > 640*100) {
	        temp -= 0.06*normal;
	    }*/

        // check signed distance to floor
	    floor_dist = normal.dot(cloud->points[i].getVector3fMap()) + d;
	    //floor_dist = normal.dot(temp) + d; // DEBUG
	    
	    // if enough below, consider a stair point
	    if (floor_dist < below_threshold) {
	        temp = cloud->points[i].getVector3fMap(); // RELEASE
	        point.getVector3fMap() = -(d/normal.dot(temp))*temp + normal*0.11;
	        floor_cloud->points.push_back(point);
	    }
	    else { // add as a normal obstacle or clearing point
	        obstacle_cloud->points.push_back(cloud->points[i]);
	    }
	}

	sensor_msgs::PointCloud2 floor_msg;
    pcl::toROSMsg(*floor_cloud, floor_msg);
	floor_msg.header = msg->header;

	floor_pub.publish(floor_msg);
	
	sensor_msgs::PointCloud2 obstacle_msg;
    pcl::toROSMsg(*obstacle_cloud, obstacle_msg);
	obstacle_msg.header = msg->header;
	
	obstacle_pub.publish(obstacle_msg);
}