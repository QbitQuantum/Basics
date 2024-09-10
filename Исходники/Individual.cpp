/*!
 *  \brief Randomly select a node that takes no argument from a specific
 *    tree in the individual.
 *  \return Randomly selected tree
 */
unsigned int GP::Individual::chooseRandomNodeWithoutArgs(unsigned int inTree,
        GP::Context& ioContext) const
{
	Beagle_StackTraceBeginM();
	// Loop through the tree adding appropriate nodes into the roulette
	unsigned int lSize = operator[](inTree)->size();
	RouletteT<unsigned int> lRoulette;
	for (unsigned int i=0; i<lSize; i++) {
		if (operator[](inTree)->operator[](i).mSubTreeSize == 1) {
			lRoulette.insert(i);
		}
	}
	// Select node with roulette
	Beagle_AssertM(!lRoulette.empty());
	return lRoulette.select(ioContext.getSystem().getRandomizer());
	Beagle_StackTraceEndM();
}