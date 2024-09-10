/// AddLandingPadInfo - Extract the exception handling information from the
/// landingpad instruction and add them to the specified machine module info.
void llvm::AddLandingPadInfo(const LandingPadInst &I, MachineModuleInfo &MMI,
                             MachineBasicBlock *MBB) {
    if (const auto *PF = dyn_cast<Function>(
                             I.getParent()->getParent()->getPersonalityFn()->stripPointerCasts()))
        MMI.addPersonality(PF);

    if (I.isCleanup())
        MMI.addCleanup(MBB);

    // FIXME: New EH - Add the clauses in reverse order. This isn't 100% correct,
    //        but we need to do it this way because of how the DWARF EH emitter
    //        processes the clauses.
    for (unsigned i = I.getNumClauses(); i != 0; --i) {
        Value *Val = I.getClause(i - 1);
        if (I.isCatch(i - 1)) {
            MMI.addCatchTypeInfo(MBB,
                                 dyn_cast<GlobalValue>(Val->stripPointerCasts()));
        } else {
            // Add filters in a list.
            Constant *CVal = cast<Constant>(Val);
            SmallVector<const GlobalValue*, 4> FilterList;
            for (User::op_iterator
                    II = CVal->op_begin(), IE = CVal->op_end(); II != IE; ++II)
                FilterList.push_back(cast<GlobalValue>((*II)->stripPointerCasts()));

            MMI.addFilterTypeInfo(MBB, FilterList);
        }
    }
}