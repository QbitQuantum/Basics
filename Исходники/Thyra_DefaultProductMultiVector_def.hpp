Teuchos::RCP<Thyra::DefaultProductMultiVector<Scalar> >
Thyra::defaultProductMultiVector(
    const RCP<const DefaultProductVectorSpace<Scalar> > &productSpace,
    const ArrayView<const RCP<const MultiVectorBase<Scalar> > > &multiVecs
)
{
    const RCP<DefaultProductMultiVector<Scalar> > pmv =
        defaultProductMultiVector<Scalar>();
    pmv->initialize(productSpace, multiVecs);
    return pmv;
}