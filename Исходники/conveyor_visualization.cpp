void MarkerVis::setMarker()
  {
    tf::Transform T_cB = T_bC.inverse();
    tf::Transform T_gB = T_cB * T_gC;
    tf::Quaternion q = T_gB.getRotation();
    marker.header.frame_id = "/world";
    marker.header.stamp = ros::Time();
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = T_gB.getOrigin()[0];
    marker.pose.position.y = T_gB.getOrigin()[1];
    marker.pose.position.z = T_gB.getOrigin()[2];
    //std::cout<<T_gB.getOrigin()[2]<<std::endl;
    //printf("%f, %f, %f\n", T_gB.getOrigin()[0]*1000, T_gB.getOrigin()[1]*1000, T_gB.getOrigin()[2]*1000);
    marker.pose.orientation.x = q[0];
    marker.pose.orientation.y = q[1];
    marker.pose.orientation.z = q[2];
    marker.pose.orientation.w = q[3];
    printf("%f, %f, %f, %f\n", q[0], q[1], q[2], q[3]);
    marker.scale.x = 0.2;
    marker.scale.y = 0.4;
    marker.scale.z = 0.01;
    marker.color.a = 1.0;
    marker.color.r = 1.0;
    marker.color.g = 0.0;
    marker.color.b = 0.0;
    marker_vis_pub.publish( marker );
  }