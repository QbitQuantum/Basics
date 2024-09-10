  void DrawableTransformCovariance::updateCovarianceDrawList() {
    GLParameterTransformCovariance *covarianceParameter = dynamic_cast<GLParameterTransformCovariance*>(_parameter);
    glNewList(_covarianceDrawList, GL_COMPILE); 
    if(_covariance != Eigen::Matrix3f::Zero() && 
       covarianceParameter && 
       covarianceParameter->show() && 
       covarianceParameter->scale() > 0.0f) {
      float scale = covarianceParameter->scale();
      Eigen::Vector4f color = covarianceParameter->color();
      
      Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigenSolver;
      eigenSolver.computeDirect(_covariance, Eigen::ComputeEigenvectors);

      Eigen::Vector3f lambda = eigenSolver.eigenvalues();      
      Eigen::Isometry3f I = Eigen::Isometry3f::Identity();
      I.linear() = eigenSolver.eigenvectors();
      I.translation() = Eigen::Vector3f(_mean.x(), _mean.y(), _mean.z());
      
      float sx = sqrt(lambda[0]) * scale;
      float sy = sqrt(lambda[1]) * scale;
      float sz = sqrt(lambda[2]) * scale;
      
      glPushMatrix();
      glMultMatrixf(I.data());
      glColor4f(color[0], color[1], color[2], color[3]);
      glScalef(sx, sy, sz);
      glCallList(_sphereDrawList);
      glPopMatrix();	    
    }
    glEndList();
  }