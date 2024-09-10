void PointWithNormalStatistcsGenerator::computeNormalsAndSVD(PointWithNormalVector& points, PointWithNormalSVDVector& svds, const Eigen::MatrixXi& indices, 
							     const Eigen::Matrix3f& cameraMatrix, const Eigen::Isometry3f& transform){
  _integralImage.compute(indices,points);
  int q=0;
  int outerStep = _numThreads * _step;
  PixelMapper pixelMapper;
  pixelMapper.setCameraMatrix(cameraMatrix);
  pixelMapper.setTransform(transform);
  Eigen::Isometry3f inverseTransform = transform.inverse();
  #pragma omp parallel
  {
#ifdef _PWN_USE_OPENMP_
    int threadNum = omp_get_thread_num();
#else // _PWN_USE_OPENMP_
    int threadNum = 0; 
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigenSolver;
#endif // _PWN_USE_OPENMP_

    for (int c=threadNum; c<indices.cols(); c+=outerStep) {
#ifdef _PWN_USE_OPENMP_
      Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigenSolver;
#endif // _PWN_USE_OPENMP_
      for (int r=0; r<indices.rows(); r+=_step, q++){
	int index  = indices(r,c);
	//cerr << "index("  << r <<"," << c << ")=" << index <<  endl;
	if (index<0)
	  continue;
	// determine the region
	PointWithNormal& point = points[index];
	PointWithNormalSVD& originalSVD = svds[index];
	PointWithNormalSVD svd;
	Eigen::Vector3f normal = point.normal();
	Eigen::Vector3f coord = pixelMapper.projectPoint(point.point()+Eigen::Vector3f(_worldRadius, _worldRadius, 0));
	svd._z=point(2);

	coord.head<2>()*=(1./coord(2));
	int dx = abs(c - coord[0]);
	int dy = abs(r - coord[1]);
	if (dx>_imageRadius)
	  dx = _imageRadius;
	if (dy>_imageRadius)
	  dy = _imageRadius;
	PointAccumulator acc = _integralImage.getRegion(c-dx, c+dx, r-dy, r+dy);
	svd._mean=point.point();
	if (acc.n()>_minPoints){
	  Eigen::Vector3f mean = acc.mean();
	  svd._mean = mean;
	  svd._n = acc.n();
	  Eigen::Matrix3f cov  = acc.covariance();
	  eigenSolver.compute(cov);
	  svd._U=eigenSolver.eigenvectors();
	  svd._singularValues=eigenSolver.eigenvalues();
	  if (svd._singularValues(0) <0)
	    svd._singularValues(0) = 0;
	  /*
	    cerr << "\t svd.singularValues():" << svd.singularValues() << endl;
	    cerr << "\t svd.U():" << endl << svd.U() << endl;
	    //cerr << "\t svd.curvature():" << svd.curvature() << endl;
	
	    */
	

	  normal = eigenSolver.eigenvectors().col(0).normalized();
	  if (normal.dot(inverseTransform * mean) > 0.0f)
	    normal =-normal;
	  svd.updateCurvature();
	  //cerr << "n(" << index << ") c:"  << svd.curvature() << endl << point.tail<3>() << endl;
	  if (svd.curvature()>_maxCurvature){
	    //cerr << "region: " << c-dx << " " <<  c+dx << " " <<  r-dx << " " << r+dx << " points: " << acc.n() << endl;
	    normal.setZero();
	  } 
	} else {
	  normal.setZero();
	  svd = PointWithNormalSVD();
	}
	if (svd.n() > originalSVD.n()){
	  originalSVD = svd;
	  point.setNormal(normal);
	}
      } 
    }
  }
}