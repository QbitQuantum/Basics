/*!
 *  \brief Apply the oversize replacement strategy operation on a deme.
 *  \param ioDeme Reference to the deme on which the operation takes place.
 *  \param ioContext Evolutionary context of the operation.
 */
void OversizeOp::operate(Deme& ioDeme, Context& ioContext)
{
	Beagle_StackTraceBeginM();
	Beagle_NonNullPointerAssertM(getRootNode());
	Beagle_ValidateParameterM
	(mOversizeRatio->getWrappedValue() >= 1.0
	 || mOversizeRatio->getWrappedValue() == -1.0,
	 mOversizeRatioName,
	 "The oversize ratio must be greater than or equal to 1.0, or equal to -1.0.");
	
	Beagle_LogTraceM(
					 ioContext.getSystem().getLogger(),
					 "replacement-strategy", "Beagle::OversizeOp",
					 string("Using oversize replacement strategy to process the ")+
					 uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
					 );
	Beagle_LogObjectM(
					  ioContext.getSystem().getLogger(),
					  Logger::eTrace,
					  "replacement-strategy", "Beagle::OversizeOp",
					  (*this)
					  );
	
	RouletteT<unsigned int> lRoulette;
	buildRoulette(lRoulette, ioContext);
	
	// Calculate the increase in size (lambda)
	float lRatio = mOversizeRatio->getWrappedValue();
	unsigned int lLambda;
	if (lRatio == -1.0) {
		// Using special ratio of -1.0 ensures deme grows to size specified in 'ec.pop.size'
		if (!ioContext.getSystem().getRegister().isRegistered("ec.pop.size")) {
			throw Beagle_RunTimeExceptionM(getName()+" requires register variable 'ec.pop.size'");
		}
		UIntArray::Handle lPopSize = castHandleT<UIntArray>
		(ioContext.getSystem().getRegister().getEntry("ec.pop.size"));
		unsigned int lSpecifiedDemeSize = (*lPopSize)[ioContext.getDemeIndex()];
		unsigned int lCurrentDemeSize = ioDeme.size();
		if (lSpecifiedDemeSize < lCurrentDemeSize) {
			throw Beagle_RunTimeExceptionM
			(std::string("For the ")+uint2ordinal(ioContext.getDemeIndex()+1)+
			 " deme, the size specified in 'ec.pop.size' ("+uint2str(lSpecifiedDemeSize)+
			 ") is less than the current deme size ("+uint2str(lCurrentDemeSize)+
			 ").  "+getName()+" can only increase the size of the deme.  Consider using DecimateOp "+
			 "if you wish to decrease the size of the deme");
		}
		lLambda = lSpecifiedDemeSize - lCurrentDemeSize;
	} else {
		// Using ratio to scale the deme's population
		lLambda = (unsigned int)ceil((lRatio-1.0)*float(ioDeme.size()));
	}
	Beagle_LogTraceM(
					 ioContext.getSystem().getLogger(),
					 "replacement-strategy", "Beagle::OversizeOp",
					 string("Population will be increased in size by ")+uint2str(lLambda)+" individuals"
					 );
	
	// Create the new individuals.
	Individual::Bag lOffsprings;
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
	
	// Add the new individuals into the deme.
	ioDeme.insert(ioDeme.end(), lOffsprings.begin(), lOffsprings.end());
	Beagle_LogDetailedM(
						ioContext.getSystem().getLogger(),
						"replacement-strategy", "Beagle::OversizeOp",
						string("There are now ")+uint2str(ioDeme.size())+" individuals in the "+
						uint2ordinal(ioContext.getDemeIndex()+1)+" deme"
						);
	Beagle_StackTraceEndM("void OversizeOp::operate(Deme& ioDeme, Context& ioContext)");
}