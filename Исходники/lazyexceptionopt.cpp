/**
 * Checks that exception edges are equal for newobj instruction node and
 * throw instruction node.
 * @param bs - bit set of operands that may be optimized
 */
void
LazyExceptionOpt::fixOptCandidates(BitSet* bs) {
    OptCandidates::iterator it;
    Inst* oinst;
    MethodCallInst* iinst;
    Inst* tinst;
    Inst* tlinst;
    U_32 opcount;
    Opnd **opnds = NULL;

    if (optCandidates == NULL) {
        return;
    }
    for (it = optCandidates->begin( ); it != optCandidates->end( ); it++ ) {
        if (bs->getBit((*it)->opndId)) {
            oinst = (*it)->objInst;
            assert(oinst != NULL);
#ifdef _DEBUG
            if (Log::isEnabled()) {
                Log::out() << "  to remove ";
                oinst->print(Log::out());
                Log::out() << std::endl;
            }
#endif
            if ((*it)->initInst == NULL) {
#ifdef _DEBUG
                if (Log::isEnabled()) {
                    Log::out() << "  init inst is null ";
                    Log::out() << std::endl;
                }
#endif
                continue;
            }
            iinst = (*it)->initInst->asMethodCallInst();
            // inline info from constructor should be propagated to lazy
            // exception if any
#ifdef _DEBUG
            if (Log::isEnabled()) {
                Log::out() << "  to remove ";
                iinst->print(Log::out());
                Log::out() << std::endl;
            }
#endif
            assert((*it)->throwInsts != NULL);
            assert(iinst->getNumSrcOperands() >= 3);
            if (!removeInsts(oinst,iinst))
                continue;   // to null bitset?
            TypeManager& tm = irManager.getTypeManager();
            Opnd* mpt = irManager.getOpndManager().createSsaTmpOpnd(
                            tm.getMethodPtrType(iinst->getMethodDesc()));
            opcount = iinst->getNumSrcOperands()-2;  //numSrc-3+1
            if (opcount >0) {
                opnds = new (leMemManager) Opnd*[opcount];   //local mem should be used
                opnds[0] = mpt;
                for (U_32 i = 0; i < opcount-1; i++)
                    opnds[i+1] = iinst->getSrc(i+3);
            }
            Inst* mptinst = irManager.getInstFactory().makeLdFunAddr(mpt,iinst->getMethodDesc());
#ifdef _DEBUG
            if (Log::isEnabled()) {
                Log::out() << "  1st      ";
                mptinst->print(Log::out());
                Log::out() << std::endl;
            }
#endif
            ThrowInsts::iterator it1;
            for (it1 = (*it)->throwInsts->begin(); it1 !=(*it)->throwInsts->end(); it1++) {
                tinst = *it1;
                assert(tinst != NULL);
                tlinst=irManager.getInstFactory().makeVMHelperCall(
                           OpndManager::getNullOpnd(), VM_RT_THROW_LAZY, opcount, opnds);
#ifdef _DEBUG
                if (Log::isEnabled()) {
                    Log::out() << "  2nd      ";
                    tlinst->print(Log::out());
                    Log::out() << std::endl;
                }
                if (Log::isEnabled()) {
                    Log::out() << "  to change ";
                    tinst->print(Log::out());
                    Log::out() << std::endl;
                }
#endif
                mptinst->insertBefore(tinst);
                tlinst->insertBefore(tinst);
                tinst->unlink();

                uint16 bcOffset = iinst->getBCOffset();
                mptinst->setBCOffset(bcOffset);
                tlinst->setBCOffset(bcOffset);
            }
        }
    }
}