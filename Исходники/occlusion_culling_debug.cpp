int main(int argc, char **argv)
{

    ros::init(argc, argv, "occlusion_culling_test");
    ros::NodeHandle n;

    ros::Publisher pub1 = n.advertise<sensor_msgs::PointCloud2>("original_point_cloud", 100);
    ros::Publisher pub2 = n.advertise<sensor_msgs::PointCloud2>("occlusion_free_cloud", 100);
    ros::Publisher pub3 = n.advertise<sensor_msgs::PointCloud2>("ray_points", 100);
    ros::Publisher pub4 = n.advertise<visualization_msgs::Marker>("box_line_intersection", 10);
    ros::Publisher pub5 = n.advertise<visualization_msgs::Marker>("sensor_origin", 1);


    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr occlusionFreeCloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr rayCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    std::string path = ros::package::getPath("component_test");
    pcl::io::loadPCDFile<pcl::PointXYZ> (path+"/src/pcd/sphere_densed.pcd", *cloud);

    Eigen::Vector3d a(-3,0,0);
    Eigen::Affine3d pose;
    pose.translation() = a;
    geometry_msgs::Pose output_vector;
    tf::poseEigenToMsg(pose, output_vector);

    tf::Quaternion orientation = tf::createQuaternionFromRPY(0,0,0);;
    Eigen::Quaterniond q;
    geometry_msgs::Quaternion quet;
    tf::quaternionTFToEigen(orientation, q);
    tf::quaternionTFToMsg(orientation,quet);

    pose.translation() = a;
    visualization_msgs::Marker marker;

    //*****************voxel grid occlusion estimation *****************
    Eigen::Quaternionf quat(q.w(),q.x(),q.y(),q.z());
    cloud->sensor_origin_  = Eigen::Vector4f(a[0],a[1],a[2],0);
    cloud->sensor_orientation_= quat;
    pcl::VoxelGridOcclusionEstimationT voxelFilter;
    voxelFilter.setInputCloud (cloud);
    //voxelFilter.setLeafSize (0.03279f, 0.03279f, 0.03279f);
    voxelFilter.setLeafSize (0.04f, 0.04f, 0.04f);
    //voxelFilter.filter(*cloud); // This filter doesn't really work, it introduces points inside the sphere !
    voxelFilter.initializeVoxelGrid();

    int state,ret;
    Eigen::Vector3i t;
    pcl::PointXYZ pt,p1,p2;
    pcl::PointXYZRGB point;
    std::vector<Eigen::Vector3i, Eigen::aligned_allocator<Eigen::Vector3i> > out_ray;
    std::vector<geometry_msgs::Point> lineSegments;
    geometry_msgs::Point linePoint;
    Eigen::Vector3i  min_b = voxelFilter.getMinBoxCoordinates ();
    Eigen::Vector3i  max_b = voxelFilter.getMaxBoxCoordinates ();
    int count = 0;
    bool foundBug = false;
    // iterate over the entire voxel grid
    for (int kk = min_b.z (); kk <= max_b.z () && !foundBug; ++kk)
    {
        for (int jj = min_b.y (); jj <= max_b.y () && !foundBug; ++jj)
        {
            for (int ii = min_b.x (); ii <= max_b.x () && !foundBug; ++ii)
            {
                Eigen::Vector3i ijk (ii, jj, kk);
                // process all free voxels
                int index = voxelFilter.getCentroidIndexAt (ijk);
                Eigen::Vector4f centroid = voxelFilter.getCentroidCoordinate (ijk);
                point = pcl::PointXYZRGB(0,244,0);
                point.x = centroid[0];
                point.y = centroid[1];
                point.z = centroid[2];
                //if(index!=-1 && point.x>1.2 && point.y<0.2 && point.y>-0.2)
                if(index!=-1 )//&& point.x<-1.2 && point.y<0.2 && point.y>-0.2)
                {
                    out_ray.clear();
                    ret = voxelFilter.occlusionEstimation( state,out_ray, ijk);
                    std::cout<<"State is:"<<state<<"\n";
                    /*
                    if(state == 1)
                    {
                        if(count++>=10)
                        {
                            foundBug = true;
                            break;
                        }
                        cout<<"Number of voxels in ray:"<<out_ray.size()<<"\n";
                        for(uint j=0; j< out_ray.size(); j++)
                        {
                            Eigen::Vector4f centroid = voxelFilter.getCentroidCoordinate (out_ray[j]);
                            pcl::PointXYZRGB p = pcl::PointXYZRGB(255,255,0);
                            p.x = centroid[0];
                            p.y = centroid[1];
                            p.z = centroid[2];
                            rayCloud->points.push_back(p);
                            std::cout<<"Ray X:"<<p.x<<" y:"<< p.y<<" z:"<< p.z<<"\n";
                        }
                    }
                    */
                    if(state != 1)
                    {
                        // estimate direction to target voxel
                        Eigen::Vector4f direction = centroid - cloud->sensor_origin_;
                        direction.normalize ();
                        // estimate entry point into the voxel grid
                        float tmin = voxelFilter.rayBoxIntersection (cloud->sensor_origin_, direction,p1,p2);
                        if(tmin!=-1)
                        {
                            // coordinate of the boundary of the voxel grid
                            Eigen::Vector4f start = cloud->sensor_origin_ + tmin * direction;
                            linePoint.x = cloud->sensor_origin_[0]; linePoint.y = cloud->sensor_origin_[1]; linePoint.z = cloud->sensor_origin_[2];
                            //std::cout<<"Box Min X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                            lineSegments.push_back(linePoint);

                            linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
                            //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                            lineSegments.push_back(linePoint);

                            linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
                            //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                            lineSegments.push_back(linePoint);

                            linePoint.x = centroid[0]; linePoint.y = centroid[1]; linePoint.z = centroid[2];
                            //std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
                            lineSegments.push_back(linePoint);

                            rayCloud->points.push_back(point);
                            pt.x = centroid[0];
                            pt.y = centroid[1];
                            pt.z = centroid[2];
                            occlusionFreeCloud->points.push_back(pt);
                        }
                    }
                }
            }
        }
    }
/*
    for ( int i = 0; i < (int)cloud->points.size(); i ++ )
    {
        pt = cloud->points[i];
        t = voxelFilter.getGridCoordinates( pt.x, pt.y, pt.z);

        // check if voxel is occupied, if empty then ignore
        int index = voxelFilter.getCentroidIndexAt (t);
        if (index = -1)
          continue;

        ret = voxelFilter.occlusionEstimation( state,out_ray, t);
        if ( state == -1 )
        {
            std::cout<<"I am -1 negative !\n";
        }
        // estimate direction to target voxel
        Eigen::Vector4f p = voxelFilter.getCentroidCoordinate (t);
        Eigen::Vector4f direction = p - cloud->sensor_origin_;
        direction.normalize ();

        // estimate entry point into the voxel grid
        float tmin = voxelFilter.rayBoxIntersection (cloud->sensor_origin_, direction,p1,p2);
        if(tmin!=-1 && state != 1)
        {
            // coordinate of the boundary of the voxel grid
            Eigen::Vector4f start = cloud->sensor_origin_ + tmin * direction;

            linePoint.x = cloud->sensor_origin_[0]; linePoint.y = cloud->sensor_origin_[1]; linePoint.z = cloud->sensor_origin_[2];
            //            std::cout<<"Box Min X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
            lineSegments.push_back(linePoint);

            linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
            //            std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
            lineSegments.push_back(linePoint);

            // i,j,k coordinate of the voxel were the ray enters the voxel grid
            Eigen::Vector3i ijk = voxelFilter.getGridCoordinates(start[0], start[1], start[2]);

            // centroid coordinate of the entry voxel
            Eigen::Vector4f voxel_max = voxelFilter.getCentroidCoordinate (ijk);
            Eigen::Vector3f leaf_size_= voxelFilter.getLeafSize();

            //            std::cout<<"voxel_max X:"<<voxel_max[0]<<" y:"<< voxel_max[1]<<" z:"<< voxel_max[2]<<"\n";

            if (direction[0] >= 0)
            {
                voxel_max[0] += leaf_size_[0] * 0.5f;
            }
            else
            {
                voxel_max[0] -= leaf_size_[0] * 0.5f;
            }
            if (direction[1] >= 0)
            {
                voxel_max[1] += leaf_size_[1] * 0.5f;
            }
            else
            {
                voxel_max[1] -= leaf_size_[1] * 0.5f;
            }
            if (direction[2] >= 0)
            {
                voxel_max[2] += leaf_size_[2] * 0.5f;
            }
            else
            {
                voxel_max[2] -= leaf_size_[2] * 0.5f;
            }
            //            std::cout<<"voxel_max X:"<<voxel_max[0]<<" y:"<< voxel_max[1]<<" z:"<< voxel_max[2]<<"\n";

            float t_max_x = tmin + (voxel_max[0] - start[0]) / direction[0];
            float t_max_y = tmin + (voxel_max[1] - start[1]) / direction[1];
            float t_max_z = tmin + (voxel_max[2] - start[2]) / direction[2];

            //            std::cout<<"t_max_x X:"<<t_max_x<<" y:"<< t_max_y<<" z:"<< t_max_z<<"\n";

            float t_delta_x = leaf_size_[0] / static_cast<float> (fabs (direction[0]));
            float t_delta_y = leaf_size_[1] / static_cast<float> (fabs (direction[1]));
            float t_delta_z = leaf_size_[2] / static_cast<float> (fabs (direction[2]));

            //            std::cout<<"Direction X:"<<direction[0]<<" y:"<< direction[1]<<" z:"<< direction[2]<<"\n";
            //            std::cout<<"LeafSize X:"<<leaf_size_[0]<<" y:"<< leaf_size_[1]<<" z:"<< leaf_size_[2]<<"\n";
            //            std::cout<<"Delta X:"<<t_delta_x<<" y:"<< t_delta_y<<" z:"<< t_delta_z<<"\n";

            linePoint.x = start[0]; linePoint.y = start[1]; linePoint.z = start[2];
            //            std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
            lineSegments.push_back(linePoint);

            linePoint.x = pt.x; linePoint.y = pt.y; linePoint.z = pt.z;
            //            std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
            lineSegments.push_back(linePoint);

//            linePoint.x = p1.x; linePoint.y = p1.y; linePoint.z = p1.z;
//            std::cout<<"Box Min X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
//            lineSegments.push_back(linePoint);
//            linePoint.x = p2.x; linePoint.y = p2.y; linePoint.z = p2.z;
//            std::cout<<"Box Max X:"<<linePoint.x<<" y:"<< linePoint.y<<" z:"<< linePoint.z<<"\n";
//            lineSegments.push_back(linePoint);

            occlusionFreeCloud->points.push_back(pt);
        }
        if(count++<100 && pt.x>=-1.8 && pt.x<-1.1 && pt.y<0.4 && pt.y>-0.4)
        {
            for(uint j=0; j< out_ray.size(); j++)
            {
                point = pcl::PointXYZRGB(255,0,0);
                Eigen::Vector4f centroid = voxelFilter.getCentroidCoordinate (out_ray[j]);
                point.x = centroid[0];
                point.y = centroid[1];
                point.z = centroid[2];
                rayCloud->points.push_back(point);
            }
        }
    }
*/
    visualization_msgs::Marker linesList = drawLines(lineSegments);

    //*****************Rviz Visualization ************
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        //***marker publishing***
        uint32_t shape = visualization_msgs::Marker::ARROW;
        marker.type = shape;
        marker.action = visualization_msgs::Marker::ADD;
        //visulaization using the markers
        marker.scale.x = 0.5;
        marker.scale.y = 0.1;
        marker.scale.z = 0.1;
        // Set the color -- be sure to set alpha to something non-zero!
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        marker.ns = "basic_shapes";
        marker.id = 2;
        ROS_INFO("Publishing Marker");
        // Set the frame ID and timestamp. See the TF tutorials for information on these.
        marker.pose =  output_vector;
        marker.pose.orientation  = quet;//output_vector.orientation;
        marker.header.frame_id = "base_point_cloud";
        marker.header.stamp = ros::Time::now();
        marker.lifetime = ros::Duration(10);
        // Publish the marker
        pub5.publish(marker);

        //***frustum cull and occlusion cull publish***
        sensor_msgs::PointCloud2 cloud1;
        sensor_msgs::PointCloud2 cloud2;
        sensor_msgs::PointCloud2 cloud3;

        pcl::toROSMsg(*cloud, cloud1);
        pcl::toROSMsg(*occlusionFreeCloud, cloud2);
        pcl::toROSMsg(*rayCloud, cloud3);

        cloud1.header.frame_id = "base_point_cloud";
        cloud2.header.frame_id = "base_point_cloud";
        cloud3.header.frame_id = "base_point_cloud";

        cloud1.header.stamp = ros::Time::now();
        cloud2.header.stamp = ros::Time::now();
        cloud3.header.stamp = ros::Time::now();

        pub1.publish(cloud1);
        pub2.publish(cloud2);
        pub3.publish(cloud3);
        pub4.publish(linesList);

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}