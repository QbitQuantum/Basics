void MapBuilder::onCloudFrame2(pcl::PointCloud<pcl::PointXYZ>::Ptr frame, pcl::PointXY sensorOffset, RobotPosition pose)
{


    //Transform current cloud to match robot's position
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_transformed (new pcl::PointCloud<pcl::PointXYZ>);
    double mx =  pose.X + sensorOffset.x;
    double my =  pose.Y + sensorOffset.y;
    double mt = AngleUtils::degToRads(pose.Heading);
    Eigen::Vector3f translation(mx, my, 0);
    Eigen::Quaternionf rotation(Eigen::AngleAxisf(-mt, Eigen::Vector3f::UnitZ()));
    pcl::transformPointCloud(*frame, *cloud_transformed, translation, rotation);

    // ICP to refine cloud alignment
    if(false)//!cloud->empty())
    {
        //Use ICP to fix errors in transformation
        pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
        icp.setMaxCorrespondenceDistance(2);
        icp.setMaximumIterations(30);
        icp.setInputSource(cloud_transformed);
        icp.setInputTarget(cloud);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_aligned (new pcl::PointCloud<pcl::PointXYZ>);
        icp.align(*cloud_aligned);

        if(icp.hasConverged())
        {
            //Add aligned cloud points to map cloud
            (*cloud) += *cloud_aligned;
        }
        else
        {
            //Ignore alignment atempt
            std::cout << "No convergence." << std::endl;
            (*cloud) += *cloud_transformed;
        }
    }
    else
    {
        //Add first cloud's points to map cloud
        (*cloud) += *cloud_transformed;
    }

    //Run map cloud through a VoxelGrid to remove any duplicate points
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_removedDuplicates (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::VoxelGrid<pcl::PointXYZ> duplicateRemover;

    duplicateRemover.setInputCloud(cloud);
    float leafSize = ConfigManager::Instance().getValue("MapBuilder", "VoxelLeafSize", 0.25);
    duplicateRemover.setLeafSize (leafSize, leafSize, leafSize);
    duplicateRemover.filter(*cloud_removedDuplicates);

    cloud.swap(cloud_removedDuplicates);

    onNewMap(cloud);
}