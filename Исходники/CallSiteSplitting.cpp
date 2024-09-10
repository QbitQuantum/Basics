/// For each (predecessor, conditions from predecessors) pair, it will split the
/// basic block containing the call site, hook it up to the predecessor and
/// replace the call instruction with new call instructions, which contain
/// constraints based on the conditions from their predecessors.
/// For example, in the IR below with an OR condition, the call-site can
/// be split. In this case, Preds for Tail is [(Header, a == null),
/// (TBB, a != null, b == null)]. Tail is replaced by 2 split blocks, containing
/// CallInst1, which has constraints based on the conditions from Head and
/// CallInst2, which has constraints based on the conditions coming from TBB.
///
/// From :
///
///   Header:
///     %c = icmp eq i32* %a, null
///     br i1 %c %Tail, %TBB
///   TBB:
///     %c2 = icmp eq i32* %b, null
///     br i1 %c %Tail, %End
///   Tail:
///     %ca = call i1  @callee (i32* %a, i32* %b)
///
///  to :
///
///   Header:                          // PredBB1 is Header
///     %c = icmp eq i32* %a, null
///     br i1 %c %Tail-split1, %TBB
///   TBB:                             // PredBB2 is TBB
///     %c2 = icmp eq i32* %b, null
///     br i1 %c %Tail-split2, %End
///   Tail-split1:
///     %ca1 = call @callee (i32* null, i32* %b)         // CallInst1
///    br %Tail
///   Tail-split2:
///     %ca2 = call @callee (i32* nonnull %a, i32* null) // CallInst2
///    br %Tail
///   Tail:
///    %p = phi i1 [%ca1, %Tail-split1],[%ca2, %Tail-split2]
///
/// Note that in case any arguments at the call-site are constrained by its
/// predecessors, new call-sites with more constrained arguments will be
/// created in createCallSitesOnPredicatedArgument().
static void splitCallSite(
    CallSite CS,
    const SmallVectorImpl<std::pair<BasicBlock *, ConditionsTy>> &Preds) {
  Instruction *Instr = CS.getInstruction();
  BasicBlock *TailBB = Instr->getParent();
  bool IsMustTailCall = CS.isMustTailCall();

  PHINode *CallPN = nullptr;

  // `musttail` calls must be followed by optional `bitcast`, and `ret`. The
  // split blocks will be terminated right after that so there're no users for
  // this phi in a `TailBB`.
  if (!IsMustTailCall && Instr->getNumUses())
    CallPN = PHINode::Create(Instr->getType(), Preds.size(), "phi.call");

  DEBUG(dbgs() << "split call-site : " << *Instr << " into \n");

  assert(Preds.size() == 2 && "The ValueToValueMaps array has size 2.");
  // ValueToValueMapTy is neither copy nor moveable, so we use a simple array
  // here.
  ValueToValueMapTy ValueToValueMaps[2];
  for (unsigned i = 0; i < Preds.size(); i++) {
    BasicBlock *PredBB = Preds[i].first;
    BasicBlock *SplitBlock = DuplicateInstructionsInSplitBetween(
        TailBB, PredBB, &*std::next(Instr->getIterator()), ValueToValueMaps[i]);
    assert(SplitBlock && "Unexpected new basic block split.");

    Instruction *NewCI =
        &*std::prev(SplitBlock->getTerminator()->getIterator());
    CallSite NewCS(NewCI);
    addConditions(NewCS, Preds[i].second);

    // Handle PHIs used as arguments in the call-site.
    for (PHINode &PN : TailBB->phis()) {
      unsigned ArgNo = 0;
      for (auto &CI : CS.args()) {
        if (&*CI == &PN) {
          NewCS.setArgument(ArgNo, PN.getIncomingValueForBlock(SplitBlock));
        }
        ++ArgNo;
      }
    }
    DEBUG(dbgs() << "    " << *NewCI << " in " << SplitBlock->getName()
                 << "\n");
    if (CallPN)
      CallPN->addIncoming(NewCI, SplitBlock);

    // Clone and place bitcast and return instructions before `TI`
    if (IsMustTailCall)
      copyMustTailReturn(SplitBlock, Instr, NewCI);
  }

  NumCallSiteSplit++;

  // FIXME: remove TI in `copyMustTailReturn`
  if (IsMustTailCall) {
    // Remove superfluous `br` terminators from the end of the Split blocks
    // NOTE: Removing terminator removes the SplitBlock from the TailBB's
    // predecessors. Therefore we must get complete list of Splits before
    // attempting removal.
    SmallVector<BasicBlock *, 2> Splits(predecessors((TailBB)));
    assert(Splits.size() == 2 && "Expected exactly 2 splits!");
    for (unsigned i = 0; i < Splits.size(); i++)
      Splits[i]->getTerminator()->eraseFromParent();

    // Erase the tail block once done with musttail patching
    TailBB->eraseFromParent();
    return;
  }

  auto *OriginalBegin = &*TailBB->begin();
  // Replace users of the original call with a PHI mering call-sites split.
  if (CallPN) {
    CallPN->insertBefore(OriginalBegin);
    Instr->replaceAllUsesWith(CallPN);
  }

  // Remove instructions moved to split blocks from TailBB, from the duplicated
  // call instruction to the beginning of the basic block. If an instruction
  // has any uses, add a new PHI node to combine the values coming from the
  // split blocks. The new PHI nodes are placed before the first original
  // instruction, so we do not end up deleting them. By using reverse-order, we
  // do not introduce unnecessary PHI nodes for def-use chains from the call
  // instruction to the beginning of the block.
  auto I = Instr->getReverseIterator();
  while (I != TailBB->rend()) {
    Instruction *CurrentI = &*I++;
    if (!CurrentI->use_empty()) {
      // If an existing PHI has users after the call, there is no need to create
      // a new one.
      if (isa<PHINode>(CurrentI))
        continue;
      PHINode *NewPN = PHINode::Create(CurrentI->getType(), Preds.size());
      for (auto &Mapping : ValueToValueMaps)
        NewPN->addIncoming(Mapping[CurrentI],
                           cast<Instruction>(Mapping[CurrentI])->getParent());
      NewPN->insertBefore(&*TailBB->begin());
      CurrentI->replaceAllUsesWith(NewPN);
    }
    CurrentI->eraseFromParent();
    // We are done once we handled the first original instruction in TailBB.
    if (CurrentI == OriginalBegin)
      break;
  }
}