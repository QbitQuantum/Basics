Vec3 ElasticBeam::displacement (const FiniteElement& fe, const Vector& eV) const
{
  Vec3 d;
  for (size_t k = 0; k < 3; k++)
    d[k] = eV.dot(fe.N,k,npv);

  return d;
}