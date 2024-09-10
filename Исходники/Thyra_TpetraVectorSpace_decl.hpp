RCP<TpetraVectorSpace<Scalar,LocalOrdinal,GlobalOrdinal,Node> >
tpetraVectorSpace(
  const RCP<const Tpetra::Map<LocalOrdinal,GlobalOrdinal,Node> > &tpetraMap
  )
{
  RCP<TpetraVectorSpace<Scalar,LocalOrdinal,GlobalOrdinal,Node> > vs =
    TpetraVectorSpace<Scalar,LocalOrdinal,GlobalOrdinal,Node>::create();
  vs->initialize(tpetraMap);
  return vs;
}