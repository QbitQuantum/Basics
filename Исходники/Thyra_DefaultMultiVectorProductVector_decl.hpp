inline
RCP<const DefaultMultiVectorProductVector<Scalar> >
multiVectorProductVector(
  const RCP<const DefaultMultiVectorProductVectorSpace<Scalar> > &productSpace,
  const RCP<const MultiVectorBase<Scalar> > &multiVec
  )
{
  RCP<DefaultMultiVectorProductVector<Scalar> > multiVecProdVec
    = Teuchos::rcp(new DefaultMultiVectorProductVector<Scalar>());
  multiVecProdVec->initialize(productSpace,multiVec);
  return multiVecProdVec;
}