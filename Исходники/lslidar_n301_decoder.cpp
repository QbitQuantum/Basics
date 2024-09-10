void LslidarN301Decoder::publishScan()
{
	sensor_msgs::LaserScan::Ptr scan(new sensor_msgs::LaserScan);

  if(sweep_data->scans[0].points.size() <= 1)
		return;

	scan->header.frame_id = child_frame_id;
	
	scan->angle_max = 0.0;
	scan->angle_min = 2.0*M_PI;
	scan->angle_increment = (scan->angle_max-scan->angle_min)/3600;

	//	scan->time_increment = motor_speed_/1e8;
	scan->range_min = 0.05;
	scan->range_max = 100.0;
	scan->ranges.reserve(3600);
	scan->intensities.reserve(3600);

  std::vector<point_struct> mean_points[3600] = {};
  point_struct temp_point;
  for(uint16_t i = 0; i < sweep_data->scans[0].points.size(); i++)
  {
    int degree = round(sweep_data->scans[0].points[i].azimuth * RAD_TO_DEG * 10);
    //ROS_INFO("degree = %d", degree);
    if (degree >= 3600) degree = 0;
    if (degree < 0) degree = 3599;
    if((degree<(1800+laser_number))&&(degree>(1800-laser_number)))				
	{
		
    		//ROS_INFO("degree = %d", degree);
		temp_point.distance=std::numeric_limits<float>::infinity();
		temp_point.intensity = 0;
	}
	else
	{
		
		temp_point.distance = sweep_data->scans[0].points[i].distance;
		temp_point.intensity = sweep_data->scans[0].points[i].intensity;
	}
	
    mean_points[degree].push_back(temp_point);
  }

  // calc mean


  point_struct mean_point;
  for(uint16_t i = 0; i < 3600; i++)
	{
//    ROS_INFO("%f", sweep_data->scans[0].points[i].azimuth);
    if ( mean_points[i].size() == 0)
    {
      scan->ranges.push_back(0);
      scan->intensities.push_back(0);
      continue;
    }
    mean_point = getMeans(mean_points[i]);
    scan->ranges.push_back(mean_point.distance);
    scan->intensities.push_back(mean_point.intensity);
	}
	scan->header.stamp = ros::Time::now();
	scan_pub.publish(scan);

}