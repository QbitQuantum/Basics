void CrichtonView<PointT>::onMouse( int event, int x, int y, int flags, void* userdata ) {
  
  if( event != cv::EVENT_LBUTTONDOWN ) {
    return;
  }
  mMutex.lock();
  cv::Point3f p; Eigen::Vector3d currentPoint;
  p = mPclMap.at<cv::Point3f>(y,x);
  currentPoint << (double)p.x, (double)p.y, (double)p.z;
  std::cout << "\t * Mouse pressed. Current point: "<< currentPoint.transpose() << std::endl;
  
  double minDist; int minIndex; double dist;

  mSelectedCluster = -1;

    for( int i = 0; i < mClustersBB.size(); ++i ) {
      int cx, cy;
      cx = (mClustersBB[i](0) + mClustersBB[i](2) )/2;
      cy = (mClustersBB[i](1) + mClustersBB[i](3) )/2;
      dist = (x-cx)*(x-cx) + (y-cy)*(y-cy);
      if( i == 0 ) { minIndex = 0; minDist = dist; }
      else { if( dist < minDist ) { minIndex = i; minDist = dist; } }
    }

    mSelectedCluster = minIndex;
    printf("\t * Selected cluster: %d \n", mSelectedCluster );
    mMutex.unlock();
}