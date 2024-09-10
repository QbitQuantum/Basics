void SFMViewer::update(std::vector<cv::Point3d> pcld,
		std::vector<cv::Vec3b> pcldrgb,
		std::vector<cv::Point3d> pcld_alternate,
		std::vector<cv::Vec3b> pcldrgb_alternate,
		std::vector<cv::Matx34d> cameras) {
	m_pcld = pcld;
	m_pcldrgb = pcldrgb;
	m_cameras = cameras;

	//get the scale of the result cloud using PCA
	{
		cv::Mat_<double> cldm(pcld.size(), 3);
		for (unsigned int i = 0; i < pcld.size(); i++) {
			cldm.row(i)(0) = pcld[i].x;
			cldm.row(i)(1) = pcld[i].y;
			cldm.row(i)(2) = pcld[i].z;
		}
		cv::Mat_<double> mean; //cv::reduce(cldm,mean,0,CV_REDUCE_AVG);
		cv::PCA pca(cldm, mean, CV_PCA_DATA_AS_ROW);
		scale_cameras_down = 1.0 / (3.0 * sqrt(pca.eigenvalues.at<double> (0)));
//		std::cout << "emean " << mean << std::endl;
//		m_global_transform = Eigen::Translation<double,3>(-Eigen::Map<Eigen::Vector3d>(mean[0]));
	}

	//compute transformation to place cameras in world
	m_cameras_transforms.resize(m_cameras.size());
	Eigen::Vector3d c_sum(0,0,0);
	for (int i = 0; i < m_cameras.size(); ++i) {
		Eigen::Matrix<double, 3, 4> P = Eigen::Map<Eigen::Matrix<double, 3, 4,
				Eigen::RowMajor> >(m_cameras[i].val);
		Eigen::Matrix3d R = P.block(0, 0, 3, 3);
		Eigen::Vector3d t = P.block(0, 3, 3, 1);
		Eigen::Vector3d c = -R.transpose() * t;
		c_sum += c;
		m_cameras_transforms[i] =
				Eigen::Translation<double, 3>(c) *
				Eigen::Quaterniond(R) *
				Eigen::UniformScaling<double>(scale_cameras_down)
				;
	}

	m_global_transform = Eigen::Translation<double,3>(-c_sum / (double)(m_cameras.size()));
//	m_global_transform = m_cameras_transforms[0].inverse();

	updateGL();
}