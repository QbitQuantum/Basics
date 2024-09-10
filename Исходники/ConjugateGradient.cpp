bool ConjugateGradientType::improve_energy(bool verbose) {
  iter++;
  //printf("I am running ConjugateGradient::improve_energy\n");
  const double E0 = energy();
  if (E0 != E0) {
    // There is no point continuing, since we're starting with a NaN!
    // So we may as well quit here.
    if (verbose) {
      printf("The initial energy is a NaN, so I'm quitting early from ConjugateGradientType::improve_energy.\n");
      f.print_summary("has nan:", E0);
      fflush(stdout);
    }
    return false;
  }
  double gdotd;
  {
    const VectorXd g = -grad();
    // Let's immediately free the cached gradient stored internally!
    invalidate_cache();

    // Note: my notation vaguely follows that of
    // [wikipedia](http://en.wikipedia.org/wiki/Nonlinear_conjugate_gradient_method).
    // I use the Polak-Ribiere method, with automatic direction reset.
    // Note that we could save some memory by using Fletcher-Reeves, and
    // it seems worth implementing that as an option for
    // memory-constrained problems (then we wouldn't need to store oldgrad).
    double beta = g.dot(g - oldgrad)/oldgradsqr;
    oldgrad = g;
    if (beta < 0 || beta != beta || oldgradsqr == 0) beta = 0;
    oldgradsqr = oldgrad.dot(oldgrad);
    direction = g + beta*direction;
    gdotd = oldgrad.dot(direction);
    if (gdotd < 0) {
      direction = oldgrad; // If our direction is uphill, reset to gradient.
      if (verbose) printf("reset to gradient...\n");
      gdotd = oldgrad.dot(direction);
    }
  }

  Minimizer lm = linmin(f, gd, kT, x, direction, -gdotd, &step);
  for (int i=0; i<100 && lm.improve_energy(verbose); i++) {
    if (verbose) lm.print_info("\t");
  }
  if (verbose) {
    //lm->print_info();
    print_info();
    printf("grad*dir/oldgrad*dir = %g\n", grad().dot(direction)/gdotd);
  }
  return (energy() < E0);
}