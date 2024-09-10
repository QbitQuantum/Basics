inline
RCP<DefaultMultiVectorProductVectorSpace<Scalar> >
multiVectorProductVectorSpace(
  const RCP<const VectorSpaceBase<Scalar> > &space,
  const int numColumns
  )
{
  RCP<DefaultMultiVectorProductVectorSpace<Scalar> > multiVecProdVecSpace =
    multiVectorProductVectorSpace<Scalar>();
  multiVecProdVecSpace->initialize(space,numColumns);
  return multiVecProdVecSpace;
}