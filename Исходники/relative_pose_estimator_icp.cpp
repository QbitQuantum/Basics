bool RelativePoseEstimatorICP :: estimateNewPose(const RGBDImage& image)
{
    if (m_ref_cloud.points.size() < 1)
    {
        ntk_dbg(1) << "Reference cloud was empty";
        return false;
    }

    PointCloud<PointXYZ>::Ptr target = m_ref_cloud.makeShared();
    PointCloud<PointXYZ>::Ptr source (new PointCloud<PointXYZ>());
    rgbdImageToPointCloud(*source, image);

    PointCloud<PointXYZ>::Ptr filtered_source (new PointCloud<PointXYZ>());
    PointCloud<PointXYZ>::Ptr filtered_target (new PointCloud<PointXYZ>());

    pcl::VoxelGrid<pcl::PointXYZ> grid;
    grid.setLeafSize (m_voxel_leaf_size, m_voxel_leaf_size, m_voxel_leaf_size);

    grid.setInputCloud(source);
    grid.filter(*filtered_source);

    grid.setInputCloud(target);
    grid.filter(*filtered_target);

    PointCloud<PointXYZ> cloud_reg;
    IterativeClosestPoint<PointXYZ, PointXYZ> reg;
    reg.setMaximumIterations (m_max_iterations);
    reg.setTransformationEpsilon (1e-5);
    reg.setMaxCorrespondenceDistance (m_distance_threshold);
    reg.setInputCloud (filtered_source);
    reg.setInputTarget (filtered_target);
    reg.align (cloud_reg);

    if (!reg.hasConverged())
    {
      ntk_dbg(1) << "ICP did not converge, ignoring.";
      return false;
    }

    Eigen::Matrix4f t = reg.getFinalTransformation ();
    cv::Mat1f T(4,4);
    //toOpencv(t,T);
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            T(r,c) = t(r,c);

    Pose3D icp_pose;
    icp_pose.setCameraTransform(T);
    ntk_dbg_print(icp_pose.cvTranslation(), 1);

    // Pose3D stores the transformation from 3D space to image.
    // So we have to invert everything so that unprojecting from
    // image to 3D gives the right transformation.
    // H2' = ICP * H1'
    m_current_pose.resetCameraTransform();
    m_current_pose = *image.calibration()->depth_pose;
    m_current_pose.invert();
    m_current_pose.applyTransformAfter(icp_pose);
    m_current_pose.invert();
    return true;
}