  void DrawableCovariances::updateCovarianceDrawList() {
    GLParameterCovariances *covariancesParameter = dynamic_cast<GLParameterCovariances*>(_parameter);
    glNewList(_covarianceDrawList, GL_COMPILE); 
    if(_covariances && 
       covariancesParameter && 
       covariancesParameter->show() && 
       covariancesParameter->ellipsoidScale() > 0.0f) {
      float ellipsoidScale = covariancesParameter->ellipsoidScale();
      Eigen::Vector4f colorLowCurvature = covariancesParameter->colorLowCurvature();
      Eigen::Vector4f colorHighCurvature = covariancesParameter->colorHighCurvature();
      float curvatureThreshold = covariancesParameter->curvatureThreshold();
      for(size_t i = 0; i < _covariances->size(); i += covariancesParameter->step()) {
	Stats cov = _covariances->at(i);
	Eigen::Vector3f lambda = cov.eigenValues();
	Eigen::Isometry3f I = Eigen::Isometry3f::Identity();
	I.linear() = cov.eigenVectors();
	if(cov.n() == 0 )
	  continue;
	I.translation() = Eigen::Vector3f(cov.mean()[0], cov.mean()[1], cov.mean()[2]);
	float sx = sqrt(lambda[0]) * ellipsoidScale;
	float sy = sqrt(lambda[1]) * ellipsoidScale;
	float sz = sqrt(lambda[2]) * ellipsoidScale;
	float curvature = cov.curvature();
	glPushMatrix();
	glMultMatrixf(I.data());
	if(curvature > curvatureThreshold) {
	  glColor4f(colorHighCurvature[0] - curvature, colorHighCurvature[1], colorHighCurvature[2], colorHighCurvature[3]);
	  sx = ellipsoidScale;
	  sy = ellipsoidScale;
	  sz = ellipsoidScale;
	}
	else {
	  glColor4f(colorLowCurvature[0], colorLowCurvature[1] - curvature, colorLowCurvature[2], colorLowCurvature[3]);
	  sx = 1e-03;
	  sy = ellipsoidScale;
	  sz = ellipsoidScale;
	}

	glScalef(sx, sy, sz);
	glCallList(_sphereDrawList);
	glPopMatrix();	    
      }   
    }
    glEndList();
  }