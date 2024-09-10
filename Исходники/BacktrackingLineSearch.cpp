double BacktrackingLineSearch::step_size(std::function<double (const VectorXd&)> f,
                                         const VectorXd &dfx,
                                         const VectorXd &x,
                                         const VectorXd &direction) const {
  auto m = direction.dot(dfx);
  auto t = -_c * m;
  auto fx = f(x);
  auto step = _alpha;
  for (unsigned int i = 0; i < _niter; i++) {
    VectorXd new_x = x + direction*step;
    if ((fx - f(new_x)) > step * t) {
      break;
    }
      step = step * _tau;
  }
  return step;
}