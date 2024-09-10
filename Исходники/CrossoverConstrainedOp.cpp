/*!
 *  \brief Select a node for mating in the given individual, following the constraints penalties.
 *  \param outSelectTreeIndex Tree index of the selected node.
 *  \param outSelectNodeIndex Index of the selected node.
 *  \param inSelectABranch True if node to select must be a branch, false if it must a leaf.
 *  \param inNodeReturnType Desired return type for the nodes to be selected.
 *  \param inPrimitSetIndex Primitive set index to which the tree must be associated.
 *  \param inMaxSubTreeDepth Maximum sub tree depth allowed of the node to be selected.
 *  \param inMaxSubTreeSize Maximum sub tree size allowed of the node to be selected.
 *  \param inIndividual Individual to select the node from.
 *  \param ioContext Evolutionary context.
 *  \return True if there was node to select, false if no node respected all constraints.
 */
bool STGP::CrossoverConstrainedOp::selectNodeToMateWithType(unsigned int& outSelectTreeIndex,
        unsigned int& outSelectNodeIndex,
        bool inSelectABranch,
        const std::type_info* inNodeReturnType,
        unsigned int inPrimitSetIndex,
        unsigned int inMaxSubTreeDepth,
        unsigned int inMaxSubTreeSize,
        GP::Individual& inIndividual,
        GP::Context& ioContext) const
{
	Beagle_StackTraceBeginM();
	RouletteT< std::pair<unsigned int,unsigned int> > lRoulette;
	GP::Tree::Handle lOldTreeHandle = ioContext.getGenotypeHandle();
	const unsigned int lOldTreeIndex = ioContext.getGenotypeIndex();
	ioContext.emptyCallStack();
	for(unsigned int i=0; i<inIndividual.size(); ++i) {
		if(inIndividual[i]->getPrimitiveSetIndex() != inPrimitSetIndex) continue;
		ioContext.setGenotypeHandle(inIndividual[i]);
		ioContext.setGenotypeIndex(i);
		buildRouletteWithType(lRoulette,
		                      inSelectABranch,
		                      inNodeReturnType,
		                      inMaxSubTreeDepth,
		                      inMaxSubTreeSize,
		                      0,
		                      *inIndividual[i],
		                      ioContext);
	}
	ioContext.setGenotypeIndex(lOldTreeIndex);
	ioContext.setGenotypeHandle(lOldTreeHandle);
	if(lRoulette.size() == 0) return false;
	std::pair<unsigned int,unsigned int> lSelectedNode =
	    lRoulette.select(ioContext.getSystem().getRandomizer());
	outSelectTreeIndex = lSelectedNode.first;
	outSelectNodeIndex = lSelectedNode.second;
	return true;
	Beagle_StackTraceEndM();
}