/*!
 *  \brief Generate children from the breeder tree.
 *  \param ioDeme Deme to generate children from.
 *  \param ioContext Evolutionary context.
 *  \param lNbChildren Number of children to generate.
 *  \param inN Dimensionality of the problem.
 *  \param ioCMAValues CMA values to use to generate new individual.
 *  \param inSelectionWeights Selection weights used to generate children.
 */
void CMA::MuWCommaLambdaCMAFltVecOp::generateChildren(Deme& ioDeme,
        Context& ioContext,
        unsigned int inNbChildren,
        unsigned int inN,
        CMAValues& ioCMAValues,
        const Vector& inSelectionWeights) const
{
	Beagle_StackTraceBeginM();
	// Check parameters and log some information
	Beagle_NonNullPointerAssertM(mElitismKeepSize);
	Beagle_ValidateParameterM(mLMRatio->getWrappedValue() >= 1.0,
	                          mLMRatioName,
	                          "The LM ratio must be higher or equal to 1.0.");
	Beagle_ValidateParameterM(mElitismKeepSize->getWrappedValue() <= ioDeme.size(),
	                          "ec.elite.keepsize",
	                          "The elistism keepsize must be less than the deme size!");

	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Using CMA-ES (mu_w,lambda) replacement strategy to process the ")+
	    uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
	);
	Beagle_LogTraceM(ioContext.getSystem().getLogger(), (*this));
	const Factory& lFactory = ioContext.getSystem().getFactory();

	// Create weighted mean individual.
	std::sort(ioDeme.begin(), ioDeme.end(), IsMorePointerPredicate());

	Individual::Alloc::Handle lIndividualAlloc =
		castHandleT<Individual::Alloc>(lFactory.getConceptAllocator("Individual"));
	Individual::Handle lMeanInd = castHandleT<Individual>(lIndividualAlloc->allocate());
	Genotype::Alloc::Handle lGenotypeAlloc =
		castHandleT<Genotype::Alloc>(lFactory.getConceptAllocator("Genotype"));
	FltVec::FloatVector::Handle lMeanFloatVec =
		castHandleT<FltVec::FloatVector>(lGenotypeAlloc->allocate());
	lMeanFloatVec->resize(inN);
	lMeanInd->push_back(lMeanFloatVec);
	
	for(unsigned int i=0; i<inN; ++i) (*lMeanFloatVec)[i] = 0.0;
	if(ioDeme.size()==1) {
		Beagle_AssertM(ioDeme[0]->size() == 1);
		FltVec::FloatVector::Handle lInd = castHandleT<FltVec::FloatVector>((*ioDeme[0])[0]);
		(*lMeanFloatVec) = *lInd;
	} else {
		for(unsigned int i=0; i<ioDeme.size(); ++i) {
			Beagle_AssertM(ioDeme[i]->size()==1);
			FltVec::FloatVector::Handle lVecI = castHandleT<FltVec::FloatVector>((*ioDeme[i])[0]);
			Beagle_AssertM(lVecI->size()==inN);
			for(unsigned int j=0; j<inN; ++j) (*lMeanFloatVec)[j] += (inSelectionWeights[i] * (*lVecI)[j]);
		}
	}
	ioCMAValues.mXmean.resize(inN);
	for(unsigned int i=0; i<inN; ++i) ioCMAValues.mXmean[i] = (*lMeanFloatVec)[i];

	// Generate lambda children with breeder tree, first build breeder roulette
	RouletteT<unsigned int> lRoulette;
	buildRoulette(lRoulette, ioContext);

	// Keep best individuals if elitism is used
	const unsigned int lElitismKS=mElitismKeepSize->getWrappedValue();
	if(lElitismKS > 0) {
		Individual::Bag lBestInd;
		History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));
		std::make_heap(ioDeme.begin(), ioDeme.end(), IsLessPointerPredicate());
		for(unsigned int i=0; i<lElitismKS; ++i) {
			if(lHistory != NULL) {
				HistoryID::Handle lHID = castHandleT<HistoryID>(ioDeme[0]->getMember("HistoryID"));
				std::vector<HistoryID> lParent;
				if(lHID != NULL) lParent.push_back(*lHID);
				lHistory->allocateNewID(*ioDeme[0]);
				lHistory->trace(ioContext, lParent, ioDeme[0], getName(), "elitism");
			}
			lBestInd.push_back(ioDeme[0]);
			std::pop_heap(ioDeme.begin(), ioDeme.end(), IsLessPointerPredicate());
			ioDeme.pop_back();
		}
		ioDeme.clear();
		ioDeme.insert(ioDeme.end(), lBestInd.begin(), lBestInd.end());
	} else ioDeme.clear();

	// Generate the children
	Individual::Bag lBagWithMeanInd;
	lBagWithMeanInd.push_back(lMeanInd);
	for(unsigned int i=0; i<inNbChildren; ++i) {
		unsigned int lIndexBreeder = lRoulette.select(ioContext.getSystem().getRandomizer());
		BreederNode::Handle lSelectedBreeder=getRootNode();
		for(unsigned int j=0; j<lIndexBreeder; ++j)
			lSelectedBreeder=lSelectedBreeder->getNextSibling();
		Beagle_NonNullPointerAssertM(lSelectedBreeder);
		Beagle_NonNullPointerAssertM(lSelectedBreeder->getBreederOp());
		Individual::Handle lBredIndiv =
		    lSelectedBreeder->getBreederOp()->breed(lBagWithMeanInd,
		                                            lSelectedBreeder->getFirstChild(),
		                                            ioContext);
		Beagle_NonNullPointerAssertM(lBredIndiv);
		ioDeme.push_back(lBredIndiv);
	}

	Beagle_StackTraceEndM();
}