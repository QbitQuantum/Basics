/// MoveExtToFormExtLoad - Move a zext or sext fed by a load into the same
/// basic block as the load, unless conditions are unfavorable. This allows
/// SelectionDAG to fold the extend into the load.
///
bool CodeGenPrepare::MoveExtToFormExtLoad(Instruction *I) {
    // Look for a load being extended.
    LoadInst *LI = dyn_cast<LoadInst>(I->getOperand(0));
    if (!LI) return false;

    // If they're already in the same block, there's nothing to do.
    if (LI->getParent() == I->getParent())
        return false;

    // If the load has other users and the truncate is not free, this probably
    // isn't worthwhile.
    if (!LI->hasOneUse() &&
            TLI && (TLI->isTypeLegal(TLI->getValueType(LI->getType())) ||
                    !TLI->isTypeLegal(TLI->getValueType(I->getType()))) &&
            !TLI->isTruncateFree(I->getType(), LI->getType()))
        return false;

    // Check whether the target supports casts folded into loads.
    unsigned LType;
    if (isa<ZExtInst>(I))
        LType = ISD::ZEXTLOAD;
    else {
        assert(isa<SExtInst>(I) && "Unexpected ext type!");
        LType = ISD::SEXTLOAD;
    }
    if (TLI && !TLI->isLoadExtLegal(LType, TLI->getValueType(LI->getType())))
        return false;

    // Move the extend into the same block as the load, so that SelectionDAG
    // can fold it.
    I->removeFromParent();
    I->insertAfter(LI);
    ++NumExtsMoved;
    return true;
}