RCP<DefaultFiniteDifferenceModelEvaluator<Scalar> >
defaultFiniteDifferenceModelEvaluator(
  const RCP<ModelEvaluator<Scalar> > &thyraModel,
  const RCP<DirectionalFiniteDiffCalculator<Scalar> > &direcFiniteDiffCalculator
  )
{
  RCP<DefaultFiniteDifferenceModelEvaluator<Scalar> > fdModel =
    defaultFiniteDifferenceModelEvaluator<Scalar>();
  fdModel->initialize(thyraModel, direcFiniteDiffCalculator);
  return fdModel;
}