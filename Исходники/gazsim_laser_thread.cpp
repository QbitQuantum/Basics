void LaserSimThread::on_laser_data_msg(ConstLaserScanStampedPtr &msg)
{
  //logger->log_info(name(), "Got new Laser data.\n");

  MutexLocker lock(loop_mutex);

  const gazebo::msgs::LaserScan &scan = msg->scan();

  //calculate start angle
  int start_index = (scan.angle_min() + 2* M_PI) / M_PI * 180;
  
  int number_beams = scan.ranges_size();

  *laser_time_ = clock->now();
  
  //copy laser data
  for(int i = 0; i < number_beams; i++)
  {
    const float range = scan.ranges(i);
    if(range < max_range_)
    {
      laser_data_[(start_index + i) % 360] = range; 
    }
    else
    {
      laser_data_[(start_index + i) % 360] = NAN;
    }

  }
  new_data_  = true;
}