/// RewriteUsesOfClonedInstructions - We just cloned the instructions from the
/// old header into the preheader.  If there were uses of the values produced by
/// these instruction that were outside of the loop, we have to insert PHI nodes
/// to merge the two values.  Do this now.
static void RewriteUsesOfClonedInstructions(BasicBlock *OrigHeader,
                                            BasicBlock *OrigPreheader,
                                            ValueToValueMapTy &ValueMap) {
  // Remove PHI node entries that are no longer live.
  BasicBlock::iterator I, E = OrigHeader->end();
  for (I = OrigHeader->begin(); PHINode *PN = dyn_cast<PHINode>(I); ++I)
    PN->removeIncomingValue(PN->getBasicBlockIndex(OrigPreheader));

  // Now fix up users of the instructions in OrigHeader, inserting PHI nodes
  // as necessary.
  SSAUpdater SSA;
  for (I = OrigHeader->begin(); I != E; ++I) {
    Value *OrigHeaderVal = &*I;

    // If there are no uses of the value (e.g. because it returns void), there
    // is nothing to rewrite.
    if (OrigHeaderVal->use_empty())
      continue;

    Value *OrigPreHeaderVal = ValueMap.lookup(OrigHeaderVal);

    // The value now exits in two versions: the initial value in the preheader
    // and the loop "next" value in the original header.
    SSA.Initialize(OrigHeaderVal->getType(), OrigHeaderVal->getName());
    SSA.AddAvailableValue(OrigHeader, OrigHeaderVal);
    SSA.AddAvailableValue(OrigPreheader, OrigPreHeaderVal);

    // Visit each use of the OrigHeader instruction.
    for (Value::use_iterator UI = OrigHeaderVal->use_begin(),
         UE = OrigHeaderVal->use_end(); UI != UE; ) {
      // Grab the use before incrementing the iterator.
      Use &U = *UI;

      // Increment the iterator before removing the use from the list.
      ++UI;

      // SSAUpdater can't handle a non-PHI use in the same block as an
      // earlier def. We can easily handle those cases manually.
      Instruction *UserInst = cast<Instruction>(U.getUser());
      if (!isa<PHINode>(UserInst)) {
        BasicBlock *UserBB = UserInst->getParent();

        // The original users in the OrigHeader are already using the
        // original definitions.
        if (UserBB == OrigHeader)
          continue;

        // Users in the OrigPreHeader need to use the value to which the
        // original definitions are mapped.
        if (UserBB == OrigPreheader) {
          U = OrigPreHeaderVal;
          continue;
        }
      }

      // Anything else can be handled by SSAUpdater.
      SSA.RewriteUse(U);
    }

    // Replace MetadataAsValue(ValueAsMetadata(OrigHeaderVal)) uses in debug
    // intrinsics.
    LLVMContext &C = OrigHeader->getContext();
    if (auto *VAM = ValueAsMetadata::getIfExists(OrigHeaderVal)) {
      if (auto *MAV = MetadataAsValue::getIfExists(C, VAM)) {
        for (auto UI = MAV->use_begin(), E = MAV->use_end(); UI != E; ) {
          // Grab the use before incrementing the iterator. Otherwise, altering
          // the Use will invalidate the iterator.
          Use &U = *UI++;
          DbgInfoIntrinsic *UserInst = dyn_cast<DbgInfoIntrinsic>(U.getUser());
          if (!UserInst) continue;

          // The original users in the OrigHeader are already using the original
          // definitions.
          BasicBlock *UserBB = UserInst->getParent();
          if (UserBB == OrigHeader)
            continue;

          // Users in the OrigPreHeader need to use the value to which the
          // original definitions are mapped and anything else can be handled by
          // the SSAUpdater. To avoid adding PHINodes, check if the value is
          // available in UserBB, if not substitute undef.
          Value *NewVal;
          if (UserBB == OrigPreheader)
            NewVal = OrigPreHeaderVal;
          else if (SSA.HasValueForBlock(UserBB))
            NewVal = SSA.GetValueInMiddleOfBlock(UserBB);
          else
            NewVal = UndefValue::get(OrigHeaderVal->getType());
          U = MetadataAsValue::get(C, ValueAsMetadata::get(NewVal));
        }
      }
    }
  }
}