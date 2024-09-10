  /**
   * @brief service offering table object candidates
   *
   * @param req request for objects of a class (table objects in this case)
   * @param res response of the service which is possible table object candidates
   *
   * @return true if service successful
   */
  bool
  getTablesService2 (cob_3d_mapping_msgs::GetTablesRequest &req,
                     cob_3d_mapping_msgs::GetTablesResponse &res)
  {
    ROS_INFO("table detection started....");

    cob_3d_mapping_msgs::ShapeArray sa, tables;
    if (getMapService (sa))
    {
      tables.header = sa.header;
      //test
      tables.header.frame_id = "/map" ;
      //end of test
      processMap(sa, tables);

      for (unsigned int i = 0; i < tables.shapes.size (); i++)
      {
        //Polygon poly;
        Polygon::Ptr poly_ptr(new Polygon());
        fromROSMsg(tables.shapes[i], *poly_ptr);

        cob_3d_mapping_msgs::Table table;
        Eigen::Affine3f pose;
        Eigen::Vector4f min_pt;
        Eigen::Vector4f max_pt;
        poly_ptr->computePoseAndBoundingBox(pose,min_pt, max_pt);
        table.pose.pose.position.x = pose.translation()(0); //poly_ptr->centroid[0];
        table.pose.pose.position.y = pose.translation()(1) ;//poly_ptr->centroid[1];
        table.pose.pose.position.z = pose.translation()(2) ;//poly_ptr->centroid[2];
        Eigen::Quaternionf quat(pose.rotation());
        //            ROS_WARN("poly_ptr->centroid[0]");
        //            std::cout << poly_ptr->centroid[0]<< "\n";
        //            ROS_WARN("pose.translation()");
        //            std::cout << pose.translation() << "\n" ;

        table.pose.pose.orientation.x = quat.x();
        table.pose.pose.orientation.y = quat.y();
        table.pose.pose.orientation.z = quat.z();
        table.pose.pose.orientation.w = quat.w();
        table.x_min = min_pt(0);
        table.x_max = max_pt(0);
        table.y_min = min_pt(1);
        table.y_max = max_pt(1);

        table.convex_hull.type = arm_navigation_msgs::Shape::MESH;
        for( unsigned int j=0; j<poly_ptr->contours[0].size(); j++)
        {
          geometry_msgs::Point p;
          p.x = poly_ptr->contours[0][j](0);
          p.y = poly_ptr->contours[0][j](1);
          p.z = poly_ptr->contours[0][j](2);
          table.convex_hull.vertices.push_back(p);
        }

        cob_3d_mapping_msgs::TabletopDetectionResult det;
        det.table = table;

        res.tables.push_back(det);
      }
      //        sa_pub_.publish (tables);
      publishShapeMarker (tables);
      table_ctr_ = tables.shapes.size();

      ROS_INFO("Found %d tables", table_ctr_);
      return true;
    }
    else
      return false;
  }