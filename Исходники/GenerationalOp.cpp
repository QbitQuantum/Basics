/*!
 *  \brief Apply the operation on a deme in the given context.
 *  \param ioDeme Reference to the deme on which the operation takes place.
 *  \param ioContext Evolutionary context of the operation.
 */
void GenerationalOp::operate(Deme& ioDeme, Context& ioContext)
{
    Beagle_StackTraceBeginM();
    Beagle_NonNullPointerAssertM(getRootNode());
    Beagle_NonNullPointerAssertM(mElitismKeepSize);
    Beagle_ValidateParameterM(mElitismKeepSize->getWrappedValue() <= ioDeme.size(),
                              "ec.elite.keepsize",
                              "The elistism keepsize must be less than the deme size!");

    Beagle_LogTraceM(
        ioContext.getSystem().getLogger(),
        "Processing using generational replacement strategy the " <<
        uint2ordinal(ioContext.getDemeIndex()+1) << " deme"
    );
    Beagle_LogTraceM(ioContext.getSystem().getLogger(), (*this));

    RouletteT<unsigned int> lRoulette;
    buildRoulette(lRoulette, ioContext);

    Individual::Bag lOffsprings;
    const Factory& lFactory = ioContext.getSystem().getFactory();
    if(mElitismKeepSize->getWrappedValue() > 0) {
        History::Handle lHistory = castHandleT<History>(ioContext.getSystem().haveComponent("History"));
        std::make_heap(ioDeme.begin(), ioDeme.end(), IsLessPointerPredicate());
        for(unsigned int i=0; i<mElitismKeepSize->getWrappedValue(); ++i) {
            std::string lIndividualType = ioDeme[0]->getType();
            Individual::Alloc::Handle lIndividualAlloc =
                castHandleT<Individual::Alloc>(lFactory.getAllocator(lIndividualType));
            Individual::Handle lEliteIndiv = castHandleT<Individual>(lIndividualAlloc->allocate());
            lEliteIndiv->copy(*ioDeme[0], ioContext.getSystem());
            lOffsprings.push_back(lEliteIndiv);
            if(lHistory != NULL) {
                HistoryID::Handle lHID = castHandleT<HistoryID>(ioDeme[0]->getMember("HistoryID"));
                std::vector<HistoryID> lParent;
                if(lHID != NULL) lParent.push_back(*lHID);
                lHistory->allocateNewID(*lEliteIndiv);
                lHistory->trace(ioContext, lParent, lEliteIndiv, getName(), "elitism");
            }
            std::pop_heap(ioDeme.begin(), (ioDeme.end()-i), IsLessPointerPredicate());
        }
    }

    for(unsigned int i=mElitismKeepSize->getWrappedValue(); i<ioDeme.size(); ++i) {
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

    for(unsigned int j=0; j<lOffsprings.size(); ++j) ioDeme[j] = lOffsprings[j];
    Beagle_StackTraceEndM();
}