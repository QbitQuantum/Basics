/*!
 *  \brief Apply the recombination operation on the deme.
 *  \param ioDeme Current deme of individuals to recombine.
 *  \param ioContext Context of the evolution.
 */
void RecombinationOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	Beagle_ValidateParameterM(mRecombProba->getWrappedValue()>=0.0, mRecombProbaName, "<0");

	Beagle_LogTraceM(
	    ioContext.getSystem().getLogger(),
	    std::string("Recombining individuals of the ")+
	    uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
	);
	Beagle_LogVerboseM(
	    ioContext.getSystem().getLogger(),
	    std::string("Recombining individuals with probability ")+
	    dbl2str(mRecombProba->getWrappedValue())
	);

	History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));
	Individual::Bag lRecombinedIndiv(ioDeme.size());
	for(unsigned int i=0; i<lRecombinedIndiv.size(); ++i) {
		if(ioContext.getSystem().getRandomizer().rollUniform() <= mRecombProba->getWrappedValue()) {
			Individual::Bag::Handle lParents = new Individual::Bag;
			const unsigned int lNbGenerated =
			    (mNumberRecomb->getWrappedValue()==0) ? ioDeme.size() :
			    minOf<unsigned int>(ioDeme.size(), mNumberRecomb->getWrappedValue());
			if(lNbGenerated == ioDeme.size()) (*lParents) = ioDeme;
			else {
				std::vector<unsigned int> lIndices(ioDeme.size());
				for(unsigned int j=0; j<lIndices.size(); ++j) lIndices[j] = j;
				std::random_shuffle(lIndices.begin(), lIndices.end(),
				                    ioContext.getSystem().getRandomizer());
				for(unsigned int j=0; j<lNbGenerated; ++j) {
					lParents->push_back(ioDeme[lIndices[j]]);
				}
			}
			lRecombinedIndiv[i] = recombine(*lParents, ioContext);
			if(lRecombinedIndiv[i]->getFitness() != NULL) {
				lRecombinedIndiv[i]->getFitness()->setInvalid();
			}
			// Log and update history.
			Beagle_LogVerboseM(
			    ioContext.getSystem().getLogger(),
			    std::string("The ")+uint2ordinal(i+1)+
			    std::string(" individual as been replaced by recombination")
			);
			if(lHistory != NULL) {
				std::vector<HistoryID> lParentNames;
				for(unsigned int j=0; j<lParents->size(); ++j) {
					HistoryID::Handle lHID = castHandleT<HistoryID>(lParents->at(j)->getMember("HistoryID"));
					if(lHID != NULL) lParentNames.push_back(*lHID);
				}
				lHistory->incrementHistoryVar(*lRecombinedIndiv[i]);
				lHistory->trace(ioContext, lParentNames, lRecombinedIndiv[i], getName(), "recombination");
			}
		}
	}
	for(unsigned int i=0; i<ioDeme.size(); ++i) {
		if(lRecombinedIndiv[i] != NULL) ioDeme[i] = lRecombinedIndiv[i];
	}

	Beagle_StackTraceEndM();
}