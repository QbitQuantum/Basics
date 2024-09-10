  double sigmoidKernel::apply(const vector<double>& a,
                              const vector<double>& b) const {
    double t=a.dot(b);

    return tanh(getParameters().kappa*t + getParameters().theta);
  }