  /** \brief Computes the gradient parameters of the patch (patch gradient components dx_ dy_, Hessian H_, Shi-Tomasi Score s_, Eigenvalues of the Hessian e0_ and e1_).
   *         The expanded patch patchWithBorder_ must be set.
   *         Sets validGradientParameters_ afterwards to true.
   */
  void computeGradientParameters() const{
    if(!validGradientParameters_){
      H_.setZero();
      const int refStep = patchSize+2;
      float* it_dx = dx_;
      float* it_dy = dy_;
      const float* it;
      Eigen::Vector3f J;
      J.setZero();
      for(int y=0; y<patchSize; ++y){
        it = patchWithBorder_ + (y+1)*refStep + 1;
        for(int x=0; x<patchSize; ++x, ++it, ++it_dx, ++it_dy){
          J[0] = 0.5 * (it[1] - it[-1]);
          J[1] = 0.5 * (it[refStep] - it[-refStep]);
          J[2] = 1;
          *it_dx = J[0];
          *it_dy = J[1];
          H_ += J*J.transpose();
        }
      }
      const float dXX = H_(0,0)/(patchSize*patchSize);
      const float dYY = H_(1,1)/(patchSize*patchSize);
      const float dXY = H_(0,1)/(patchSize*patchSize);

      e0_ = 0.5 * (dXX + dYY - sqrtf((dXX + dYY) * (dXX + dYY) - 4 * (dXX * dYY - dXY * dXY)));
      e1_ = 0.5 * (dXX + dYY + sqrtf((dXX + dYY) * (dXX + dYY) - 4 * (dXX * dYY - dXY * dXY)));
      s_ = e0_;
      validGradientParameters_ = true;
    }
  }