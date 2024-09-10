// [[Rcpp::export()]]
VectorXd sample_delta_c_Eigen(
    VectorXd delta,
    VectorXd tauh,
    Map<MatrixXd> Lambda_prec,
    double delta_1_shape,
    double delta_1_rate,
    double delta_2_shape,
    double delta_2_rate,
    Map<MatrixXd> randg_draws,  // all done with rate = 1;
    Map<MatrixXd> Lambda2
) {
  int times = randg_draws.rows();
  int k = tauh.size();

  MatrixXd scores_mat = Lambda_prec.cwiseProduct(Lambda2);
  VectorXd scores = scores_mat.colwise().sum();

  double rate,delta_old;
  for(int i = 0; i < times; i++){
    delta_old = delta(0);
    rate = delta_1_rate + 0.5 * (1/delta(0)) * tauh.dot(scores);
    delta(0) = randg_draws(i,0) / rate;
    // tauh = cumprod(delta);
    tauh *= delta(0)/delta_old;   // replaces re-calculating cumprod

    for(int h = 1; h < k-1; h++) {
      delta_old = delta(h);
      rate = delta_2_rate + 0.5*(1/delta(h))*tauh.tail(k-h).dot(scores.tail(k-h));
      delta(h) = randg_draws(i,h) / rate;
      // tauh = cumprod(delta);
      tauh.tail(k-h) *= delta(h)/delta_old; // replaces re-calculating cumprod
      // Rcout << (tauh - cumprod(delta)).sum() << std::endl;
    }
  }
  return(delta);
}