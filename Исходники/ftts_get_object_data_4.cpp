/**
 * @function onMouse
 * @brief Tells the point location
 */
static void onMouse( int event, int x, int y, int flags, void* userdata ) {
  
  if( event != cv::EVENT_LBUTTONDOWN ) {
    return;
  }
  mutex.lock();
  cv::Point3f p; Eigen::Vector3d currentPoint;
  p = gXyzImg.at<cv::Point3f>(y,x);
  currentPoint << (double)p.x, (double)p.y, (double)p.z;
  std::cout << "\t * Mouse pressed. Current point: "<< currentPoint.transpose() << std::endl;
  
  double minDist; int minIndex; double dist;

  gSelectedCluster = -1;

    for( int i = 0; i < gClustersBB.size(); ++i ) {
      int cx, cy;
      cx = (gClustersBB[i](0) + gClustersBB[i](2) )/2;
      cy = (gClustersBB[i](1) + gClustersBB[i](3) )/2;
      dist = (x-cx)*(x-cx) + (y-cy)*(y-cy);
      if( i == 0 ) { minIndex = 0; minDist = dist; }
      else { if( dist < minDist ) { minIndex = i; minDist = dist; } }
    }

    gSelectedCluster = minIndex;

    saveData();
    mutex.unlock();
}