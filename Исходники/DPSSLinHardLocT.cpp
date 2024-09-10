/* computes the hydrostatic (mean) stress */
double DPSSLinHardLocT::MeanStress(const dSymMatrixT& trialstrain,
	const ElementCardT& element)
{
	#pragma unused(element)

	fMeanStress = fK*trialstrain.Trace();
	return fMeanStress;
}