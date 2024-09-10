void SSABuilder::checkForTrivialPhis2(Node *node, 
                                      const StlVectorSet<VarOpnd *> *lookatVars,
                                      StlVector<VarOpnd *> *changedVars,
                                      StlVector<Opnd *> *removedVars)
{
    // Check that phi insts can start from the second or third position only
    // and goes in a row
    assert(phiInstsOnRightPositionsInBB(node));

    Inst* phi = (Inst*)node->getSecondInst();
    if(phi && !phi->isPhi()) {
        // try the next one (third)
        phi = phi->getNextInst();
    }

    Inst *nextphi = NULL;
#ifdef DEBUG_SSA
    if (Log::isEnabled()) {
        Log::out() << "Checking node " << (int)node->getId() 
                   << " for trivial phis2" << ::std::endl;
    }
#endif
    for (;phi->isPhi(); phi = nextphi) {
        nextphi = phi->getNextInst();
#ifdef _DEBUG
        PhiInst *phiInst = phi->asPhiInst();
        assert(phiInst);
#endif
        U_32 nSrcs = phi->getNumSrcOperands();
        if (nSrcs <= 1) {
            // phi must be trivial
#ifdef DEBUG_SSA
            ::std::ostream &cout = Log::out();
            if (Log::isEnabled()) {
                cout << "removing trivial2 instruction "; phi->print(cout); cout << ::std::endl;
            }
#endif
            Opnd *dstOp = phi->getDst();
            VarOpnd *varOp = dstOp->asVarOpnd();
            if (!varOp) {
                SsaVarOpnd *ssaOp = dstOp->asSsaVarOpnd();
                assert(ssaOp);
                varOp = ssaOp->getVar();
            }
            assert(!lookatVars || (lookatVars->has(varOp)));
            changedVars->push_back(varOp);
            removedVars->push_back(dstOp);
            phi->unlink();
        }
    }
}