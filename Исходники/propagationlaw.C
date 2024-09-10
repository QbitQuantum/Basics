void PLCrackPrescribedDir::propagateInterfaces(EnrichmentDomain &ioEnrDom) {
	printf("Entering PLCrackPrescribedDir::propagateInterfaces().\n");

	// Fetch crack tip data
	std::vector<TipInfo> tipInfo;
	ioEnrDom.giveTipInfos(tipInfo);

	int tipIndex = 1;
	FloatArray dir;
	double angleRad = mAngle*M_PI/180.0;
	dir.setValues(2, cos(angleRad), sin(angleRad));
	dir.normalize();


	std::vector<TipPropagation> tipPropagations;
	TipPropagation tipProp;
	tipProp.mTipIndex = tipIndex;
	tipProp.mPropagationDir = dir;
	tipProp.mPropagationLength = mIncrementLength;
	tipPropagations.push_back(tipProp);

	ioEnrDom.propagateTips(tipPropagations);
}