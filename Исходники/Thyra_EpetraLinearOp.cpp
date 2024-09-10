Teuchos::RCP<const Thyra::EpetraLinearOp>
Thyra::epetraLinearOp(
  const RCP<const Epetra_Operator> &op,
  const std::string &label,
  EOpTransp opTrans,
  EApplyEpetraOpAs applyAs,
  EAdjointEpetraOp adjointSupport,
  const RCP< const SpmdVectorSpaceBase<double> > &range,
  const RCP< const SpmdVectorSpaceBase<double> > &domain
  )
{
  RCP<EpetraLinearOp> thyraEpetraOp = Teuchos::rcp(new EpetraLinearOp());
  thyraEpetraOp->initialize(
    Teuchos::rcp_const_cast<Epetra_Operator>(op), // Safe cast due to return type!
    opTrans, applyAs, adjointSupport, range, domain
    );
  thyraEpetraOp->setObjectLabel(label);
  return thyraEpetraOp;
}