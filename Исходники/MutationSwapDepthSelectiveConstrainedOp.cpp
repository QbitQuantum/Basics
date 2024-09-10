/*!
 *  \brief Swap mutate a constrained GP individual.
 *  \param ioIndividual GP individual to swap mutate.
 *  \param ioContext Context of the evolution.
 *  \return True if the individual is effectively mutated, false if not.
 */
bool GP::MutationSwapDepthSelectiveConstrainedOp::mutate(Beagle::Individual& ioIndividual, Beagle::Context& ioContext)
{
	Beagle_StackTraceBeginM();
	GP::Individual& lIndividual  = castObjectT<GP::Individual&>(ioIndividual);
	GP::Context& lContext        = castObjectT<GP::Context&>(ioContext);
	double lDistrProba           = mDistributionProba->getWrappedValue();
	unsigned int lNumberAttempts = mNumberAttempts->getWrappedValue();
	bool lMutationDone           = false;
	
	//Select node to mutate
	unsigned int lChoosenTree = 0;
	unsigned int lChoosenNode = 0;
	
	bool lDoParameterSearch = (lContext.getSystem().getRandomizer().rollUniform(0.0, 1.0) <= mMutParameterPb->getWrappedValue());
	
	RouletteT< std::pair<unsigned int,unsigned int> > lRoulette;
	//Select primitive based on type
	for(unsigned int lTry = 0; lTry < 2; ++lTry) { //Do only twice
		std::vector<const std::type_info*> lDesiredTypes(1, ArgEph);
		DepthDependentSelectionOp::buildRoulette(lRoulette, lDesiredTypes, lIndividual, lContext,!lDoParameterSearch,lDoParameterSearch);
		
		if(lRoulette.size() == 0) {
			if(lDoParameterSearch) {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
								   string("No EphemeralDouble node found.")
								   );
			}
			else {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
								   string("No non EphemeralDouble node found.")
								   );
			}
			lDoParameterSearch = !lDoParameterSearch;
			if(lTry >= 1) {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
								   "Unable to GP standard mutate the individual"
								   );
				return false;
			}
		}
		else { 
			std::pair<unsigned int,unsigned int> lSelectedNode = lRoulette.select(ioContext.getSystem().getRandomizer());
			lChoosenTree = lSelectedNode.first;
			lChoosenNode = lSelectedNode.second;
			break;
		}
	}
	
	if(lDoParameterSearch) {
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
						   string("Mutation applied only on EphemeralDouble node.")
						   );
	}
	else {
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
						   string("Mutation applied on node that are not EphemeralDouble.")
						   );
	}
	
	GP::Tree& lTree = *lIndividual[lChoosenTree];
	if(lTree.size() == 0) return false;
	
	GP::Tree::Handle lOldTreeHandle = lContext.getGenotypeHandle();
	unsigned int lOldTreeIndex = lContext.getGenotypeIndex();
	lContext.setGenotypeHandle(lIndividual[lChoosenTree]);
	lContext.setGenotypeIndex(lChoosenTree);
	
	Beagle_LogDebugM(
					 ioContext.getSystem().getLogger(),
					 "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
					 std::string("Individual before constrained GP tree swap mutation: ")+ioIndividual.serialize()
					 );
	
	if(lTree.size() > 1) {
		bool lTypeNode = (lContext.getSystem().getRandomizer().rollUniform(0., 1.) < lDistrProba);
		//Clean the roulette to include only the choosen tree
		for(std::vector< std::pair<double, std::pair<unsigned int,unsigned int> > >::iterator lRouletteIter = lRoulette.begin(); lRouletteIter!=lRoulette.end();){
			if(lRouletteIter->second.first != lChoosenTree || (lTree[lRouletteIter->second.second].mPrimitive->getNumberArguments() != 0) != lTypeNode ) {
				lRouletteIter = lRoulette.erase(lRouletteIter++);
			} else {
				++lRouletteIter;
			}
		}
		if(lRoulette.size() > 0) 
			lChoosenNode = lRoulette.select(ioContext.getSystem().getRandomizer()).second;
	}
	
	if( !lDoParameterSearch || lRoulette.size() > 0 ) {
	
		Primitive::Handle lOriginalPrimitive = lTree[lChoosenNode].mPrimitive;
		
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
						   std::string("Trying to constrained GP tree swap mutate the ")+uint2ordinal(lChoosenNode+1)+
						   std::string(" node (primitive: \"")+lOriginalPrimitive->getName()+
						   std::string("\" nb args: ")+uint2str(lOriginalPrimitive->getNumberArguments())+
						   std::string(") of the ")+uint2ordinal(lChoosenTree+1)+std::string(" tree")
						   );
		
		GP::PrimitiveSet& lPrimitiveSet = lTree.getPrimitiveSet(lContext);
		unsigned int lNbArgsPrimit = lTree[lChoosenNode].mPrimitive->getNumberArguments();
		lTree.setContextToNode(lChoosenNode, lContext);
		for(unsigned int lAttempt=0; lAttempt < lNumberAttempts; ++lAttempt) {
			Primitive::Handle lChoosenPrimitive = lPrimitiveSet.select(lNbArgsPrimit, lContext);
			if(lChoosenPrimitive==NULL) break;
			
			lTree[lChoosenNode].mPrimitive = lChoosenPrimitive->giveReference(lNbArgsPrimit, lContext);
			
			Beagle_LogVerboseM(
							   ioContext.getSystem().getLogger(),
							   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
							   std::string("Trying the primitive \"")+lChoosenPrimitive->getName()+
							   std::string("\"")
							   );
			
			if(lTree.validateSubTree(lChoosenNode, lContext)) {
				lMutationDone = true;
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
								   "Constrained GP tree swap mutation valid"
								   );
				break;
			}
			else {
				lTree[lChoosenNode].mPrimitive = lOriginalPrimitive;
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
								   "Constrained GP tree swap mutation invalid"
								   );
			}
		}
	}
	
	lContext.setGenotypeHandle(lOldTreeHandle);
	lContext.setGenotypeIndex(lOldTreeIndex);
	
	if(lMutationDone) {
		if( !lDoParameterSearch ) {
			//Set structure id invalid
			castHandleT<TreeSTag>((lIndividual)[0])->setStructureIDInvalid();
			Beagle_LogVerboseM(
							   ioContext.getSystem().getLogger(),
							   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
							   std::string("Set structure id invalid") );
		}
		
		Beagle_LogDebugM(
						 ioContext.getSystem().getLogger(),
						 "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
						 std::string("Individual after constrained GP swap mutation: ")+
						 ioIndividual.serialize()
						 );
	}
	else {
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationSwapDepthSelectiveConstrainedOp",
						   "Unable to swap mutate the constrained individual"
						   );
	}
	
	return lMutationDone;
	Beagle_StackTraceEndM("bool GP::MutationSwapDepthSelectiveConstrainedOp::mutate(Beagle::Individual& ioIndividual, Beagle::Context& ioContext)");
}