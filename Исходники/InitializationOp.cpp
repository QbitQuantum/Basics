/*!
 *  \brief Apply the initialization operation on the deme.
 *  \param ioDeme Current deme of individuals to initialize.
 *  \param ioContext Context of the evolution.
 */
void InitializationOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();

#ifndef BEAGLE_NDEBUG
	if(ioContext.getVivariumHandle()!=NULL) {
		Beagle_AssertM(mPopSize->size() == ioContext.getVivarium().size());
	}
#endif // BEAGLE_NDEBUG

	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Initializing the ")+
	    uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
	);
	if(!ioDeme.empty()) {
		Beagle_LogBasicM(
		    ioContext.getSystem().getLogger(),
		    std::string("Warning!  Applying '")+getName()+"' will overwrite the "+
		    uint2str(ioDeme.size())+" individual(s) currently in the deme with newly initialized "+
		    "individuals.  If this is not what you desire consider using OversizeOp instead."
		);
	}
	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Resizing the deme from ")+
	    uint2str(ioDeme.size())+" to "+
	    uint2str((*mPopSize)[ioContext.getDemeIndex()])+" individuals"
	);

	const Factory& lFactory = ioContext.getSystem().getFactory();
	Individual::Alloc::Handle lIndividualAlloc =
	    castHandleT<Individual::Alloc>(lFactory.getConceptAllocator("Individual"));
	ioDeme.clear();
	const unsigned int lDemeSize = (*mPopSize)[ioContext.getDemeIndex()];
	for(unsigned int i=0; i<lDemeSize; ++i) {
		ioDeme.push_back(lIndividualAlloc->allocate());
	}

	unsigned int lSeededIndividuals = 0;
	if(mSeedsFile->getWrappedValue().empty() == false) {
		Beagle_LogInfoM(
		    ioContext.getSystem().getLogger(),
		    std::string("Reading seeds file '")+mSeedsFile->getWrappedValue()+
		    std::string("' to initialize the ")+uint2ordinal(ioContext.getDemeIndex()+1)+
		    std::string(" deme")
		);
		lSeededIndividuals = readSeeds(mSeedsFile->getWrappedValue(), ioDeme, ioContext);
		Beagle_LogDetailedM(
		    ioContext.getSystem().getLogger(),
		    uint2str(lSeededIndividuals)+std::string(" individuals read to seed the deme")
		);
	}

	History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));

	Individual::Handle lOldIndividualHandle = ioContext.getIndividualHandle();
	unsigned int lOldIndividualIndex = ioContext.getIndividualIndex();
	for(unsigned int i=lSeededIndividuals; i<ioDeme.size(); ++i) {
		Beagle_LogVerboseM(
		    ioContext.getSystem().getLogger(),
		    std::string("Initializing the ")+uint2ordinal(i+1)+" individual"
		);
		ioContext.setIndividualHandle(ioDeme[i]);
		ioContext.setIndividualIndex(i);
		initIndividual(*ioDeme[i], ioContext);
		if(ioDeme[i]->getFitness() != NULL) {
			ioDeme[i]->getFitness()->setInvalid();
		}
		if(lHistory != NULL) {
			lHistory->incrementHistoryVar(*ioDeme[i]);
			lHistory->trace(ioContext, std::vector<HistoryID>(), ioDeme[i], getName(), "initialization");
		}
	}
	ioContext.setIndividualIndex(lOldIndividualIndex);
	ioContext.setIndividualHandle(lOldIndividualHandle);

	Beagle_StackTraceEndM();
}