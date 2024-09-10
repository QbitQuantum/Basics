RCP<DelayedLinearOpWithSolve<Scalar> >
delayedLinearOpWithSolve(
  const RCP<const LinearOpSourceBase<Scalar> > &fwdOpSrc,
  const RCP<LinearOpWithSolveFactoryBase<Scalar> > &lowsf
  )
{
  using Teuchos::null;
  const RCP<DelayedLinearOpWithSolve<Scalar> > dlows =
    delayedLinearOpWithSolve<Scalar>();
  dlows->initialize(fwdOpSrc, null, null, SUPPORT_SOLVE_UNSPECIFIED, lowsf);
  return dlows;
}