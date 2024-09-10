      // see Rasmussen and Williams, 2006 (p. 114)
      Eigen::VectorXd log_likelihood_grad(const Eigen::VectorXd& h_params,
                                          bool update_kernel = true) {
        this->_kernel_function.set_h_params(h_params);
        if (update_kernel)
          this->_compute_kernel();
        size_t n = this->_observations.size();

        /// what we should write, but it is less numerically stable than using the Cholesky decomposition
        // Eigen::MatrixXd alpha = this->_inverted_kernel * this->_obs_mean;
        //  Eigen::MatrixXd w = alpha * alpha.transpose() - this->_inverted_kernel;

        // alpha = K^{-1} * this->_obs_mean;
        Eigen::VectorXd alpha = this->_llt.matrixL().solve(this->_obs_mean);
        this->_llt.matrixL().adjoint().solveInPlace(alpha);

        // K^{-1} using Cholesky decomposition
        Eigen::MatrixXd w = Eigen::MatrixXd::Identity(n, n);
        this->_llt.matrixL().solveInPlace(w);
        this->_llt.matrixL().transpose().solveInPlace(w);

        // alpha * alpha.transpose() - K^{-1}
        w = alpha * alpha.transpose() - w;

        // only compute half of the matrix (symmetrical matrix)
        Eigen::VectorXd grad =
          Eigen::VectorXd::Zero(this->_kernel_function.h_params_size());
        for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j <= i; ++j) {
            Eigen::VectorXd g = this->_kernel_function.grad(this->_samples[i], this->_samples[j]);
            if (i == j)
              grad += w(i, j) * g * 0.5;
            else
              grad += w(i, j) * g;
          }
        }
        return grad;
      }