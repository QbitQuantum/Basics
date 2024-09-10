RCP<DefaultProductVector<Scalar> >
defaultProductVector(
  const RCP<const DefaultProductVectorSpace<Scalar> > &productSpace,
  const ArrayView<const RCP<const VectorBase<Scalar> > > &vecs
  )
{
  RCP<DefaultProductVector<Scalar> > pv = defaultProductVector<Scalar>();
  pv->initialize(productSpace, vecs);
  return pv;
}