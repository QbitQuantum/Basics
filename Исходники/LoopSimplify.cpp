/// \brief This method is called when the specified loop has more than one
/// backedge in it.
///
/// If this occurs, revector all of these backedges to target a new basic block
/// and have that block branch to the loop header.  This ensures that loops
/// have exactly one backedge.
static BasicBlock *insertUniqueBackedgeBlock(Loop *L, BasicBlock *Preheader,
                                             DominatorTree *DT, LoopInfo *LI) {
  assert(L->getNumBackEdges() > 1 && "Must have > 1 backedge!");

  // Get information about the loop
  BasicBlock *Header = L->getHeader();
  Function *F = Header->getParent();

  // Unique backedge insertion currently depends on having a preheader.
  if (!Preheader)
    return nullptr;

  // The header is not a landing pad; preheader insertion should ensure this.
  assert(!Header->isLandingPad() && "Can't insert backedge to landing pad");

  // Figure out which basic blocks contain back-edges to the loop header.
  std::vector<BasicBlock*> BackedgeBlocks;
  for (pred_iterator I = pred_begin(Header), E = pred_end(Header); I != E; ++I){
    BasicBlock *P = *I;

    // Indirectbr edges cannot be split, so we must fail if we find one.
    if (isa<IndirectBrInst>(P->getTerminator()))
      return nullptr;

    if (P != Preheader) BackedgeBlocks.push_back(P);
  }

  // Create and insert the new backedge block...
  BasicBlock *BEBlock = BasicBlock::Create(Header->getContext(),
                                           Header->getName() + ".backedge", F);
  BranchInst *BETerminator = BranchInst::Create(Header, BEBlock);
  BETerminator->setDebugLoc(Header->getFirstNonPHI()->getDebugLoc());

  DEBUG(dbgs() << "LoopSimplify: Inserting unique backedge block "
               << BEBlock->getName() << "\n");

  // Move the new backedge block to right after the last backedge block.
  Function::iterator InsertPos = BackedgeBlocks.back(); ++InsertPos;
  F->getBasicBlockList().splice(InsertPos, F->getBasicBlockList(), BEBlock);

  // Now that the block has been inserted into the function, create PHI nodes in
  // the backedge block which correspond to any PHI nodes in the header block.
  for (BasicBlock::iterator I = Header->begin(); isa<PHINode>(I); ++I) {
    PHINode *PN = cast<PHINode>(I);
    PHINode *NewPN = PHINode::Create(PN->getType(), BackedgeBlocks.size(),
                                     PN->getName()+".be", BETerminator);

    // Loop over the PHI node, moving all entries except the one for the
    // preheader over to the new PHI node.
    unsigned PreheaderIdx = ~0U;
    bool HasUniqueIncomingValue = true;
    Value *UniqueValue = nullptr;
    for (unsigned i = 0, e = PN->getNumIncomingValues(); i != e; ++i) {
      BasicBlock *IBB = PN->getIncomingBlock(i);
      Value *IV = PN->getIncomingValue(i);
      if (IBB == Preheader) {
        PreheaderIdx = i;
      } else {
        NewPN->addIncoming(IV, IBB);
        if (HasUniqueIncomingValue) {
          if (!UniqueValue)
            UniqueValue = IV;
          else if (UniqueValue != IV)
            HasUniqueIncomingValue = false;
        }
      }
    }

    // Delete all of the incoming values from the old PN except the preheader's
    assert(PreheaderIdx != ~0U && "PHI has no preheader entry??");
    if (PreheaderIdx != 0) {
      PN->setIncomingValue(0, PN->getIncomingValue(PreheaderIdx));
      PN->setIncomingBlock(0, PN->getIncomingBlock(PreheaderIdx));
    }
    // Nuke all entries except the zero'th.
    for (unsigned i = 0, e = PN->getNumIncomingValues()-1; i != e; ++i)
      PN->removeIncomingValue(e-i, false);

    // Finally, add the newly constructed PHI node as the entry for the BEBlock.
    PN->addIncoming(NewPN, BEBlock);

    // As an optimization, if all incoming values in the new PhiNode (which is a
    // subset of the incoming values of the old PHI node) have the same value,
    // eliminate the PHI Node.
    if (HasUniqueIncomingValue) {
      NewPN->replaceAllUsesWith(UniqueValue);
      BEBlock->getInstList().erase(NewPN);
    }
  }

  // Now that all of the PHI nodes have been inserted and adjusted, modify the
  // backedge blocks to just to the BEBlock instead of the header.
  for (unsigned i = 0, e = BackedgeBlocks.size(); i != e; ++i) {
    TerminatorInst *TI = BackedgeBlocks[i]->getTerminator();
    for (unsigned Op = 0, e = TI->getNumSuccessors(); Op != e; ++Op)
      if (TI->getSuccessor(Op) == Header)
        TI->setSuccessor(Op, BEBlock);
  }

  //===--- Update all analyses which we must preserve now -----------------===//

  // Update Loop Information - we know that this block is now in the current
  // loop and all parent loops.
  L->addBasicBlockToLoop(BEBlock, *LI);

  // Update dominator information
  DT->splitBlock(BEBlock);

  return BEBlock;
}