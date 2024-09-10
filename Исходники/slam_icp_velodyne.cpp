int runGeneralizedICP(pcl::PointCloud<pcl::PointXYZRGB>::Ptr source_pointcloud,
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr target_pointcloud,
		Eigen::Matrix<double, 4, 4> source_pointcloud_pose,
		Eigen::Matrix<double, 4, 4> target_pointcloud_pose,
		Eigen::Matrix<double, 4, 4> *out_pose,
		int current_index,
		int before_index)
{

	static int is_first_icp_run = 1;

	Eigen::Matrix<double, 4, 4> out_transform;
	Eigen::Matrix<double, 4, 4> src_transform;
	Eigen::Matrix<double, 4, 4> final_transform;

	/**************************************/
	/********** Initializations ***********/
	/**************************************/

	pcl::PointCloud<pcl::PointXYZRGB>::Ptr src_pcl_pointcloud_corrected =
			boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB> >(
					new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr tgt_pcl_pointcloud_corrected =
			boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB> >(
					new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud < pcl::PointXYZRGB > out_pcl_pointcloud;
	pcl::PointCloud < pcl::PointXYZRGB > out_pcl_pointcloud_transformed;

	/**************************************/
	/**************** GICP ****************/
	/**************************************/

//	if (is_first_icp_run) {
//		accumulated_correction_transform =
//				Eigen::Matrix<double, 4, 4>().Identity();
//		is_first_icp_run = 0;
//	}

//	source_pointcloud_pose = accumulated_correction_transform
//			* source_pointcloud_pose;
//	target_pointcloud_pose = accumulated_correction_transform
//			* target_pointcloud_pose;

	pcl::transformPointCloud(*source_pointcloud, *src_pcl_pointcloud_corrected,
			(target_pointcloud_pose.inverse() * source_pointcloud_pose).cast<float>());

	pcl::transformPointCloud(*target_pointcloud, *tgt_pcl_pointcloud_corrected,
			Eigen::Matrix<float, 4, 4>().Identity());

	gicp.setInputCloud(src_pcl_pointcloud_corrected);
	gicp.setInputTarget(tgt_pcl_pointcloud_corrected);
	gicp.align(out_pcl_pointcloud);

	out_transform = //target_pointcloud_pose *
			gicp.getFinalTransformation().cast<double>();
//			* target_pointcloud_pose.inverse();
	//*corrected_pose = final_transform = source_pointcloud_pose;

	src_pcl_pointcloud_corrected->clear();
	tgt_pcl_pointcloud_corrected->clear();

	if (gicp.hasConverged())
	{
		*out_pose = out_transform;
		return 1;
	}

	return 0;
}