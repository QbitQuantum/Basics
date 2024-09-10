    void CovarianceEstimator::update(uint i, const Eigen::VectorXd &sample)
    {
      // 10 is theoretically optimal
      double n = (double)lengths_[i] + 10 * sample.size();

      a_[i] = a_[i] * (n / (n + 1)) + (sample * sample.transpose()) / (n + 1);
      u_[i] = u_[i] * (n / (n + 1)) + sample / (n + 1);

      covs_[i] = a_[i] - (u_[i] * u_[i].transpose());// / (n + 1);

      lengths_[i]++;
    }