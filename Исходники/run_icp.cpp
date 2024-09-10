int
perform_icp(pcl::PointCloud<pcl::PointXYZRGB>::Ptr source_pointcloud, pcl::PointCloud<pcl::PointXYZRGB>::Ptr target_pointcloud, Eigen::Matrix<double, 4, 4> *correction, pcl::PointCloud<pcl::PointXYZRGB>::Ptr source_pointcloud2)
{
	pcl::PointCloud<pcl::PointXYZRGB> out_pcl_pointcloud;
	pcl::PointCloud<pcl::PointXYZRGB> out_pcl_pointcloud_transformed;

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr source_filtered = GridFiltering(source_pointcloud, 0.2);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr target_filtered = GridFiltering(target_pointcloud, 0.2);

	gicp.setInputCloud(source_filtered);
	gicp.setInputTarget(target_filtered);
	gicp.align(out_pcl_pointcloud);
	(*correction) = gicp.getFinalTransformation().cast<double>();

	pcl::transformPointCloud(out_pcl_pointcloud, out_pcl_pointcloud_transformed, (*correction));
	//save_clouds_for_debug(*source_pointcloud, *target_pointcloud, out_pcl_pointcloud_transformed, *source_pointcloud2);

	if(gicp.hasConverged())
	{
		return 1;
	}

	return 0;
}