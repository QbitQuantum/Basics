void LagrangeConstraints::getCoefficients(FieldContainer<double> &lhs, FieldContainer<double> &rhs,
    int elemConstraintIndex, DofOrderingPtr trialOrdering,
    BasisCachePtr basisCache)
{
  LinearTermPtr lt = _constraints[elemConstraintIndex].linearTerm();
  TFunctionPtr<double> f = _constraints[elemConstraintIndex].f();
  lt->integrate(lhs, trialOrdering, basisCache);
  bool onBoundary = f->boundaryValueOnly();
  if ( !onBoundary )
  {
    f->integrate(rhs, basisCache);
  }
  else
  {
    int numSides = basisCache->cellTopology()->getSideCount();
    rhs.initialize(0);
    for (int sideIndex=0; sideIndex<numSides; sideIndex++)
    {
      f->integrate(rhs, basisCache->getSideBasisCache(sideIndex), true); // true: sumInto
    }
  }
}