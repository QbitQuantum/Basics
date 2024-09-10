void WinEHPrepare::cloneCommonBlocks(Function &F) {
  // We need to clone all blocks which belong to multiple funclets.  Values are
  // remapped throughout the funclet to propagate both the new instructions
  // *and* the new basic blocks themselves.
  for (auto &Funclets : FuncletBlocks) {
    BasicBlock *FuncletPadBB = Funclets.first;
    std::vector<BasicBlock *> &BlocksInFunclet = Funclets.second;
    Value *FuncletToken;
    if (FuncletPadBB == &F.getEntryBlock())
      FuncletToken = ConstantTokenNone::get(F.getContext());
    else
      FuncletToken = FuncletPadBB->getFirstNonPHI();

    std::vector<std::pair<BasicBlock *, BasicBlock *>> Orig2Clone;
    ValueToValueMapTy VMap;
    for (BasicBlock *BB : BlocksInFunclet) {
      ColorVector &ColorsForBB = BlockColors[BB];
      // We don't need to do anything if the block is monochromatic.
      size_t NumColorsForBB = ColorsForBB.size();
      if (NumColorsForBB == 1)
        continue;

      DEBUG_WITH_TYPE("winehprepare-coloring",
                      dbgs() << "  Cloning block \'" << BB->getName()
                              << "\' for funclet \'" << FuncletPadBB->getName()
                              << "\'.\n");

      // Create a new basic block and copy instructions into it!
      BasicBlock *CBB =
          CloneBasicBlock(BB, VMap, Twine(".for.", FuncletPadBB->getName()));
      // Insert the clone immediately after the original to ensure determinism
      // and to keep the same relative ordering of any funclet's blocks.
      CBB->insertInto(&F, BB->getNextNode());

      // Add basic block mapping.
      VMap[BB] = CBB;

      // Record delta operations that we need to perform to our color mappings.
      Orig2Clone.emplace_back(BB, CBB);
    }

    // If nothing was cloned, we're done cloning in this funclet.
    if (Orig2Clone.empty())
      continue;

    // Update our color mappings to reflect that one block has lost a color and
    // another has gained a color.
    for (auto &BBMapping : Orig2Clone) {
      BasicBlock *OldBlock = BBMapping.first;
      BasicBlock *NewBlock = BBMapping.second;

      BlocksInFunclet.push_back(NewBlock);
      ColorVector &NewColors = BlockColors[NewBlock];
      assert(NewColors.empty() && "A new block should only have one color!");
      NewColors.push_back(FuncletPadBB);

      DEBUG_WITH_TYPE("winehprepare-coloring",
                      dbgs() << "  Assigned color \'" << FuncletPadBB->getName()
                              << "\' to block \'" << NewBlock->getName()
                              << "\'.\n");

      BlocksInFunclet.erase(
          std::remove(BlocksInFunclet.begin(), BlocksInFunclet.end(), OldBlock),
          BlocksInFunclet.end());
      ColorVector &OldColors = BlockColors[OldBlock];
      OldColors.erase(
          std::remove(OldColors.begin(), OldColors.end(), FuncletPadBB),
          OldColors.end());

      DEBUG_WITH_TYPE("winehprepare-coloring",
                      dbgs() << "  Removed color \'" << FuncletPadBB->getName()
                              << "\' from block \'" << OldBlock->getName()
                              << "\'.\n");
    }

    // Loop over all of the instructions in this funclet, fixing up operand
    // references as we go.  This uses VMap to do all the hard work.
    for (BasicBlock *BB : BlocksInFunclet)
      // Loop over all instructions, fixing each one as we find it...
      for (Instruction &I : *BB)
        RemapInstruction(&I, VMap,
                         RF_IgnoreMissingLocals | RF_NoModuleLevelChanges);

    // Catchrets targeting cloned blocks need to be updated separately from
    // the loop above because they are not in the current funclet.
    SmallVector<CatchReturnInst *, 2> FixupCatchrets;
    for (auto &BBMapping : Orig2Clone) {
      BasicBlock *OldBlock = BBMapping.first;
      BasicBlock *NewBlock = BBMapping.second;

      FixupCatchrets.clear();
      for (BasicBlock *Pred : predecessors(OldBlock))
        if (auto *CatchRet = dyn_cast<CatchReturnInst>(Pred->getTerminator()))
          if (CatchRet->getCatchSwitchParentPad() == FuncletToken)
            FixupCatchrets.push_back(CatchRet);

      for (CatchReturnInst *CatchRet : FixupCatchrets)
        CatchRet->setSuccessor(NewBlock);
    }

    auto UpdatePHIOnClonedBlock = [&](PHINode *PN, bool IsForOldBlock) {
      unsigned NumPreds = PN->getNumIncomingValues();
      for (unsigned PredIdx = 0, PredEnd = NumPreds; PredIdx != PredEnd;
           ++PredIdx) {
        BasicBlock *IncomingBlock = PN->getIncomingBlock(PredIdx);
        bool EdgeTargetsFunclet;
        if (auto *CRI =
                dyn_cast<CatchReturnInst>(IncomingBlock->getTerminator())) {
          EdgeTargetsFunclet = (CRI->getCatchSwitchParentPad() == FuncletToken);
        } else {
          ColorVector &IncomingColors = BlockColors[IncomingBlock];
          assert(!IncomingColors.empty() && "Block not colored!");
          assert((IncomingColors.size() == 1 ||
                  llvm::all_of(IncomingColors,
                               [&](BasicBlock *Color) {
                                 return Color != FuncletPadBB;
                               })) &&
                 "Cloning should leave this funclet's blocks monochromatic");
          EdgeTargetsFunclet = (IncomingColors.front() == FuncletPadBB);
        }
        if (IsForOldBlock != EdgeTargetsFunclet)
          continue;
        PN->removeIncomingValue(IncomingBlock, /*DeletePHIIfEmpty=*/false);
        // Revisit the next entry.
        --PredIdx;
        --PredEnd;
      }
    };

    for (auto &BBMapping : Orig2Clone) {
      BasicBlock *OldBlock = BBMapping.first;
      BasicBlock *NewBlock = BBMapping.second;
      for (PHINode &OldPN : OldBlock->phis()) {
        UpdatePHIOnClonedBlock(&OldPN, /*IsForOldBlock=*/true);
      }
      for (PHINode &NewPN : NewBlock->phis()) {
        UpdatePHIOnClonedBlock(&NewPN, /*IsForOldBlock=*/false);
      }
    }

    // Check to see if SuccBB has PHI nodes. If so, we need to add entries to
    // the PHI nodes for NewBB now.
    for (auto &BBMapping : Orig2Clone) {
      BasicBlock *OldBlock = BBMapping.first;
      BasicBlock *NewBlock = BBMapping.second;
      for (BasicBlock *SuccBB : successors(NewBlock)) {
        for (PHINode &SuccPN : SuccBB->phis()) {
          // Ok, we have a PHI node.  Figure out what the incoming value was for
          // the OldBlock.
          int OldBlockIdx = SuccPN.getBasicBlockIndex(OldBlock);
          if (OldBlockIdx == -1)
            break;
          Value *IV = SuccPN.getIncomingValue(OldBlockIdx);

          // Remap the value if necessary.
          if (auto *Inst = dyn_cast<Instruction>(IV)) {
            ValueToValueMapTy::iterator I = VMap.find(Inst);
            if (I != VMap.end())
              IV = I->second;
          }

          SuccPN.addIncoming(IV, NewBlock);
        }
      }
    }

    for (ValueToValueMapTy::value_type VT : VMap) {
      // If there were values defined in BB that are used outside the funclet,
      // then we now have to update all uses of the value to use either the
      // original value, the cloned value, or some PHI derived value.  This can
      // require arbitrary PHI insertion, of which we are prepared to do, clean
      // these up now.
      SmallVector<Use *, 16> UsesToRename;

      auto *OldI = dyn_cast<Instruction>(const_cast<Value *>(VT.first));
      if (!OldI)
        continue;
      auto *NewI = cast<Instruction>(VT.second);
      // Scan all uses of this instruction to see if it is used outside of its
      // funclet, and if so, record them in UsesToRename.
      for (Use &U : OldI->uses()) {
        Instruction *UserI = cast<Instruction>(U.getUser());
        BasicBlock *UserBB = UserI->getParent();
        ColorVector &ColorsForUserBB = BlockColors[UserBB];
        assert(!ColorsForUserBB.empty());
        if (ColorsForUserBB.size() > 1 ||
            *ColorsForUserBB.begin() != FuncletPadBB)
          UsesToRename.push_back(&U);
      }

      // If there are no uses outside the block, we're done with this
      // instruction.
      if (UsesToRename.empty())
        continue;

      // We found a use of OldI outside of the funclet.  Rename all uses of OldI
      // that are outside its funclet to be uses of the appropriate PHI node
      // etc.
      SSAUpdater SSAUpdate;
      SSAUpdate.Initialize(OldI->getType(), OldI->getName());
      SSAUpdate.AddAvailableValue(OldI->getParent(), OldI);
      SSAUpdate.AddAvailableValue(NewI->getParent(), NewI);

      while (!UsesToRename.empty())
        SSAUpdate.RewriteUseAfterInsertions(*UsesToRename.pop_back_val());
    }
  }
}