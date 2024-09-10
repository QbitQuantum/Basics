void fi::VPDetectionWrapper::validateVanishingPoint(const std::vector<std::vector< Eigen::Vector2f> > &computed_vp_hypothesis, const Eigen::Matrix3f &cam_calib, Eigen::Vector3f &final_robust_vp_x, Eigen::Vector3f &final_robust_vp_y)
{
	Eigen::Matrix3f inv_cam_calib = cam_calib.inverse(); 

	//trans from vps to rays through camera axis, see Z+H Chapter 8, more on single view geometry!
	unsigned int num_vps = computed_vp_hypothesis.size();
	std::vector< Eigen::Vector3f> computed_vp_hypothesis_x;
	std::vector< Eigen::Vector3f> computed_vp_hypothesis_y;
	std::vector< Eigen::Vector3f> computed_vp_hypothesis_z;
	for (unsigned int i = 0; i < num_vps; i++)
	{
		std::vector<Eigen::Vector2f> a_vp = computed_vp_hypothesis.at(i);

		Eigen::Vector2f a_x = a_vp.at(0);
		Eigen::Vector3f x_h, n_x;
		x_h(0) = a_x(0);
		x_h(1) = a_x(1);
		x_h(2) = 1;
		n_x = inv_cam_calib * x_h;
		n_x = n_x.normalized();
		computed_vp_hypothesis_x.push_back(n_x);

		Eigen::Vector2f a_y = a_vp.at(1);
		Eigen::Vector3f y_h, n_y;
		y_h(0) = a_y(0);
		y_h(1) = a_y(1);
		y_h(2) = 1;
		n_y = inv_cam_calib * y_h;
		n_y = n_y.normalized();
		computed_vp_hypothesis_y.push_back(n_y);

		Eigen::Vector2f a_z = a_vp.at(2);
		Eigen::Vector3f z_h, n_z;
		z_h(0) = a_z(0);
		z_h(1) = a_z(1);
		z_h(2) = 1;
		n_z = inv_cam_calib * z_h;
		n_z = n_z.normalized();
		computed_vp_hypothesis_z.push_back(n_z);
	}

	std::vector<Eigen::Vector3f> in_liers_x;
	std::vector<Eigen::Vector3f> in_liers_y;
	std::vector<Eigen::Vector3f> in_liers_z;
	bool found_inliers_x = getRansacInliers(computed_vp_hypothesis_x, in_liers_x);
	bool found_inliers_y = getRansacInliers(computed_vp_hypothesis_y, in_liers_y);
	bool found_inliers_z = getRansacInliers(computed_vp_hypothesis_z, in_liers_z);

	Eigen::VectorXf optimized_vp_x;
	Eigen::VectorXf optimized_vp_y;
	Eigen::VectorXf optimized_vp_z;
	leastQuaresVPFitting(in_liers_x, optimized_vp_x);
	leastQuaresVPFitting(in_liers_y, optimized_vp_y);
	leastQuaresVPFitting(in_liers_z, optimized_vp_z);
        std::cout<<"Vanishing Points Validated"<<std::endl;

	//test the angles and see if OK otherwise check again if truelly orthogonal
	Eigen::Vector3f vp_x (optimized_vp_x[3], optimized_vp_x[4], optimized_vp_x[5]);;
	Eigen::Vector3f vp_y (optimized_vp_y[3], optimized_vp_y[4], optimized_vp_y[5]);
	Eigen::Vector3f vp_z (optimized_vp_z[3], optimized_vp_z[4], optimized_vp_z[5]);

	Eigen::Vector3f vp_x_centroid (optimized_vp_x[0], optimized_vp_x[1], optimized_vp_x[2]);
	Eigen::Vector3f vp_y_centroid (optimized_vp_y[0], optimized_vp_y[1], optimized_vp_y[2]);
	Eigen::Vector3f vp_z_centroid (optimized_vp_z[0], optimized_vp_z[1], optimized_vp_z[2]);

	float angle_value_radiens_cxy = angleBetweenVectors(vp_x_centroid, vp_y_centroid);
	float angle_value_degrees_cxy = pcl::rad2deg(angle_value_radiens_cxy);
	float angle_value_radiens_cxz = angleBetweenVectors(vp_x_centroid, vp_z_centroid);
	float angle_value_degrees_cxz = pcl::rad2deg(angle_value_radiens_cxz);
	float angle_value_radiens_cyz = angleBetweenVectors(vp_y_centroid, vp_z_centroid);
	float angle_value_degrees_cyz = pcl::rad2deg(angle_value_radiens_cyz);

	float angle_value_radiens_xy = angleBetweenVectors(vp_x, vp_y);
	float angle_value_degrees_xy = pcl::rad2deg(angle_value_radiens_xy);
	float angle_value_radiens_xz = angleBetweenVectors(vp_x, vp_z);
	float angle_value_degrees_xz = pcl::rad2deg(angle_value_radiens_xz);
	float angle_value_radiens_yz = angleBetweenVectors(vp_y, vp_z);
	float angle_value_degrees_yz = pcl::rad2deg(angle_value_radiens_yz);

	//collect only the mean vps
	final_robust_vp_x = optimized_vp_x.tail<3> ();
	final_robust_vp_y = optimized_vp_y.tail<3> ();

	//final_robust_vp_x = vp_x_centroid;
	//final_robust_vp_y = vp_y_centroid;
}