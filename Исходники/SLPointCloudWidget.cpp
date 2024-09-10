void SLPointCloudWidget::updateCalibration(){

    CalibrationData calibration;
    bool load_result = calibration.load("calibration.xml");
	if (!load_result)
		return;
    // Camera coordinate system
    visualizer->addCoordinateSystem(50, "camera", 0);

    // Projector coordinate system
    cv::Mat TransformPCV(4, 4, CV_32F, 0.0);
    cv::Mat(calibration.Rp).copyTo(TransformPCV.colRange(0, 3).rowRange(0, 3));
    cv::Mat(calibration.Tp).copyTo(TransformPCV.col(3).rowRange(0, 3));
    TransformPCV.at<float>(3, 3) = 1.0; // make it homogeneous 
    Eigen::Affine3f TransformP;
    cv::cv2eigen(TransformPCV, TransformP.matrix());

    visualizer->addCoordinateSystem(50, TransformP.inverse(), "projector", 0);
}