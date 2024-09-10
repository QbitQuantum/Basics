/*!
 *  \brief Apply the evaluation process on the invalid individuals of the deme.
 *  \param ioDeme Deme to process.
 *  \param ioContext Context of the evolution.
 */
void EvaluationMultipleOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    "Evaluating the fitness of the individuals in the " << 
	    uint2ordinal(ioContext.getDemeIndex()+1) << " deme"
	);

	Beagle_AssertM( ioDeme.size()!=0 );

	// Prepare stats
	prepareStats(ioDeme,ioContext);

	// Generate a vector of indicies into the population
	std::vector<unsigned int> lEvalVector;
	for(unsigned int i=0; i<ioDeme.size(); i++) {
		if((ioDeme[i]->getFitness() == NULL) ||
		        (ioDeme[i]->getFitness()->isValid() == false)) {
			lEvalVector.push_back(i);
			Beagle_LogDebugM(
			    ioContext.getSystem().getLogger(),
			    "Added " << uint2ordinal(i+1) << " individual for evaluation."
			);
		}
	}
	std::random_shuffle(lEvalVector.begin(), lEvalVector.end(),
	                    ioContext.getSystem().getRandomizer());

	Beagle_LogDebugM(
	    ioContext.getSystem().getLogger(),
	    "There are " << lEvalVector.size() << " individuals to be evaluated."
	);

	History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));

	while ( !lEvalVector.empty() ) {
		// Put individuals and context into bags.
		Individual::Bag lIndividuals;
		Context::Bag lContexts;
		lIndividuals.resize( mIndisPerGroup );
		lContexts.resize( mIndisPerGroup );
		unsigned int lIndiCounter =0;

		for (unsigned int i=0; i<mIndisPerGroup; i++) {
			// Set individual
			lIndividuals[i] = ioDeme[lEvalVector.back()];
			lIndiCounter++;
			// Set context
			Context::Alloc::Handle lContextAlloc =
			    castHandleT<Context::Alloc>(ioContext.getSystem().getFactory().getConceptAllocator("Context"));
			Context::Handle lContext = castHandleT<Context>(lContextAlloc->clone(ioContext));
			lContext->setIndividualIndex( lEvalVector.back() );
			lContext->setIndividualHandle( ioDeme[lEvalVector.back()] );
			lContexts[i] = lContext;
			// Remove this index from the evaluation vector
			lEvalVector.pop_back();
			if(lEvalVector.empty()) {
				lIndividuals.resize( lIndiCounter );
				lContexts.resize( lIndiCounter );
				break;
			}
		}

		// Evaluate individuals
		std::ostringstream lOSS;
		lOSS << "Evaluating the fitness of the ";
		for(unsigned int i=0; i<lIndiCounter; i++) {
			// Add to message
			if (i==lIndiCounter-1) lOSS << " and ";
			lOSS << uint2ordinal(lContexts[i]->getIndividualIndex()+1);
			if (i<lIndiCounter-2) lOSS << ", ";
		}
		lOSS << " individuals";
		Beagle_LogVerboseM(
		    ioContext.getSystem().getLogger(),
		    lOSS.str()
		);
		Fitness::Bag::Handle lFitnessBag = evaluateIndividuals(lIndividuals, lContexts);

		// Assign fitnesses
		for (unsigned int i=0; i<lIndiCounter; i++) {
			Beagle_LogDebugM(
			    ioContext.getSystem().getLogger(),
			    "Considering fitness of the " << uint2ordinal(lContexts[i]->getIndividualIndex()+1) << " individual"
			);
			Beagle_AssertM( i < lFitnessBag->size() );
			Fitness::Handle lFitness = lFitnessBag->at(i);
			Beagle_NonNullPointerAssertM( lFitness );
			lIndividuals[i]->setFitness( lFitness );
			lIndividuals[i]->getFitness()->setValid();
			if(lHistory != NULL) {
				lHistory->allocateID(*lIndividuals[i]);
				lHistory->trace(ioContext, std::vector<HistoryID>(), lIndividuals[i], getName(), "evaluation");
			}

			Beagle_LogVerboseM(
			    ioContext.getSystem().getLogger(),
			    *lIndividuals[i]->getFitness()
			);
		}

		// Update stats
		updateStats(lIndividuals.size(),ioContext);
	}

	updateHallOfFameWithDeme(ioDeme,ioContext);
	Beagle_StackTraceEndM();
}