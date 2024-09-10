Vec3 Elasticity::evalSol (const Vector& eV, const Vector& N) const
{
  Vec3 u;
  if (eV.size() == N.size()*nsd)
    for (unsigned short int i = 0; i < nsd; i++)
      u[i] = eV.dot(N,i,nsd);

  return u;
}