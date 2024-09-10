Eigen::MatrixXd HmcSampler::rtnorm(const Eigen::MatrixXd& b,
					  const Eigen::MatrixXd& P,
					  const Eigen::MatrixXd& F,
					  const Eigen::VectorXd& g,
					  const Eigen::VectorXd& iv,
					  int samp,
					  int burn,
					  bool kern,
					  int seed)
{
  int d = P.rows();
  LLT<MatrixXd> llt(P);

  MatrixXd UI = llt.matrixU().solve(MatrixXd::Identity(d, d));

  MatrixXd m;
  if (!kern) m = b;
  else m = llt.solve(b);

  MatrixXd Fz = F * UI;
  VectorXd gz = F * m + g;

  // std::cerr << "Fz: " << Fz << "\n";
  // std::cerr << "gz: " << gz.transpose() << "\n";

  if (seed==-1) seed = std::time(NULL);
  HmcSampler hmc(d, seed);

  VectorXd tfm_iv = llt.matrixU() * (iv - m);
  hmc.setInitialValue(tfm_iv);

  for (int j=0; j<F.rows(); j++) 
    hmc.addLinearConstraint(Fz.row(j), gz(j));

  double check = hmc.verifyConstraints(tfm_iv);
  if (check < 0) {
    printf("Problem!  Constraints and initial value do not match!\n");
    printf("Check returned %g.\n", check);
    throw std::runtime_error("HmcSampler::rtnorm: initial value and constraints do not match.");
  }
  // if (check <= 0.1) {
  //   fprintf(stderr, "small check for initial value: %g\n", check);
  // }

  MatrixXd draw(samp, d);
  
  for (int j=0; j<burn; j++) hmc.sampleNext(false);

  for (int j=0; j<samp; j++) {
    MatrixXd temp = hmc.sampleNext(false);
    // std::cerr << "temp: " << temp << "\n";
    // draw.row(j) = UI * temp + m;
    draw.row(j) = temp * UI.transpose() + m.transpose();
    // Be carefule here.  Eigen will try to do some sort of operation even if
    // what you write down does not conform.  Forcing things to a vector seems
    // to be safe.
  }
  
  return draw;
}