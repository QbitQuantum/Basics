bool
IncrementalPoseEstimatorFromRgbFeatures::optimizeWithICP(
    pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_source,
    Pose3D& depth_pose,
    int closest_view_index)
{
    pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_target = m_image_data[closest_view_index].sampled_cloud;
    pcl::PointCloud<pcl::PointXYZ> cloud_reg;

    Pose3D new_depth_pose = depth_pose;

    ntk_dbg_print(cloud_source->points.size(), 1);
    ntk_dbg_print(cloud_target->points.size(), 1);

    IterativeClosestPoint<PointXYZ, PointXYZ> reg;

    reg.setInputCloud (cloud_target);
    reg.setInputTarget (cloud_source);

    reg.setMaximumIterations (50);
    reg.setTransformationEpsilon (1e-5);
    reg.setMaxCorrespondenceDistance (0.5);
    reg.align (cloud_reg);

    if (!reg.hasConverged())
    {
        ntk_dbg(1) << "ICP did not converge, ignoring.";
        return false;
    }

    ntk_dbg_print(reg.getFitnessScore(), 1);

    Eigen::Matrix4f t = reg.getFinalTransformation ();
    cv::Mat1f T(4,4);
    //toOpencv(t,T);
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            T(r,c) = t(r,c);

    Pose3D icp_pose;
    icp_pose.setCameraTransform(T);

    new_depth_pose.applyTransformAfter(icp_pose);
    depth_pose = new_depth_pose;
    return true;
}