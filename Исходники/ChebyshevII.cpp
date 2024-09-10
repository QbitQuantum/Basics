void AnalogLowPass::design (int numPoles,
                            double stopBandDb)
{
  if (m_numPoles != numPoles ||
      m_stopBandDb != stopBandDb)
  {
    m_numPoles = numPoles;
    m_stopBandDb = stopBandDb;

    reset ();

    const double eps = std::sqrt (1. / (std::exp (stopBandDb * 0.1 * doubleLn10) - 1));
    const double v0 = asinh (1 / eps) / numPoles;
    const double sinh_v0 = -sinh (v0);
    const double cosh_v0 = cosh (v0);
    const double fn = doublePi / (2 * numPoles);

    int k = 1;
    for (int i = numPoles / 2; --i >= 0; k+=2)
    {
      const double a = sinh_v0 * cos ((k - numPoles) * fn);
      const double b = cosh_v0 * sin ((k - numPoles) * fn);
      const double d2 = a * a + b * b;
      const double im = 1 / cos (k * fn);
      addPoleZeroConjugatePairs (complex_t (a / d2, b / d2),
                                       complex_t (0, im));
    }

    if (numPoles & 1)
    {
      add (1 / sinh_v0, infinity());
    }
  }
}