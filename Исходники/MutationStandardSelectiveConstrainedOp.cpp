/*!
 *  \brief Standard mutate a constrained GP individual.
 *  \param ioIndividual GP individual to standard mutate.
 *  \param ioContext Context of the evolution.
 *  \return True if the individual is effectively mutated, false if not.
 */
bool GP::MutationStandardSelectiveConstrainedOp::mutate(Beagle::Individual& ioIndividual, Beagle::Context& ioContext)
{
	Beagle_StackTraceBeginM();
	GP::Individual& lIndividual        = castObjectT<GP::Individual&>(ioIndividual);
	GP::Context& lContext              = castObjectT<GP::Context&>(ioContext);
	unsigned int lMaxTreeDepth         = mMaxTreeDepth->getWrappedValue();
	unsigned int lMaxRegenerationDepth = mMaxRegenerationDepth->getWrappedValue();
	
	//Select node to mutate
	unsigned int lChoosenTree = 0;
	unsigned int lChoosenNode = 0;
	
	bool lDoParameterSearch = (lContext.getSystem().getRandomizer().rollUniform(0.0, 1.0) <= mMutParameterPb->getWrappedValue());
	
	//Select primitive based on type
	for(unsigned int lTry = 0; lTry < 2; ++lTry) { //Do only twice
		std::vector<const std::type_info*> lDesiredTypes(1, ArgEph);
		RouletteT< std::pair<unsigned int,unsigned int> > lRoulette;
		SelectiveConstrainedSelectionOp::buildRoulette(lRoulette, lDesiredTypes, lIndividual, lContext,!lDoParameterSearch,lDoParameterSearch);
		
		if(lRoulette.size() == 0) {
			if(lDoParameterSearch) {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
								   string("No EphemeralDouble node found.")
								   );
			}
			else {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
								   string("No non EphemeralDouble node found.")
								   );
			}
			lDoParameterSearch = !lDoParameterSearch;
			if(lTry >= 1) {
				Beagle_LogVerboseM(
								   ioContext.getSystem().getLogger(),
								   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
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
						   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
						   string("Mutation applied only on EphemeralDouble node.")
						   );
	}
	else {
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
						   string("Mutation applied on node that are not EphemeralDouble.")
						   );
	}
	
	
	unsigned int lOldGenotypeIndex = lContext.getGenotypeIndex();
	GP::Tree::Handle lOldGenotypeHandle = lContext.getGenotypeHandle();
	
	Beagle_LogDebugM(
					 ioContext.getSystem().getLogger(),
					 "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
					 std::string("Individual before GP standard mutation: ")+
					 ioIndividual.serialize()
					 );
	
	GP::Tree::Handle lActualTree = lIndividual[lChoosenTree];
	GP::Tree::Handle lNewTree    = castHandleT<GP::Tree>(lIndividual.getTypeAlloc()->allocate());
	lNewTree->setPrimitiveSetIndex(lActualTree->getPrimitiveSetIndex());
	lNewTree->setNumberArguments(lActualTree->getNumberArguments());
	unsigned int lChoosenNodeSubTreeSize = (*lActualTree)[lChoosenNode].mSubTreeSize;
	lNewTree->insert(lNewTree->end(), lActualTree->begin(), lActualTree->begin()+lChoosenNode);
	lContext.setGenotypeIndex(lChoosenTree);
	lContext.setGenotypeHandle(lActualTree);
	lContext.emptyCallStack();
	lActualTree->setContextToNode(lChoosenNode, lContext);
	lContext.popCallStack();
	const unsigned int lMaxSubTreeDepth =
    minOf<unsigned int>(lMaxTreeDepth - lContext.getCallStackSize(), lMaxRegenerationDepth);
	lIndividual[lChoosenTree] = lNewTree;
	lContext.setGenotypeHandle(lNewTree);
	
	unsigned int lAttempt=0;
	if(lMaxSubTreeDepth >= 1) {
		for(; lAttempt < mNumberAttempts->getWrappedValue(); lAttempt++) {
			if(mInitOp->initTree(*lNewTree, 1, lMaxSubTreeDepth, lContext) != 0) break;
		}
	} else {
		lAttempt = mNumberAttempts->getWrappedValue();
	}
	
	if(lAttempt == mNumberAttempts->getWrappedValue()) {
		lIndividual[lChoosenTree] = lActualTree;
		lContext.setGenotypeIndex(lOldGenotypeIndex);
		lContext.setGenotypeHandle(lOldGenotypeHandle);
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
						   "Unable to GP standard mutate the individual"
						   );
		return false;
	}
	
	if( !lDoParameterSearch ) {
		//Set structure id invalid
		castHandleT<TreeSTag>((lIndividual)[0])->setStructureIDInvalid();
		Beagle_LogVerboseM(
						   ioContext.getSystem().getLogger(),
						   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
						   std::string("Set structure id invalid") );
	}
	
	Beagle_LogVerboseM(
					   ioContext.getSystem().getLogger(),
					   "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
					   std::string("GP standard mutate the ")+uint2ordinal(lChoosenNode+1)+
					   std::string(" node, ")+ (*lActualTree)[lChoosenNode].mPrimitive->getName()
					   +std::string(", of the ")+uint2ordinal(lChoosenTree+1)+
					   std::string(" tree with max depth ")+uint2str(lMaxSubTreeDepth)
					   );
	
	lNewTree->insert(lNewTree->end(),
					 lActualTree->begin()+lChoosenNode+lChoosenNodeSubTreeSize,
					 lActualTree->end());
	unsigned int lDiffSize =
    (*lActualTree)[lChoosenNode].mSubTreeSize - (*lNewTree)[lChoosenNode].mSubTreeSize;
	for(unsigned int l=0; l<lContext.getCallStackSize(); l++) {
		(*lNewTree)[lContext.getCallStackElement(l)].mSubTreeSize -= lDiffSize;
	}
	
	lContext.setGenotypeIndex(lOldGenotypeIndex);
	lContext.setGenotypeHandle(lOldGenotypeHandle);
	
	Beagle_LogDebugM(
					 ioContext.getSystem().getLogger(),
					 "mutation", "Beagle::GP::MutationStandardSelectiveConstrainedOp",
					 std::string("Individual after GP standard mutation: ")+
					 ioIndividual.serialize()
					 );
	
	return true;
	Beagle_StackTraceEndM("bool GP::MutationStandardSelectiveConstrainedOp::mutate(Beagle::Individual& ioIndividual, Beagle::Context& ioContext)");
}