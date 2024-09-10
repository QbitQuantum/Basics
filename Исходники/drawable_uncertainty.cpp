  void DrawableUncertainty::updateCovarianceDrawList() {
    GLParameterUncertainty *uncertaintyParameter = dynamic_cast<GLParameterUncertainty*>(_parameter);
    glNewList(_covarianceDrawList, GL_COMPILE); 
    if(_covarianceDrawList &&
       _covariances && 
       uncertaintyParameter && 
       uncertaintyParameter->ellipsoidScale() > 0.0f) {
      uncertaintyParameter->applyGLParameter();
      Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigenSolver;
      float ellipsoidScale = uncertaintyParameter->ellipsoidScale();
      for(size_t i = 0; i < _covariances->size(); i += uncertaintyParameter->step()) {
	Gaussian3f &gaussian3f = _covariances->at(i);
	Eigen::Matrix3f covariance = gaussian3f.covarianceMatrix();
	Eigen::Vector3f mean = gaussian3f.mean();
	eigenSolver.computeDirect(covariance, Eigen::ComputeEigenvectors);
	Eigen::Vector3f eigenValues = eigenSolver.eigenvalues();      
	Eigen::Isometry3f I = Eigen::Isometry3f::Identity();
	I.linear() = eigenSolver.eigenvectors();
	I.translation() = mean;
	float sx = sqrt(eigenValues[0]) * ellipsoidScale;
	float sy = sqrt(eigenValues[1]) * ellipsoidScale;
	float sz = sqrt(eigenValues[2]) * ellipsoidScale;
	glPushMatrix();
	glMultMatrixf(I.data());	
	sx = sx;
	sy = sy;
	sz = sz;
	glScalef(sx, sy, sz);
	glCallList(_sphereDrawList);
	glPopMatrix();	    
      }   
    }
    glEndList();
  }