const RCP<NonlinearCG<Scalar> >
nonlinearCG(
  const RCP<const Thyra::ModelEvaluator<Scalar> > &model,
  const int paramIndex,
  const int responseIndex,
  const RCP<GlobiPack::LineSearchBase<Scalar> > &linesearch
  )
{
  const RCP<NonlinearCG<Scalar> > solver = 
    Teuchos::rcp(new NonlinearCG<Scalar>);
  solver->initialize(model, paramIndex, responseIndex, linesearch);
  return solver;
}