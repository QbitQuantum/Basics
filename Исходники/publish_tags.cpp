Eigen::Isometry3d getRelativeTransform(TagMatch const& match, Eigen::Matrix3d const & camera_matrix, const Eigen::Vector4d &distortion_coefficients, double tag_size) 
{
  std::vector<cv::Point3f> objPts;
  std::vector<cv::Point2f> imgPts;
  double s = tag_size/2.;
  objPts.push_back(cv::Point3f(-s,-s, 0));
  objPts.push_back(cv::Point3f( s,-s, 0));
  objPts.push_back(cv::Point3f( s, s, 0));
  objPts.push_back(cv::Point3f(-s, s, 0));


  imgPts.push_back(match.p0);
  imgPts.push_back(match.p1);
  imgPts.push_back(match.p2);
  imgPts.push_back(match.p3);

  cv::Mat rvec, tvec;
  cv::Matx33f cameraMatrix(
                           camera_matrix(0,0), 0, camera_matrix(0,2),
                           0, camera_matrix(1,1), camera_matrix(1,2),
                           0,  0,  1);

  cv::Vec4f distParam(distortion_coefficients(0), distortion_coefficients(1), distortion_coefficients(2), distortion_coefficients(3)); 
  cv::solvePnP(objPts, imgPts, cameraMatrix, distParam, rvec, tvec);
  cv::Matx33d r;
  cv::Rodrigues(rvec, r);
  Eigen::Matrix3d wRo;
  wRo << r(0,0), r(0,1), r(0,2), r(1,0), r(1,1), r(1,2), r(2,0), r(2,1), r(2,2);

  Eigen::Isometry3d T; 
  T.linear() = wRo;
  T.translation() << tvec.at<double>(0), tvec.at<double>(1), tvec.at<double>(2);
  return T;
}