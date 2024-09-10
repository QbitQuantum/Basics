void laserCallback(const sensor_msgs::LaserScan& msg)
{
  double angle;
  unsigned int i;

  // Store robot position in map grid coordinates
  unsigned int robot_col = 0; // CHANGE ME
  unsigned int robot_row = 0; // CHANGE ME

  angle = msg.angle_min;
  i=0;
  // Go through all the LRF measurements
  while(angle <= msg.angle_max)
  {
    if( msg.ranges[i] > msg.range_min )
    {
      ///////////////////////////////////////////////////////////////////////
      // Update map with each sensor reading.
      //
      // Important variables (already defined and available):
      //  - (robot_pose.x, robot_pose.y, robot_pose.theta) ==> Robot pose in the
      // world frame;
      //  - msg.ranges[i] ==> LRF i reading (distance from the LRF to the beacon
      // detected by the beacon at the i-th angle);
      //
      ///////////////////////////////////////////////////////////////////////
      // INSERT YOUR CODE BELOW THIS POINT
      ///////////////////////////////////////////////////////////////////////

      // Create obstacle position in sensor coordinates from msg.ranges[i]


      // Transform obstacle position to robot coordinates using local2world


      // Get obtained value in world coordinates using again local2world


      // Get obtained value in the map grid (columm and row) - must be unsigned
      // int.


      // Update map using the line iterator for free space

      // Update map using the line iterator for occupied space, if applicable

      ///////////////////////////////////////////////////////////////////////
      // INSERT YOUR CODE ABOVE THIS POINT
      ///////////////////////////////////////////////////////////////////////
    }

    // Proceed to next laser measure
    angle += msg.angle_increment;
    i++;
  }

  // Show map
  cv::imshow("Mapa", map);

  // Save the map every DELTA_SAVE iterations
  iteration++;
  if( iteration == DELTA_SAVE )
  {
    cv::imwrite("mapa.png", map);
    iteration = 0;
  }

  /// Update distance to closest obstacles
  // Right obstacle
  angle = -1.571; // DEG2RAD(-90)
  i = round((angle - msg.angle_min)/msg.angle_increment);
  closest_right_obstacle = msg.range_max;
  while( angle < -1.309 ) // DEG2RAD(-90+15)
  {
    if( (msg.ranges[i] < msg.range_max) &&
        (msg.ranges[i] > msg.range_min) &&
        (msg.ranges[i] < closest_right_obstacle) )
      closest_right_obstacle = msg.ranges[i];
    i++;
    angle += msg.angle_increment;
  }

  // Front obstacle
  angle = -0.785; // DEG2RAD(-45)
  i = round((angle - msg.angle_min)/msg.angle_increment);
  closest_front_obstacle = msg.range_max;
  while( angle < 0.785 ) // DEG2RAD(45)
  {
    if( (msg.ranges[i] < msg.range_max) &&
        (msg.ranges[i] > msg.range_min) &&
        (msg.ranges[i] < closest_front_obstacle) )
      closest_front_obstacle = msg.ranges[i];
    i++;
    angle += msg.angle_increment;
  }

  // Left obstacle
  angle = 1.309; // DEG2RAD(90-15)
  i = round((angle - msg.angle_min)/msg.angle_increment);
  closest_left_obstacle = msg.range_max;
  while( angle < 1.571 ) // DEG2RAD(90)
  {
    if( (msg.ranges[i] < msg.range_max) &&
        (msg.ranges[i] > msg.range_min) &&
        (msg.ranges[i] < closest_left_obstacle) )
      closest_left_obstacle = msg.ranges[i];
    i++;
    angle += msg.angle_increment;
  }

  laser_updated = true;
  return;
}