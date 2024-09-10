/*!
 *  \brief Apply NSGA2 multiobjective selection operator as a replacement strategy.
 *  \param ioDeme Deme on which selection operator is applied.
 *  \param ioContext Evolutionary context.
 */
void EMO::NSGA2Op::applyAsReplacementStrategy(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Processing using NSGA2 replacement strategy the ")+
	    uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
	);
	Beagle_LogTraceM(ioContext.getSystem().getLogger(), (*this));

	// Generate a new generation of individuals, merged with the actual one.
	const unsigned int lLambda =
	    (unsigned int)std::ceil(mLMRatio->getWrappedValue()*float(ioDeme.size()));
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    "Generating " << lLambda << " offsprings using breeder tree"
	);
	RouletteT<unsigned int> lRoulette;
	buildRoulette(lRoulette, ioContext);
	Individual::Bag lOffsprings(ioDeme);
	for(unsigned int i=0; i<lLambda; ++i) {
		unsigned int lIndexBreeder = lRoulette.select(ioContext.getSystem().getRandomizer());
		BreederNode::Handle lSelectedBreeder=getRootNode();
		for(unsigned int j=0; j<lIndexBreeder; ++j)
			lSelectedBreeder=lSelectedBreeder->getNextSibling();
		Beagle_NonNullPointerAssertM(lSelectedBreeder);
		Beagle_NonNullPointerAssertM(lSelectedBreeder->getBreederOp());
		Individual::Handle lBredIndiv =
		    lSelectedBreeder->getBreederOp()->breed(ioDeme, lSelectedBreeder->getFirstChild(), ioContext);
		Beagle_NonNullPointerAssertM(lBredIndiv);
		lOffsprings.push_back(lBredIndiv);
	}

	// Fast non-dominated sorting, followed by insertion of the first Pareto fronts.
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    "Applying fast non-dominated sorting on the union of parents and offsprings individual"
	);
	NSGA2Op::Fronts lParetoFronts;
	sortFastND(lParetoFronts, ioDeme.size(), lOffsprings, ioContext);
	unsigned int lIndexDeme=0;
	for(unsigned int j=0; j<(lParetoFronts.size()-1); ++j) {
		for(unsigned int k=0; k<lParetoFronts[j].size(); ++k) {
			ioDeme[lIndexDeme++] = lOffsprings[lParetoFronts[j][k]];
		}
	}

	// Insertion of the last Pareto front, using crowding distance
	Individual::Bag lLastFrontIndiv;
	for(unsigned int l=0; l<lParetoFronts.back().size(); ++l) {
		lLastFrontIndiv.push_back(lOffsprings[lParetoFronts.back()[l]]);
	}
	NSGA2Op::Distances lDistances;
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    "Computing crowding distance on the " << uint2ordinal(lParetoFronts.size()) <<
	    " Pareto front, which is made of " << lParetoFronts.back().size() << " individuals"
	);
	evalCrowdingDistance(lDistances, lLastFrontIndiv);
	for(unsigned int m=0; lIndexDeme<ioDeme.size(); ++m) {
		ioDeme[lIndexDeme++] = lLastFrontIndiv[lDistances[m].second];
	}
	Beagle_StackTraceEndM();
}