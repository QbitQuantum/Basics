/*!
 *  \brief Read switch case operator from XML subtree and system.
 *  \param inIter XML iterator from which the operator is read.
 *  \param ioSystem Beagle System.
 *  \throw IOException If a reading error occurs.
 */
void HPC::SwitchTypeOp::readWithSystem(PACC::XML::ConstIterator inIter, System& ioSystem)
{
        Beagle_StackTraceBeginM();

        if((inIter->getType()!=PACC::XML::eData) || (inIter->getValue()!=getName())) {
                std::ostringstream lOSS;
                lOSS << "tag <" << getName() << "> expected!" << std::flush;
                throw Beagle_IOExceptionNodeM(*inIter, lOSS.str());
        }
	
	mOperatorSetMap.clear();
        for(PACC::XML::ConstIterator lChild=inIter->getFirstChild(); lChild; ++lChild) {
                if(lChild->getType() == PACC::XML::eData) {
			mOperatorSetMap[lChild->getValue()] = Operator::Bag();
			OperatorSetMap::iterator lIterMap = mOperatorSetMap.find(lChild->getValue());
			for(PACC::XML::ConstIterator lChild2=lChild->getFirstChild(); lChild2; ++lChild2) {
				if(lChild2->getType() == PACC::XML::eData) {
					const std::string& lOpName = lChild2->getValue();
					Operator::Alloc::Handle lOpAlloc =
						castHandleT<Operator::Alloc>(ioSystem.getFactory().getAllocator(lOpName));
					if(lOpAlloc == 0) {
						std::ostringstream lOSS;
						lOSS << "Operator '" << lOpName << "' not found in factory!";
						throw Beagle_RunTimeExceptionM(lOSS.str());
					}
					Operator::Handle lOp = castHandleT<Operator>(lOpAlloc->allocate());
					lOp->setName(lOpName);
					lIterMap->second.push_back(lOp);
					lOp->readWithSystem(lChild2, ioSystem);
				}
			}
		}
        }

        Beagle_StackTraceEndM();
}