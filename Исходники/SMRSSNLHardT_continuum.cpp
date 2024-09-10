/* computes the hydrostatic (mean) stress */
double SMRSSNLHardT::MeanStress(const dSymMatrixT& trialstrain,
	const ElementCardT& element)
{
#pragma unused(element)

  fMeanStress = fkappa*trialstrain.Trace();
  return fMeanStress;
}