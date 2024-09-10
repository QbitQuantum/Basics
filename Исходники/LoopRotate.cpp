static void
updateSSAForUseOfInst(SILSSAUpdater &Updater,
                      SmallVectorImpl<SILArgument*> &InsertedPHIs,
                      const llvm::DenseMap<ValueBase *, SILValue> &ValueMap,
                      SILBasicBlock *Header, SILBasicBlock *EntryCheckBlock,
                      ValueBase *Inst) {
    if (Inst->use_empty())
        return;

    // Find the mapped instruction.
    assert(ValueMap.count(Inst) && "Expected to find value in map!");
    SILValue MappedValue = ValueMap.find(Inst)->second;
    assert(MappedValue);

    // For each use of a specific result value of the instruction.
    if (Inst->hasValue()) {
        SILValue Res(Inst);
        assert(Res->getType() == MappedValue->getType() && "The types must match");

        InsertedPHIs.clear();
        Updater.Initialize(Res->getType());
        Updater.AddAvailableValue(Header, Res);
        Updater.AddAvailableValue(EntryCheckBlock, MappedValue);


        // Because of the way that phi nodes are represented we have to collect all
        // uses before we update SSA. Modifying one phi node can invalidate another
        // unrelated phi nodes operands through the common branch instruction (that
        // has to be modified). This would invalidate a plain ValueUseIterator.
        // Instead we collect uses wrapping uses in branches specially so that we
        // can reconstruct the use even after the branch has been modified.
        SmallVector<UseWrapper, 8> StoredUses;
        for (auto *U : Res->getUses())
            StoredUses.push_back(UseWrapper(U));
        for (auto U : StoredUses) {
            Operand *Use = U;
            SILInstruction *User = Use->getUser();
            assert(User && "Missing user");

            // Ignore uses in the same basic block.
            if (User->getParent() == Header)
                continue;

            assert(User->getParent() != EntryCheckBlock &&
                   "The entry check block should dominate the header");
            Updater.RewriteUse(*Use);
        }
        // Canonicalize inserted phis to avoid extra BB Args.
        for (SILArgument *Arg : InsertedPHIs) {
            if (SILInstruction *Inst = replaceBBArgWithCast(Arg)) {
                Arg->replaceAllUsesWith(Inst);
                // DCE+SimplifyCFG runs as a post-pass cleanup.
                // DCE replaces dead arg values with undef.
                // SimplifyCFG deletes the dead BB arg.
            }
        }
    }
}