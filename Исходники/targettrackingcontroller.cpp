Eigen::VectorXd TargetTrackingController::getControl(const EKF *ekf, const MultiAgentMotionModel *motionModel, const std::vector<const SensorModel*> &sensorModel, double *f) const {
  Evaluator evaluator(ekf, motionModel, sensorModel, params);

  Eigen::VectorXd p = Eigen::VectorXd::Zero(motionModel->getControlDim());
  Eigen::VectorXd lowerBound = Eigen::VectorXd::Constant(motionModel->getControlDim(), params("multi_rotor_control/controlMin").toDouble());
  Eigen::VectorXd upperBound = Eigen::VectorXd::Constant(motionModel->getControlDim(), params("multi_rotor_control/controlMax").toDouble());

  nlopt_opt opt = nlopt_create(NLOPT_LN_COBYLA, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LN_BOBYQA, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LN_NEWUOA_BOUND, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LN_PRAXIS, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LN_NELDERMEAD, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LN_SBPLX, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_GN_ORIG_DIRECT, p.size()); // failed
//  nlopt_opt opt = nlopt_create(NLOPT_GN_ORIG_DIRECT_L, p.size()); // very good: p    0.0118546 -6.27225e-05  6.27225e-05 -2.09075e-05  2.09075e-05 -8.51788e-06 -2.09075e-05           10
//  nlopt_opt opt = nlopt_create(NLOPT_GN_ISRES, p.size()); // rather bad
//  nlopt_opt opt = nlopt_create(NLOPT_GN_CRS2_LM, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LD_MMA, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LD_CCSAQ, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LD_SLSQP, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LD_LBFGS, p.size());
//  nlopt_opt opt = nlopt_create(NLOPT_LD_TNEWTON_PRECOND, p.size()); // bad
//  nlopt_opt opt = nlopt_create(NLOPT_LD_TNEWTON_PRECOND_RESTART, p.size()); // bad
//  nlopt_opt opt = nlopt_create(NLOPT_LD_VAR2, p.size());

  nlopt_set_min_objective(opt, f_evaluate, &evaluator);
  nlopt_set_lower_bounds(opt, lowerBound.data());
  nlopt_set_upper_bounds(opt, upperBound.data());
  nlopt_set_ftol_abs(opt, 1E-6);
  nlopt_set_xtol_rel(opt, 1E-3);
  nlopt_set_maxeval(opt, 1E8);
  nlopt_set_maxtime(opt, 7200);
  double pa[p.size()];
  memcpy(pa, p.data(), p.size()*sizeof(double));
  double cost = 0;
//  std::string tmp; std::cerr << "Press enter to start optimization\n"; std::getline(std::cin, tmp);
  nlopt_result ret = nlopt_optimize(opt, pa, &cost);
  Eigen::VectorXd p_res = Eigen::Map<Eigen::VectorXd>(pa, p.size());
  if (f)
    *f = cost;

  std::cerr << "\nInitial guess:\n";
  std::cerr << "  p " << p.transpose() << "\n";
  std::cerr << "  value " << evaluator.evaluate(p) << "\n";

  std::cerr << "Optimization result (return code " << ret << "):\n";
  std::cerr << "  p " << p_res.transpose() << "\n";
  std::cerr << "  value " << evaluator.evaluate(p_res) << "\n";
  nlopt_destroy(opt);
  return p_res;
}