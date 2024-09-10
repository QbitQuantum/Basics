double VarRTM::PredictAUC(RTMC &m, Mat &z_bar) {
  VReal real,pre;
  for (int d = 0; d < held_out_net_.cols(); d++) {
    for (SpMatInIt it(held_out_net_, d); it; ++it) {
      double label = it.value();
      Vec pi = z_bar.col(d).cwiseProduct(z_bar.col(it.index()));
      double prob = Sigmoid(pi.dot(m.eta));
      real.push_back(label);
      pre.push_back(prob);
    }
  }
  return AUC(real,pre);
}