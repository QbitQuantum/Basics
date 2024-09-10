  CloudPtr
      get ()
      {
        //lock while we swap our cloud and reset it.
        boost::mutex::scoped_lock lock (mtx_);
        CloudPtr temp_cloud (new Cloud);
        CloudPtr temp_cloud2 (new Cloud);
        CloudPtr temp_cloud3 (new Cloud);
        CloudPtr temp_cloud4 (new Cloud);
        CloudPtr temp_cloud5 (new Cloud);
        CloudConstPtr empty_cloud;


        cout << "===============================\n"
                "======Start of frame===========\n"
                "===============================\n";
        //cerr << "cloud size orig: " << cloud_->size() << endl;
        voxel_grid.setInputCloud (cloud_);
        voxel_grid.filter (*temp_cloud);  // filter cloud for z depth

        //cerr << "cloud size postzfilter: " << temp_cloud->size() << endl;

        pcl::ModelCoefficients::Ptr planecoefficients (new pcl::ModelCoefficients ());
        pcl::PointIndices::Ptr plane_inliers (new pcl::PointIndices ());
        std::vector<pcl::ModelCoefficients> linecoefficients1;
        pcl::ModelCoefficients model;
        model.values.resize (6);
        pcl::PointIndices::Ptr line_inliers (new pcl::PointIndices ());
        std::vector<Eigen::Vector3f> corners;

        if(temp_cloud->size() > MIN_CLOUD_POINTS) {
          plane_seg.setInputCloud (temp_cloud);
          plane_seg.segment (*plane_inliers, *planecoefficients); // find plane
        }

        //cerr << "plane inliers size: " << plane_inliers->indices.size() << endl;

        cout << "planecoeffs: " 
            << planecoefficients->values[0]  << " "
            << planecoefficients->values[1]  << " "
            << planecoefficients->values[2]  << " "
            << planecoefficients->values[3]  << " "
            << endl;

        Eigen::Vector3f pn = Eigen::Vector3f(
            planecoefficients->values[0],
            planecoefficients->values[1],
            planecoefficients->values[2]);

        float planedeg = pcl::rad2deg(acos(pn.dot(Eigen::Vector3f::UnitZ())));
        cout << "angle of camera to floor normal: " << planedeg << " degrees" << endl;
        cout << "distance of camera to floor: " << planecoefficients->values[3]
            << " meters" <<  endl;

        plane_extract.setNegative (true); 
        plane_extract.setInputCloud (temp_cloud);
        plane_extract.setIndices (plane_inliers);
        plane_extract.filter (*temp_cloud2);   // remove plane
        plane_extract.setNegative (false); 
        plane_extract.filter (*temp_cloud5);   // only plane

        for(size_t i = 0; i < temp_cloud5->size (); ++i)
        {
          temp_cloud5->points[i].r = 0; 
          temp_cloud5->points[i].g = 255; 
          temp_cloud5->points[i].b = 0; 
          // tint found plane green for ground
        }

        for(size_t j = 0 ; j < MAX_LINES && temp_cloud2->size() > MIN_CLOUD_POINTS; j++) 
          // look for x lines until cloud gets too small
        {
//          cerr << "cloud size: " << temp_cloud2->size() << endl;

          line_seg.setInputCloud (temp_cloud2);
          line_seg.segment (*line_inliers, model); // find line

 //         cerr << "line inliears size: " << line_inliers->indices.size() << endl;

          if(line_inliers->indices.size() < MIN_CLOUD_POINTS)
            break;

          linecoefficients1.push_back (model);  // store line coeffs

          line_extract.setNegative (true); 
          line_extract.setInputCloud (temp_cloud2);
          line_extract.setIndices (line_inliers);
          line_extract.filter (*temp_cloud3);  // remove plane
          line_extract.setNegative (false); 
          line_extract.filter (*temp_cloud4);  // only plane
          for(size_t i = 0; i < temp_cloud4->size (); ++i) {
            temp_cloud4->points[i].g = 0; 
            if(j%2) {
              temp_cloud4->points[i].r = 255-j*int(255/MAX_LINES); 
              temp_cloud4->points[i].b = 0+j*int(255/MAX_LINES); 
            } else {
              temp_cloud4->points[i].b = 255-j*int(255/MAX_LINES); 
              temp_cloud4->points[i].r = 0+j*int(255/MAX_LINES); 
            }
          }
          *temp_cloud5 += *temp_cloud4;	// add line to ground

          temp_cloud2.swap ( temp_cloud3); // remove line

        }

        cout << "found " << linecoefficients1.size() << " lines." << endl;

        for(size_t i = 0; i < linecoefficients1.size(); i++)
        {
          //cerr << "linecoeffs: " << i  << " "
          //    << linecoefficients1[i].values[0]  << " "
          //    << linecoefficients1[i].values[1]  << " "
          //    << linecoefficients1[i].values[2]  << " "
          //    << linecoefficients1[i].values[3]  << " "
          //    << linecoefficients1[i].values[4]  << " "
          //    << linecoefficients1[i].values[5]  << " "
          //    << endl;

          Eigen::Vector3f lv = Eigen::Vector3f(
              linecoefficients1[i].values[3],
              linecoefficients1[i].values[4],
              linecoefficients1[i].values[5]); 

          Eigen::Vector3f lp = Eigen::Vector3f(
              linecoefficients1[i].values[0],
              linecoefficients1[i].values[1],
              linecoefficients1[i].values[2]); 

          float r = pn.dot(lv);
          float deg = pcl::rad2deg(acos(r));

          cout << "angle of line to floor normal: " << deg << " degrees" << endl;

          if(abs(deg-30) < 5 || abs(deg-150) < 5) 
          {
            cout << "found corner line" << endl;

            float t = -(lp.dot(pn) + planecoefficients->values[3])/ r;
            Eigen::Vector3f intersect = lp + lv*t;
            cout << "corner intersects floor at: " << endl << intersect << endl;
            cout << "straight line distance from camera to corner: " <<
                intersect.norm() << " meters" << endl;

            corners.push_back(intersect);

            Eigen::Vector3f floor_distance = intersect + pn;  // should be - ???

            cout << "distance along floor to corner: " <<
                floor_distance.norm() << " meters" << endl;
          }
          else if(abs(deg-90) < 5) 
          {
            cout << "found horizontal line" << endl;
          }

        }

        switch(corners.size())
        {
          case 2:
            cout << "distance between corners " << (corners[0] - corners[1]).norm() << endl;
            cout << "angle of pyramid to camera " <<
                pcl::rad2deg(acos(((corners[0] - corners[1]).normalized()).dot(Eigen::Vector3f::UnitX())))
                << endl;

            break;

          case 3:
            cout << "distance between corners " << (corners[0] - corners[1]).norm() << endl;
            cout << "distance between corners " << (corners[0] - corners[2]).norm() << endl;
            cout << "distance between corners " << (corners[1] - corners[2]).norm() << endl;

            cout << "angle of corner on floor (should be 90) " <<
                pcl::rad2deg(acos((corners[0] - corners[1]).dot(corners[0] - corners [2])))
                << endl;
            
            cout << "angle of pyramid to camera " <<
                pcl::rad2deg(acos(((corners[0] - corners[1]).normalized()).dot(Eigen::Vector3f::UnitX())))
                << endl;

            break;
        }

        if (saveCloud)
        {
          std::stringstream stream, stream1;
          std::string filename;

          stream << "inputCloud" << filesSaved << ".pcd";
          filename = stream.str();
          if (pcl::io::savePCDFile(filename, *cloud_, true) == 0)
          {
            filesSaved++;
            cout << "Saved " << filename << "." << endl;
          }
          else PCL_ERROR("Problem saving %s.\n", filename.c_str());

          
          stream1 << "inputCloud" << filesSaved << ".pcd";
          filename = stream1.str();
          if (pcl::io::savePCDFile(filename, *temp_cloud5, true) == 0)
          {
            filesSaved++;
            cout << "Saved " << filename << "." << endl;
          }
          else PCL_ERROR("Problem saving %s.\n", filename.c_str());

          saveCloud = false;
        }

        empty_cloud.swap(cloud_);  // set cloud_ to null

        if(toggleView == 1) 
          return (temp_cloud);  // return orig cloud
        else
          return (temp_cloud5); // return colored cloud
      }