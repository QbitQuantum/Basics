  void operator() ( const Particle & p,
                    const double & time,
                    const double & dt,
                          Vector<double,6u> & F ) {
    ++num_calls;
    /* copy over the dx/dt, dy/dt, and dz/dt */
    F[X] = p[VX];
    F[Y] = p[VY];
    F[Z] = p[VZ];

    /* and accelerations for a simple harmonic oscillator (kind of simple) */
    F[VX] = - k_m[X]*p[X] - a[X]*k_m[X] * sin( omega_prime[X] * time );
    F[VY] = - k_m[Y]*p[Y] - a[Y]*k_m[Y] * sin( omega_prime[Y] * time );
    F[VZ] = - k_m[Z]*p[Z] - a[Z]*k_m[Z] * sin( omega_prime[Z] * time );
  }