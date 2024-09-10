    void callback(const PointCloud::ConstPtr& cloud)
    {
        sensor_msgs::LaserScanPtr output(new sensor_msgs::LaserScan());
        NODELET_DEBUG("Got cloud");
        //Copy Header
        output->header = cloud->header;
        output->header.frame_id = output_frame_id_;
        output->angle_min = -M_PI/2;
        output->angle_max = M_PI/2;
        output->angle_increment = M_PI/180.0/2.0;
        output->time_increment = 0.0;
        output->scan_time = 1.0/30.0;
        output->range_min = 0.45;
        output->range_max = 10.0;

        uint32_t ranges_size = std::ceil((output->angle_max - output->angle_min) / output->angle_increment);
        output->ranges.assign(ranges_size, output->range_max + 1.0);

        //pcl::PointCloud<pcl::PointXYZ> cloud;
        //pcl::fromROSMsg(*input, cloud);

        for (PointCloud::const_iterator it = cloud->begin(); it != cloud->end(); ++it)
        {
            const float &x = it->x;
            const float &y = it->y;
            const float &z = it->z;

            /*    for (uint32_t u = std::max((uint32_t)u_min_, 0U); u < std::min((uint32_t)u_max_, cloud.height - 1); u++)
              for (uint32_t v = 0; v < cloud.width -1; v++)
              {
                //NODELET_ERROR("%d %d,  %d %d", u, v, cloud.height, cloud.width);
                pcl::PointXYZ point = cloud.at(v,u); ///WTF Column major?
                const float &x = point.x;
                const float &y = point.y;
                const float &z = point.z;
            */

            if ( std::isnan(x) || std::isnan(y) || std::isnan(z) )
            {
                NODELET_DEBUG("rejected for nan in point(%f, %f, %f)\n", x, y, z);
                continue;
            }
            if (-y > max_height_ || -y < min_height_)
            {
                NODELET_DEBUG("rejected for height %f not in range (%f, %f)\n", x, min_height_, max_height_);
                continue;
            }
            double angle = -atan2(x, z);
            if (angle < output->angle_min || angle > output->angle_max)
            {
                NODELET_DEBUG("rejected for angle %f not in range (%f, %f)\n", angle, output->angle_min, output->angle_max);
                continue;
            }
            int index = (angle - output->angle_min) / output->angle_increment;
            //printf ("index xyz( %f %f %f) angle %f index %d\n", x, y, z, angle, index);
            double range_sq = z*z+x*x;
            if (output->ranges[index] * output->ranges[index] > range_sq)
                output->ranges[index] = sqrt(range_sq);


        }

        pub_.publish(output);
    }