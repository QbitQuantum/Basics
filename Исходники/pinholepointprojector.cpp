  void PinholePointProjector::unProject(PointVector &points, 
					Gaussian3fVector &gaussians,
					IntImage &indexImage,
					const DepthImage &depthImage) const {
    assert(depthImage.rows > 0 && depthImage.cols > 0 && "PinholePointProjector: Depth image has zero dimensions");
    points.resize(depthImage.rows * depthImage.cols);
    gaussians.resize(depthImage.rows * depthImage.cols);
    indexImage.create(depthImage.rows, depthImage.cols);
    int count = 0;
    Point *point = &points[0];
    Gaussian3f *gaussian = &gaussians[0];
    float fB = _baseline * _cameraMatrix(0, 0);
    Eigen::Matrix3f J;
    for(int r = 0; r < depthImage.rows; r++) {
      const float *f = &depthImage(r, 0);
      int *i = &indexImage(r, 0);
      for(int c = 0; c < depthImage.cols; c++, f++, i++) {      
	if(!_unProject(*point, c, r, *f)) {
	  *i = -1;
	  continue;
	}
	float z = *f;
	float zVariation = (_alpha * z * z) / (fB + z * _alpha);
	J <<       
	  z, 0, (float)r,
	  0, z, (float)c,
	  0, 0, 1;
	J = _iK * J;
	Diagonal3f imageCovariance(3.0f, 3.0f, zVariation);
	Eigen::Matrix3f cov = J * imageCovariance * J.transpose();
	*gaussian = Gaussian3f(point->head<3>(), cov);
	gaussian++;
	point++;
	*i = count;
	count++;
      }
    }

    points.resize(count);
    gaussians.resize(count);
  }