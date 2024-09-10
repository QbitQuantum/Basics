void PointWithNormalMerger::computeAccumulator() {
  // Compute skin.
  _indexImage.resize(480*_scale, 640*_scale);
  Matrix3f _scaledCameraMatrix = _cameraMatrix;
  _scaledCameraMatrix.block<2, 3>(0, 0) *= _scale;
  _points.toIndexImage(_indexImage, _depthImage, _scaledCameraMatrix, Isometry3f::Identity());
  
  // Compute sigma for each point and create image accumulator.
  PixelMapper pm;
  pm.setCameraMatrix(_scaledCameraMatrix);
  pm.setTransform(Isometry3f::Identity());
  Matrix3f inverseCameraMatrix = _scaledCameraMatrix.inverse();
  float fB = (_baseLine * _scaledCameraMatrix(0, 0)); // kinect baseline * focal lenght;
  CovarianceAccumulator covAcc;
  _covariances.resize(480*_scale, 640*_scale);
  _covariances.fill(covAcc);
  for(size_t i = 0; i < _points.size(); i++ ) {
    PointWithNormal &p = _points[i];
    Vector2i coord = pm.imageCoords(pm.projectPoint(p.point()));
    if(coord[0] < 0 || coord[0] >= _depthImage.cols() ||
       coord[1] < 0 || coord[1] >= _depthImage.rows())
      continue;
    int index = _indexImage(coord[1], coord[0]);
    float skinZ = _depthImage(coord[1], coord[0]);
    Vector3f normal = p.normal();
    Vector3f skinNormal = _points[index].normal();
    float z = p[2];
    if(abs(z - skinZ) > 0.05)
      continue;
    if(acosf(skinNormal.dot(normal)) > M_PI/4.0f)
      continue;
    float zVariation = (_alpha*z*z)/(fB+z*_alpha);
    zVariation *= zVariation;
    Diagonal3f imageCovariance(1.0f, 1.0f, zVariation);
    Matrix3f covarianceJacobian;
    covarianceJacobian <<
      z, 0, (float)coord[0],
      0, z, (float)coord[1],
      0, 0, 1;
    covarianceJacobian = inverseCameraMatrix*covarianceJacobian;
    Matrix3f worldCovariance = covarianceJacobian * imageCovariance * covarianceJacobian.transpose();
    _covariances(coord[1], coord[0])._omegaAcc += worldCovariance.inverse();
    _covariances(coord[1], coord[0])._pointsAcc += worldCovariance.inverse()*p.point();
    _covariances(coord[1], coord[0])._used = true;
  }
}