/*
 * Calculates Jerk Minimizing Trajectory for start, end and T.
 */
void Ptg::JMT(double* coeffs, struct model* start, struct model* end, double T)
{
  coeffs[0] = start->m;
  coeffs[1] = start->m_dot;
  coeffs[2] = start->m_ddot / 2.0;
  double c_0 = coeffs[0] + coeffs[1] * T + coeffs[2] * T * T;
  double c_1 = coeffs[1] + 2 * coeffs[2] * T;
  double c_2 = 2 * coeffs[2];

  // A*X = B
  MatrixXd A = MatrixXd::Zero(3, 3);
  A <<  T*T*T, T*T*T*T, T*T*T*T*T,
        3*T*T, 4*T*T*T, 5*T*T*T*T,
          6*T,  12*T*T,  20*T*T*T;

  VectorXd B = VectorXd::Zero(3);
  B <<  end->m - c_0,
        end->m_dot - c_1,
        end->m_ddot - c_2;

  VectorXd X = A.inverse() * B;
  coeffs[3] = X[0];
  coeffs[4] = X[1];
  coeffs[5] = X[2];
}