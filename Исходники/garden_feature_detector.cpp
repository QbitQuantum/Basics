// Separate into separate clouds and publish polygons
std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr > // use jsk_recognition_msgs::PointsArray
separate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz_rot, std_msgs::Header header) {
  double x_pitch = 0.25, x_min = 1.0, x_max = 3.0; // 1.5~1.75 1.75~2.00 1.5~1.675
  double y_min = -0.75, y_max = 0.75;
  double z_min = -0.250, z_1 = 0.000, z_2 = 1.000, z_max = 1.750; // -0.3125, 2.0
  pcl::PointXYZ pt_1, pt_2, pt_3, pt_4, pt_5, pt_6; // deprecate with polygon

  // Divide large cloud
  std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr > cloud_vector;
  // pcl::PointCloud<pcl::PointXYZ>::Ptr tmp_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  // pcl::PointXYZ tmp_p;

  jsk_recognition_msgs::PolygonArray polygon_array;
  polygon_array.header = header;
  for (int i = 0; i < (int)( (x_max - x_min) / x_pitch ); i++) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr tmp_cloud (new pcl::PointCloud<pcl::PointXYZ>);
    geometry_msgs::PolygonStamped polygon;
    visualization_msgs::Marker texts, line_strip; // TEXT_VIEW_FACING

    texts.header = header;
    texts.ns = "text"; // namespace + ID
    texts.action = visualization_msgs::Marker::ADD;
    texts.type = visualization_msgs::Marker::TEXT_VIEW_FACING;

    texts.pose.orientation.x = 0.0;
    texts.pose.orientation.y = 0.0;
    texts.pose.orientation.z = 0.0;
    texts.pose.orientation.w = 1.0;
    texts.scale.x = 0.125;
    texts.scale.y = 0.125;
    texts.scale.z = 0.125;
    texts.color.r = 1.0f;
    texts.color.g = 0.0f;
    texts.color.b = 0.0f;
    texts.color.a = 1.0;

    geometry_msgs::Point32 tmp_p_up_0, tmp_p_up_1, tmp_p_up_2, tmp_p_down_0, tmp_p_down_1, tmp_p_down_2;
    pcl::PointXYZ tmp_p;
    double width_tmp, width_min_up = 2.000, width_min_down = 4.000;
    double width_min_bottom = 0.500, width_min_top = 0.200;
    for (pcl::PointCloud<pcl::PointXYZ>::const_iterator itr = cloud_xyz_rot->begin();
         itr != cloud_xyz_rot->end(); itr++) {
      if ( (x_min + i*x_pitch) < itr->x && itr->x < (x_min + (i+1)*x_pitch) ) {
        if (y_min < itr->y && itr->y < y_max) {
          if (z_min < itr->z && itr->z < z_max) {
            // compare tmp_p and itr, and calculate width and points
            if (itr != cloud_xyz_rot->begin()) { // skip at 1st time
              if ( (tmp_p.y < 0 && 0 <= itr->y) || (itr->y < 0 && 0 <= tmp_p.y) ) {
                if (itr->z < z_1) {
                  width_tmp = sqrt(pow(fabs(tmp_p.x - itr->x), 2)
                                   + pow(fabs(tmp_p.y - itr->y), 2)
                                   + pow(fabs(tmp_p.z - itr->z), 2));
                  if (width_min_bottom < width_tmp && width_tmp <= width_min_down) {
                    width_min_down = width_tmp; // create width_min array
                    tmp_p_down_0.x = tmp_p.x; tmp_p_down_0.y = tmp_p.y;
                    tmp_p_down_0.z = (tmp_p.z + itr->z) / 2;
                    tmp_p_down_1.x = itr->x; tmp_p_down_1.y = itr->y;
                    tmp_p_down_1.z = (tmp_p.z + itr->z) / 2;
                    tmp_p_down_2.x = tmp_p.x; // ignore adding sqrt
                    tmp_p_down_2.y = tmp_p.y + sqrt(pow(fabs(tmp_p.y - itr->y), 2)) / 2;
                    tmp_p_down_2.z = (tmp_p.z + itr->z) / 2;
                  }
                }
                if (z_2 < itr->z) {
                  width_tmp = sqrt(pow(fabs(tmp_p.x - itr->x), 2)
                                   + pow(fabs(tmp_p.y - itr->y), 2)
                                   + pow(fabs(tmp_p.z - itr->z), 2));
                  if (width_tmp <= width_min_down) {
                    width_min_up = width_tmp;
                    tmp_p_up_0.x = tmp_p.x; tmp_p_up_0.y = tmp_p.y;
                    tmp_p_up_0.z = (tmp_p.z + itr->z) / 2;
                    tmp_p_up_1.x = itr->x; tmp_p_up_1.y = itr->y;
                    tmp_p_up_1.z = (tmp_p.z + itr->z) / 2;
                    tmp_p_up_2.x = tmp_p.x; // ignore adding sqrt
                    tmp_p_up_2.y = tmp_p.y + sqrt(pow(fabs(tmp_p.y - itr->y), 2)) / 2;
                    tmp_p_up_2.z = (tmp_p.z + itr->z) / 2;
                  }
                }
              }
              tmp_p.x = itr->x; tmp_p.y = itr->y; tmp_p.z = itr->z;
              tmp_cloud->points.push_back(tmp_p);
            }
          }
        }
      }
      // From tmp_cloud, get 4 points to publish marker
      // Create polygon
    }

    cloud_vector.push_back(tmp_cloud);

    tmp_p_up_0.x = x_min + i*x_pitch - x_pitch/2;
    tmp_p_up_1.x = x_min + i*x_pitch - x_pitch/2;
    tmp_p_down_0.x = x_min + i*x_pitch - x_pitch/2;
    tmp_p_down_1.x = x_min + i*x_pitch - x_pitch/2;
    if (tmp_p_up_0.y < tmp_p_up_1.y) {
      polygon.polygon.points.push_back(tmp_p_up_0);
      polygon.polygon.points.push_back(tmp_p_up_1);
    }
    if (tmp_p_up_0.y >= tmp_p_up_1.y) {
      polygon.polygon.points.push_back(tmp_p_up_1);
      polygon.polygon.points.push_back(tmp_p_up_0);
    }
    if (tmp_p_down_0.y < tmp_p_down_1.y) {
      polygon.polygon.points.push_back(tmp_p_down_1);
      polygon.polygon.points.push_back(tmp_p_down_0);
    }
    if (tmp_p_down_0.y >= tmp_p_down_1.y) {
      polygon.polygon.points.push_back(tmp_p_down_0);
      polygon.polygon.points.push_back(tmp_p_down_1);
    }
    polygon.header = header;
    polygon_array.polygons.push_back(polygon);

    std::cerr << "count:" << i << ", " << "size:" << cloud_vector.at(i)->size() << std::endl;
    std::cerr << "width_min_up:" << width_min_up << std::endl;
    std::cerr << "width_min_down:" << width_min_down << std::endl;

    texts.id = 2*i;
    texts.pose.position.x = tmp_p_up_0.x;
    texts.pose.position.y = tmp_p_up_2.y;
    texts.pose.position.z = tmp_p_up_2.z;

    std::ostringstream strs;
    strs << width_min_up;
    std::string str = strs.str();
    texts.text = str;
    pub_marker.publish(texts);

    texts.id = 2*i + 1;
    texts.pose.position.x = tmp_p_down_0.x;
    texts.pose.position.y = tmp_p_down_2.y;
    texts.pose.position.z = tmp_p_down_2.z;

    strs.str("");
    strs.clear(std::stringstream::goodbit);
    strs << width_min_down;
    str = strs.str();
    texts.text = str;
    pub_marker.publish(texts);

  }
  pub_polygon_array.publish(polygon_array); // error
  return cloud_vector;
}