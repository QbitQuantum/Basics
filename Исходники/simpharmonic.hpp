  std::vector<Real> Exact(Real t, const std::vector<Real>& yinit) const
    {
      using std::sin;
      using std::cos;
      std::vector<Real> yexact(n);

      yexact[q] = yinit[p]/omega*sin(omega*t) + yinit[q]*cos(omega*t);
      yexact[p] = yinit[p]*cos(omega*t) - yinit[q]*omega*sin(omega*t);

      return yexact;
    }