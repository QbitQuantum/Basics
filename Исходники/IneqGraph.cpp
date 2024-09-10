// addEdgesFor
// Creates a node for I and inserts edges from the created node to the
// appropriate node of other values.
void IneqGraph::addEdgesFor(Instruction *I) {
  if (I->getType()->isPointerTy())
    return;

  Range RI = RA->getRange(I);
  if (!RI.getLower().isMinSignedValue())
    addMayEdge(AlfaConst, I, -RI.getLower().getSExtValue());
  if (!RI.getUpper().isMaxSignedValue())
    addMayEdge(I, AlfaConst, RI.getUpper().getSExtValue());

  // TODO: Handle multiplication, remainder and division instructions.
  switch (I->getOpcode()) {
    case Instruction::SExt:
    case Instruction::ZExt:
    case Instruction::Trunc:
    case Instruction::BitCast:
      addMayEdge(I, I->getOperand(0), 0);
      addMayEdge(I->getOperand(0), I, 0);
      break;
    case Instruction::Add:
      // a = b + c
      // ==> a <= b + sup(c)
      // ==> a <= c + sup(b)
      // ==> b <= a - inf(c)
      // ==> c <= a - inf(b)
      {
        Value *A = I->getOperand(0);
        Value *B = I->getOperand(1);
        Range AR = RA->getRange(A);
        Range BR = RA->getRange(B);
        if (!isa<ConstantInt>(B) && !AR.getUpper().isMaxSignedValue())
          addMayEdge(I, B, AR.getUpper());
        if (!isa<ConstantInt>(A) && !BR.getUpper().isMaxSignedValue())
          addMayEdge(I, A, BR.getUpper());
        if (!isa<ConstantInt>(A) && !BR.getLower().isMinSignedValue())
          addMayEdge(A, I, -BR.getUpper());
        if (!isa<ConstantInt>(B) && !AR.getLower().isMinSignedValue())
          addMayEdge(B, I, -AR.getUpper());
        break;
      }
    case Instruction::Sub:
      // a = b - c
      // ==> a <= b - inf(c)
      {
        Value *A = I->getOperand(0);
        Value *B = I->getOperand(1);
        Range AR = RA->getRange(A);
        Range BR = RA->getRange(B);
        if (!isa<ConstantInt>(A) && !BR.getLower().isMinSignedValue())
          addMayEdge(I, A, -BR.getLower());
        break;
      }
    case Instruction::Br:
      // if (a > b) {
      //   a1 = sigma(a)
      //   b1 = sigma(b)
      {      
        BranchInst *BI = cast<BranchInst>(I);
        ICmpInst *Cmp = dyn_cast<ICmpInst>(I->getOperand(0));
        if (!Cmp)
          break;
        Value *L = Cmp->getOperand(0);
        DEBUG(dbgs() << "IneqGraph: L: " << *L << "\n");
        Value *R = Cmp->getOperand(1);
        DEBUG(dbgs() << "IneqGraph: R: " << *R << "\n");
        Value *LSigma = VS->findSigma(L, BI->getSuccessor(0), BI->getParent());
        DEBUG(dbgs() << "IneqGraph: LSigma: " << *LSigma << "\n");
        Value *RSigma = VS->findSigma(R, BI->getSuccessor(0), BI->getParent());
        DEBUG(dbgs() << "IneqGraph: RSigma: " << *RSigma << "\n");
        Value *LSExtSigma = VS->findSExtSigma(L, BI->getSuccessor(0), BI->getParent());
        DEBUG(dbgs() << "IneqGraph: LSExtSigma: " << *LSExtSigma << "\n");
        Value *RSExtSigma = VS->findSExtSigma(R, BI->getSuccessor(0), BI->getParent());
        DEBUG(dbgs() << "IneqGraph: RSExtSigma: " << *RSExtSigma << "\n");
        switch (Cmp->getPredicate()) {
          case ICmpInst::ICMP_SLT:
            DEBUG(dbgs() << "IneqGraph: SLT:\n");
            if (!isa<ConstantInt>(R) && LSigma) {
              if (RSigma)
                addMayEdge(LSigma, RSigma, -1);
              if (RSExtSigma)
                addMayEdge(LSigma, RSExtSigma, -1);
            }
            if (!isa<ConstantInt>(R) && LSExtSigma && LSExtSigma != LSigma) {
              if (RSigma)
                addMayEdge(LSExtSigma, RSigma, -1);
              if (RSExtSigma)
                addMayEdge(LSExtSigma, RSExtSigma, -1);
            }
            break;
          case ICmpInst::ICMP_SLE:
            DEBUG(dbgs() << "IneqGraph: SLE:\n");
            if (!isa<ConstantInt>(R) && LSigma && RSigma)
              addMayEdge(LSigma, RSigma, 0);
            if (!isa<ConstantInt>(R) && (LSExtSigma != LSigma || RSExtSigma != RSigma))
              addMayEdge(LSExtSigma, RSExtSigma, 0);
            break;
          default:
            break;
        }
        break;
      }
    case Instruction::PHI:
      {
        PHINode *Phi = cast<PHINode>(I);
        for (unsigned Idx = 0; Idx < Phi->getNumIncomingValues(); ++Idx) {
          addMustEdge(Phi, Phi->getIncomingValue(Idx), 0);
        }
        break;
      }
    case Instruction::Call:
      {
        CallInst *CI = cast<CallInst>(I);
        if (Function *F = CI->getCalledFunction()) {
          unsigned Idx = 0;
          for (Function::arg_iterator AI = F->arg_begin(), AE = F->arg_end();
               AI != AE; ++AI, ++Idx) {
            addMustEdge(&(*AI), CI->getArgOperand(Idx), 0);
          }
        }
        break;
      }
  }
}