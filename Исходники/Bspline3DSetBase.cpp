void Bspline3DSetBase::setLattice(const CrystalLattice<RealType,DIM>& lat)
{
  Lattice.set(lat);
  UnitLattice.set(lat);
  GGt=dot(Lattice.G,transpose(Lattice.G));
}