void PushObject::updateModel(const Eigen::MatrixXd& traj, GRBQuadExpr& objective) {
  VectorXd& times = m_problem->m_times;
  MatrixXd perts_tk = getSinBasis(times/times.maxCoeff(), fmin(6, times.size()/2));
  MatrixXd pinvperts_tk = perts_tk * (perts_tk.transpose() * perts_tk).inverse();

  m_exactObjective = simulateTraj2(traj, true); // current value
  LOG_INFO_FMT("current val: %.3f", m_exactObjective);
  
  MatrixXd dy_jk(traj.cols(), perts_tk.cols());
  double eps = 3e-4; // scale for joint angle change
  
  Matrix3d A;
  A << sq(eps/2), eps/2, 1,
        0, 0, 1,
      sq(eps/2),  -eps/2,   1;
  Matrix3d Ainv = A.inverse();
  MatrixXd grad_tj(traj.rows(), traj.cols());

  m_obj = GRBQuadExpr(0);

  
  for (int j = 0; j < traj.cols(); ++j) {

    VarVector v;
    VectorXd vactual(traj.rows()-1);
    for (int t=1; t < traj.rows(); ++t) {
      v.push_back(m_problem->m_trajVars.at(t,j));
      vactual(t-1) = traj(t,j);
    }

    for (int k = 0; k < perts_tk.cols(); ++k) {
      MatrixXd newTraj = traj;
      newTraj.col(j) = traj.col(j) + (eps/2)*perts_tk.col(k);
      double plusVal = simulateTraj2(newTraj, false);
      newTraj.col(j) = traj.col(j) - (eps/2)*perts_tk.col(k);
      double minusVal = simulateTraj2(newTraj, false);
      LOG_DEBUG_FMT("joint %i, basis %i, pert vals: %.4e %.4e ", j, k, plusVal-m_exactObjective,minusVal-m_exactObjective);
      dy_jk(j,k) = (plusVal - minusVal)/eps;
      Vector3d y;
      y << plusVal-m_exactObjective, 0, minusVal - m_exactObjective;
      Vector3d abc = Ainv*y;
      GRBLinExpr q;
      int T = traj.rows()-1;
      VectorXd pertVec=perts_tk.block(1,k,T, 1);
      q.addTerms(pertVec.data(),v.data(), T);
      double qactual = pertVec.dot(vactual);
      m_obj += fmax(abc(0),0)*(q-qactual)*(q-qactual) + abc(1)*(q-qactual);
    }
    
//    grad_tj.col(j) = pinvperts_tk * dy_jk.row(j).transpose();
  }
  m_obj += m_exactObjective;

//  cout << "dy_jk:" << endl;
//  cout << dy_jk << endl;
//  cout << "grad_tj:" << endl;
//  cout << grad_tj << endl;

  
//  m_obj.addTerms(grad_tj.data()+7, m_problem->m_trajVars.m_data.data()+7, (traj.rows()-1)*traj.cols());
//  m_obj += m_exactObjective - (grad_tj.middleRows(1, traj.rows()-1).array() * traj.middleRows(1, traj.rows()-1).array()).sum();
  objective += m_obj;
}