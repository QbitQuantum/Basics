static void
irt_rpf_nominal_paramInfo(const double *spec, const int param,
			  const char **type, double *upper, double *lower)
{
	int numDims = spec[RPF_ISpecDims];
	const int numOutcomes = spec[RPF_ISpecOutcomes];
	*upper = nan("unset");
	*lower = nan("unset");
	if (numDims == 0) {
		*type = "intercept";
		return;
	}
	*type = NULL;
	if (param >= 0 && param < numDims) {
		*type = "slope";
		*lower = 1e-6;
	} else if (param < numDims + numOutcomes - 1) {
		*type = "slope";
	} else {
		*type = "intercept";
	}
}