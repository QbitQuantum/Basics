RCP<DiagonalScalarProd<Scalar> >
diagonalScalarProd(const RCP<const VectorBase<Scalar> > &s_diag)
{
  const RCP<DiagonalScalarProd<Scalar> > scalarProd =
    Teuchos::rcp(new DiagonalScalarProd<Scalar>());
  scalarProd->initialize(s_diag);
  return scalarProd;
}