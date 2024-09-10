double harness(const std::vector<double>& input, size_t N, Fn func) {
  std::vector<double> output(N);
  Timer timer;
  timer.start();
  func(input.begin(), input.end(), N, output.begin());
  timer.stop();
  return timer.time();
}