 Eigen::MatrixXd grad(const Eigen::VectorXd& x, const GP& gp) const
 {
     Eigen::MatrixXd grad = Eigen::MatrixXd::Zero(_tr.rows(), h_params_size());
     Eigen::VectorXd m = _mean_function(x, gp);
     for (int i = 0; i < _tr.rows(); i++) {
         grad.block(i, i * _tr.cols(), 1, _tr.cols() - 1) = m.transpose();
         grad(i, (i + 1) * _tr.cols() - 1) = 1;
     }
     if (_mean_function.h_params_size() > 0) {
         Eigen::MatrixXd m_grad = Eigen::MatrixXd::Zero(_tr.rows() + 1, _mean_function.h_params_size());
         m_grad.block(0, 0, _tr.rows(), _mean_function.h_params_size()) = _mean_function.grad(x, gp);
         Eigen::MatrixXd gg = _tr * m_grad;
         grad.block(0, h_params_size() - _mean_function.h_params_size(), _tr.rows(), _mean_function.h_params_size()) = gg;
     }
     return grad;
 }