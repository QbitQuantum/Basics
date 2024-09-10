// checks if su is SU(3) matrix by tr(x*x^dagger) and sum(x*x^dagger)
static void check_su3(const Eigen::Matrix3cd &su) {
  std::complex<double> test1 = (su * su.adjoint()).trace();
  std::complex<double> test2 = (su * su.adjoint()).sum();

  if (((abs(test1) - 3.) > 10e-11) || ((abs(test2) - 3.) > 10e-11)) {
    std::cout << std::setprecision(13) << " det:  " << su.determinant()
              << "\n tr: " << test1 << "\n sum: " << test2 << "\n"
              << std::endl;
  }
}