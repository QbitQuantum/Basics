/// Insert monomorphic inline caches for a specific class or metatype
/// type \p SubClassTy.
static FullApplySite speculateMonomorphicTarget(FullApplySite AI,
                                                SILType SubType,
                                                CheckedCastBranchInst *&CCBI) {
  CCBI = nullptr;
  // Bail if this class_method cannot be devirtualized.
  if (!canDevirtualizeClassMethod(AI, SubType))
    return FullApplySite();

  // Create a diamond shaped control flow and a checked_cast_branch
  // instruction that checks the exact type of the object.
  // This cast selects between two paths: one that calls the slow dynamic
  // dispatch and one that calls the specific method.
  auto It = AI.getInstruction()->getIterator();
  SILFunction *F = AI.getFunction();
  SILBasicBlock *Entry = AI.getParent();

  // Iden is the basic block containing the direct call.
  SILBasicBlock *Iden = F->createBasicBlock();
  // Virt is the block containing the slow virtual call.
  SILBasicBlock *Virt = F->createBasicBlock();
  Iden->createBBArg(SubType);

  SILBasicBlock *Continue = Entry->splitBasicBlock(It);

  SILBuilderWithScope Builder(Entry, AI.getInstruction());
  // Create the checked_cast_branch instruction that checks at runtime if the
  // class instance is identical to the SILType.

  ClassMethodInst *CMI = cast<ClassMethodInst>(AI.getCallee());

  CCBI = Builder.createCheckedCastBranch(AI.getLoc(), /*exact*/ true,
                                       CMI->getOperand(), SubType, Iden,
                                       Virt);
  It = CCBI->getIterator();

  SILBuilderWithScope VirtBuilder(Virt, AI.getInstruction());
  SILBuilderWithScope IdenBuilder(Iden, AI.getInstruction());
  // This is the class reference downcasted into subclass SubType.
  SILValue DownCastedClassInstance = Iden->getBBArg(0);

  // Copy the two apply instructions into the two blocks.
  FullApplySite IdenAI = CloneApply(AI, IdenBuilder);
  FullApplySite VirtAI = CloneApply(AI, VirtBuilder);

  // See if Continue has a release on self as the instruction right after the
  // apply. If it exists, move it into position in the diamond.
  if (auto *Release =
          dyn_cast<StrongReleaseInst>(std::next(Continue->begin()))) {
    if (Release->getOperand() == CMI->getOperand()) {
      VirtBuilder.createStrongRelease(Release->getLoc(), CMI->getOperand());
      IdenBuilder.createStrongRelease(Release->getLoc(),
                                      DownCastedClassInstance);
      Release->eraseFromParent();
    }
  }

  // Create a PHInode for returning the return value from both apply
  // instructions.
  SILArgument *Arg = Continue->createBBArg(AI.getType());
  if (!isa<TryApplyInst>(AI)) {
    IdenBuilder.createBranch(AI.getLoc(), Continue,
                             ArrayRef<SILValue>(IdenAI.getInstruction()));
    VirtBuilder.createBranch(AI.getLoc(), Continue,
                             ArrayRef<SILValue>(VirtAI.getInstruction()));
  }

  // Remove the old Apply instruction.
  if (!isa<TryApplyInst>(AI))
    AI.getInstruction()->replaceAllUsesWith(Arg);
  auto *OriginalBB = AI.getParent();
  AI.getInstruction()->eraseFromParent();
  if (OriginalBB->empty())
    OriginalBB->removeFromParent();

  // Update the stats.
  NumTargetsPredicted++;

  // Devirtualize the apply instruction on the identical path.
  auto NewInstPair = devirtualizeClassMethod(IdenAI, DownCastedClassInstance);
  assert(NewInstPair.first && "Expected to be able to devirtualize apply!");
  replaceDeadApply(IdenAI, NewInstPair.first);

  // Split critical edges resulting from VirtAI.
  if (auto *TAI = dyn_cast<TryApplyInst>(VirtAI)) {
    auto *ErrorBB = TAI->getFunction()->createBasicBlock();
    ErrorBB->createBBArg(TAI->getErrorBB()->getBBArg(0)->getType());
    Builder.setInsertionPoint(ErrorBB);
    Builder.createBranch(TAI->getLoc(), TAI->getErrorBB(),
                         {ErrorBB->getBBArg(0)});

    auto *NormalBB = TAI->getFunction()->createBasicBlock();
    NormalBB->createBBArg(TAI->getNormalBB()->getBBArg(0)->getType());
    Builder.setInsertionPoint(NormalBB);
    Builder.createBranch(TAI->getLoc(), TAI->getNormalBB(),
                        {NormalBB->getBBArg(0) });

    Builder.setInsertionPoint(VirtAI.getInstruction());
    SmallVector<SILValue, 4> Args;
    for (auto Arg : VirtAI.getArguments()) {
      Args.push_back(Arg);
    }
    FullApplySite NewVirtAI = Builder.createTryApply(VirtAI.getLoc(), VirtAI.getCallee(),
        VirtAI.getSubstCalleeSILType(), VirtAI.getSubstitutions(),
        Args, NormalBB, ErrorBB);
    VirtAI.getInstruction()->eraseFromParent();
    VirtAI = NewVirtAI;
  }

  return VirtAI;
}