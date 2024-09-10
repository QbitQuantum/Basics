  int FitNullModel(Matrix& mat_Xnull, Matrix& mat_y,
                   const EigenMatrix& kinshipU, const EigenMatrix& kinshipS){
    // type conversion
    Eigen::MatrixXf x;
    Eigen::MatrixXf y;
    G_to_Eigen(mat_Xnull, &x);
    G_to_Eigen(mat_y, &y);
    this->lambda = kinshipS.mat;
    const Eigen::MatrixXf& U = kinshipU.mat;
    // rotate
    this->ux = U.transpose() * x;
    this->uy = U.transpose() * y;

    // get beta, sigma2_g and delta
    // where delta = sigma2_e / sigma2_g
    double loglik[101];
    int maxIndex = -1;
    double maxLogLik = 0;
    for (int i = 0; i <= 100; ++i ){
      double d = exp(-10 + i * 0.2);
      getBetaSigma2(d);
      loglik[i] = getLogLikelihood(d);
      // fprintf(stderr, "%d\tdelta=%g\tll=%lf\n", i, delta, loglik[i]);
      if (std::isnan(loglik[i])) {
        continue;
      }
      if (maxIndex < 0 || loglik[i] > maxLogLik) {
        maxIndex = i;
        maxLogLik = loglik[i];
      }
    }
    if (maxIndex < -1) {
      fprintf(stderr, "Cannot optimize\n");
      return -1;
    }
    if (maxIndex == 0 || maxIndex == 100) {
      // on the boundary
      // do not try maximize it.
    } else {
      gsl_function F;
      F.function = goalFunction;
      F.params = this;

      Minimizer minimizer;
      double lb = exp(-10 + (maxIndex-1) * 0.2);
      double ub = exp(-10 + (maxIndex+1) * 0.2);
      double start =  exp(-10 + maxIndex * 0.2);
      if (minimizer.minimize(F, start, lb, ub)) {
        // fprintf(stderr, "Minimization failed, fall back to initial guess.\n");
        this->delta = start;
      } else {
        this->delta = minimizer.getX();
        // fprintf(stderr, "minimization succeed when delta = %g, sigma2_g = %g\n", this->delta, this->sigma2_g);
      }
    }
    // store some intermediate results
    // fprintf(stderr, "maxIndex = %d, delta = %g, Try brent\n", maxIndex, delta);
    // fprintf(stderr, "beta[%d][%d] = %g\n", (int)beta.rows(), (int)beta.cols(), beta(0,0));
    this->h2 =  1.0 /(1.0 + this->delta);
    this->sigma2 = this->sigma2_g * this->h2;
    
    // we derive different formular to replace original eqn (7)
    this->gamma = (this->lambda.array() / (this->lambda.array() + this->delta)).sum() / this->sigma2_g / (this->ux.rows() - 1 ) ;
    // fprintf(stderr, "gamma = %g\n", this->gamma);
    // transformedY = \Sigma^{-1} * (y_tilda) and y_tilda = y - X * \beta
    // since \Sigma = (\sigma^2_g * h^2 ) * (U * (\lambda + delta) * U')
    // transformedY = 1 / (\sigma^2_g * h^2 ) * (U * (\lambda+delta)^{-1} * U' * (y_tilda))
    //              = 1 / (\sigma^2_g * h^2 ) * (U * \lambda^{-1} * (uResid))
    // since h^2 = 1 / (1+delta)
    // transformedY = (1 + delta/ (\sigma^2_g ) * (U * \lambda^{-1} * (uResid))
    Eigen::MatrixXf resid = y - x * (x.transpose() * x).eval().ldlt().solve(x.transpose() * y); // this is y_tilda
            
    this->transformedY.noalias() =  U.transpose() * resid;
    this->transformedY = (this->lambda.array() + this->delta).inverse().matrix().asDiagonal() * this->transformedY;
    this->transformedY = U * this->transformedY;
    this->transformedY /= this->sigma2_g;
    // fprintf(stderr, "transformedY(0,0) = %g\n", transformedY(0,0));
    
    this->ySigmaY= (resid.array() * transformedY.array()).sum();
    return 0;
  }