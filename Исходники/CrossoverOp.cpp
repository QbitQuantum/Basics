/*!
 *  \brief Apply the crossover operation on the deme.
 *  \param ioDeme Current deme of individuals to mate.
 *  \param ioContext Context of the evolution.
 */
void CrossoverOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();

	Beagle_ValidateParameterM(mMatingProba->getWrappedValue()>=0.0, mMatingProbaName, "<0");

	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Mating individuals of the ")+
	    uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
	);
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    std::string("Mating individuals with probability ")+
	    dbl2str(mMatingProba->getWrappedValue())
	);

	History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));

	Individual::Handle lOldIndividualHandle = ioContext.getIndividualHandle();
	unsigned int lOldIndividualIndex = ioContext.getIndividualIndex();

	std::vector<unsigned int> lMateVector;
	for(unsigned int i=0; i<ioDeme.size(); i++) {
		if(ioContext.getSystem().getRandomizer().rollUniform() <= mMatingProba->getWrappedValue()) {
			lMateVector.push_back(i);
		}
	}

	std::random_shuffle(lMateVector.begin(), lMateVector.end(),
	                    ioContext.getSystem().getRandomizer());
	if((lMateVector.size() % 2) != 0) lMateVector.pop_back();

	int j = 0;
	int lSize = lMateVector.size();

#if defined(BEAGLE_USE_OMP_NR) || defined(BEAGLE_USE_OMP_R)
	static OpenMP::Handle lOpenMP = castHandleT<OpenMP>(ioContext.getSystem().getComponent("OpenMP"));
	const Factory& lFactory = ioContext.getSystem().getFactory();
	const std::string& lContextName = lFactory.getConceptTypeName("Context");
	Context::Alloc::Handle lContextAlloc = castHandleT<Context::Alloc>(lFactory.getAllocator(lContextName));
	Context::Bag lContexts(lOpenMP->getMaxNumThreads());
	Context::Bag lContexts2(lOpenMP->getMaxNumThreads());
	for(unsigned int i = 0; i < lOpenMP->getMaxNumThreads(); ++i) {
		lContexts[i] = castHandleT<Context>(lContextAlloc->clone(ioContext));
		lContexts2[i] = castHandleT<Context>(lContextAlloc->clone(ioContext));
	}
#if defined(BEAGLE_USE_OMP_NR)
#pragma omp parallel for shared(lSize, lMateVector, lHistory, lContexts, lContexts2) private(j) schedule(dynamic)
#elif defined(BEAGLE_USE_OMP_R)
	const int lChunkSize = std::max((int)(lSize / lOpenMP->getMaxNumThreads()), 1);
#pragma omp parallel for shared(lSize, lMateVector, lHistory, lContexts, lContexts2) private(j) schedule(static, lChunkSize)
#endif
#else
	Context::Alloc::Handle lContextAlloc =
	    castHandleT<Context::Alloc>(ioContext.getSystem().getFactory().getConceptAllocator("Context"));
	Context::Handle lContext2 = castHandleT<Context>(lContextAlloc->clone(ioContext));
#endif
	for(j=0; j<lSize; j+=2) {
		unsigned int lFirstMate  = lMateVector[j];
		unsigned int lSecondMate = lMateVector[j+1];

#if defined(BEAGLE_USE_OMP_NR) || defined(BEAGLE_USE_OMP_R)
		lContexts[lOpenMP->getThreadNum()]->setIndividualIndex(lFirstMate);
		lContexts[lOpenMP->getThreadNum()]->setIndividualHandle(ioDeme[lFirstMate]);
		lContexts2[lOpenMP->getThreadNum()]->setIndividualIndex(lSecondMate);
		lContexts2[lOpenMP->getThreadNum()]->setIndividualHandle(ioDeme[lSecondMate]);
#else
		ioContext.setIndividualIndex(lFirstMate);
		ioContext.setIndividualHandle(ioDeme[lFirstMate]);
		lContext2->setIndividualIndex(lSecondMate);
		lContext2->setIndividualHandle(ioDeme[lSecondMate]);
#endif

		Beagle_LogVerboseM(
		    ioContext.getSystem().getLogger(),
		    std::string("Mating the ")+uint2ordinal(lFirstMate+1)+
		    std::string(" individual with the ")+uint2ordinal(lSecondMate+1)+" individual"
		);

		std::vector<HistoryID> lParents;
		if(lHistory != NULL) {
#pragma omp critical (Beagle_History)
			{
				HistoryID::Handle lHID1 = castHandleT<HistoryID>(ioDeme[lFirstMate]->getMember("HistoryID"));
				if(lHID1 != NULL) lParents.push_back(*lHID1);
				HistoryID::Handle lHID2 = castHandleT<HistoryID>(ioDeme[lSecondMate]->getMember("HistoryID"));
				if(lHID2 != NULL) lParents.push_back(*lHID2);
			}
		}

#if defined(BEAGLE_USE_OMP_NR) || defined(BEAGLE_USE_OMP_R)
		bool lMated = mate(*ioDeme[lFirstMate], *(lContexts[lOpenMP->getThreadNum()]), *ioDeme[lSecondMate], *(lContexts2[lOpenMP->getThreadNum()]));
#else
		bool lMated = mate(*ioDeme[lFirstMate], ioContext, *ioDeme[lSecondMate], *lContext2);
#endif
		if(lMated) {
			if(ioDeme[lFirstMate]->getFitness() != NULL) {
				ioDeme[lFirstMate]->getFitness()->setInvalid();
			}
			if(ioDeme[lSecondMate]->getFitness() != NULL) {
				ioDeme[lSecondMate]->getFitness()->setInvalid();
			}
			if(lHistory != NULL) {
#pragma omp critical (Beagle_History)
				{
					lHistory->incrementHistoryVar(*ioDeme[lFirstMate]);
#if defined(BEAGLE_USE_OMP_R) || defined(BEAGLE_USE_OMP_NR)
					lHistory->trace(*lContexts[lOpenMP->getThreadNum()], lParents, ioDeme[lFirstMate], getName(), "crossover");
#else
					lHistory->trace(ioContext, lParents, ioDeme[lFirstMate], getName(), "crossover");
#endif
					lHistory->incrementHistoryVar(*ioDeme[lSecondMate]);
#if defined(BEAGLE_USE_OMP_R) || defined(BEAGLE_USE_OMP_NR)
					lHistory->trace(*lContexts[lOpenMP->getThreadNum()], lParents, ioDeme[lSecondMate], getName(), "crossover");
#else
					lHistory->trace(ioContext, lParents, ioDeme[lSecondMate], getName(), "crossover");
#endif
				}
			}
		}
	}

	ioContext.setIndividualIndex(lOldIndividualIndex);
	ioContext.setIndividualHandle(lOldIndividualHandle);

	Beagle_StackTraceEndM();
}