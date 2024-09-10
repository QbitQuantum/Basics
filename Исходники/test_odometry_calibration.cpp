TEST(OdometryCalibration, Calibration) {
	FileIO fileIO;
	std::string path = ros::package::getPath("odometry_calibration") + "/data/calib.dat";
	try {
		fileIO.loadFromFile(path.c_str());
	} catch(const std::runtime_error& e) {
		ASSERT_TRUE(false) << "Could not load calibration data file";
	}
	Eigen::Matrix3d calibrationMatrix = OdometryCalibration::calibrateOdometry(fileIO.measurements);
	ASSERT_NEAR(-0.0754092, calibrationMatrix.determinant(), 1e-5);
}