bool PPCLoopPreIncPrep::runOnLoop(Loop *L) {
  bool MadeChange = false;

  // Only prep. the inner-most loop
  if (!L->empty())
    return MadeChange;

  DEBUG(dbgs() << "PIP: Examining: " << *L << "\n");

  BasicBlock *Header = L->getHeader();

  const PPCSubtarget *ST =
    TM ? TM->getSubtargetImpl(*Header->getParent()) : nullptr;

  unsigned HeaderLoopPredCount =
    std::distance(pred_begin(Header), pred_end(Header));

  // Collect buckets of comparable addresses used by loads and stores.
  SmallVector<Bucket, 16> Buckets;
  for (Loop::block_iterator I = L->block_begin(), IE = L->block_end();
       I != IE; ++I) {
    for (BasicBlock::iterator J = (*I)->begin(), JE = (*I)->end();
        J != JE; ++J) {
      Value *PtrValue;
      Instruction *MemI;

      if (LoadInst *LMemI = dyn_cast<LoadInst>(J)) {
        MemI = LMemI;
        PtrValue = LMemI->getPointerOperand();
      } else if (StoreInst *SMemI = dyn_cast<StoreInst>(J)) {
        MemI = SMemI;
        PtrValue = SMemI->getPointerOperand();
      } else if (IntrinsicInst *IMemI = dyn_cast<IntrinsicInst>(J)) {
        if (IMemI->getIntrinsicID() == Intrinsic::prefetch) {
          MemI = IMemI;
          PtrValue = IMemI->getArgOperand(0);
        } else continue;
      } else continue;

      unsigned PtrAddrSpace = PtrValue->getType()->getPointerAddressSpace();
      if (PtrAddrSpace)
        continue;

      // There are no update forms for Altivec vector load/stores.
      if (ST && ST->hasAltivec() &&
          PtrValue->getType()->getPointerElementType()->isVectorTy())
        continue;

      if (L->isLoopInvariant(PtrValue))
        continue;

      const SCEV *LSCEV = SE->getSCEVAtScope(PtrValue, L);
      if (const SCEVAddRecExpr *LARSCEV = dyn_cast<SCEVAddRecExpr>(LSCEV)) {
        if (LARSCEV->getLoop() != L)
          continue;
      } else {
        continue;
      }

      bool FoundBucket = false;
      for (auto &B : Buckets) {
        const SCEV *Diff = SE->getMinusSCEV(LSCEV, B.BaseSCEV);
        if (const auto *CDiff = dyn_cast<SCEVConstant>(Diff)) {
          B.Elements.push_back(BucketElement(CDiff, MemI));
          FoundBucket = true;
          break;
        }
      }

      if (!FoundBucket) {
        if (Buckets.size() == MaxVars)
          return MadeChange;
        Buckets.push_back(Bucket(LSCEV, MemI));
      }
    }
  }

  if (Buckets.empty())
    return MadeChange;

  BasicBlock *LoopPredecessor = L->getLoopPredecessor();
  // If there is no loop predecessor, or the loop predecessor's terminator
  // returns a value (which might contribute to determining the loop's
  // iteration space), insert a new preheader for the loop.
  if (!LoopPredecessor ||
      !LoopPredecessor->getTerminator()->getType()->isVoidTy()) {
    LoopPredecessor = InsertPreheaderForLoop(L, DT, LI, PreserveLCSSA);
    if (LoopPredecessor)
      MadeChange = true;
  }
  if (!LoopPredecessor)
    return MadeChange;

  DEBUG(dbgs() << "PIP: Found " << Buckets.size() << " buckets\n");

  SmallSet<BasicBlock *, 16> BBChanged;
  for (unsigned i = 0, e = Buckets.size(); i != e; ++i) {
    // The base address of each bucket is transformed into a phi and the others
    // are rewritten as offsets of that variable.

    // We have a choice now of which instruction's memory operand we use as the
    // base for the generated PHI. Always picking the first instruction in each
    // bucket does not work well, specifically because that instruction might
    // be a prefetch (and there are no pre-increment dcbt variants). Otherwise,
    // the choice is somewhat arbitrary, because the backend will happily
    // generate direct offsets from both the pre-incremented and
    // post-incremented pointer values. Thus, we'll pick the first non-prefetch
    // instruction in each bucket, and adjust the recurrence and other offsets
    // accordingly. 
    for (int j = 0, je = Buckets[i].Elements.size(); j != je; ++j) {
      if (auto *II = dyn_cast<IntrinsicInst>(Buckets[i].Elements[j].Instr))
        if (II->getIntrinsicID() == Intrinsic::prefetch)
          continue;

      // If we'd otherwise pick the first element anyway, there's nothing to do.
      if (j == 0)
        break;

      // If our chosen element has no offset from the base pointer, there's
      // nothing to do.
      if (!Buckets[i].Elements[j].Offset ||
          Buckets[i].Elements[j].Offset->isZero())
        break;

      const SCEV *Offset = Buckets[i].Elements[j].Offset;
      Buckets[i].BaseSCEV = SE->getAddExpr(Buckets[i].BaseSCEV, Offset);
      for (auto &E : Buckets[i].Elements) {
        if (E.Offset)
          E.Offset = cast<SCEVConstant>(SE->getMinusSCEV(E.Offset, Offset));
        else
          E.Offset = cast<SCEVConstant>(SE->getNegativeSCEV(Offset));
      }

      std::swap(Buckets[i].Elements[j], Buckets[i].Elements[0]);
      break;
    }

    const SCEVAddRecExpr *BasePtrSCEV =
      cast<SCEVAddRecExpr>(Buckets[i].BaseSCEV);
    if (!BasePtrSCEV->isAffine())
      continue;

    DEBUG(dbgs() << "PIP: Transforming: " << *BasePtrSCEV << "\n");
    assert(BasePtrSCEV->getLoop() == L &&
           "AddRec for the wrong loop?");

    // The instruction corresponding to the Bucket's BaseSCEV must be the first
    // in the vector of elements.
    Instruction *MemI = Buckets[i].Elements.begin()->Instr;
    Value *BasePtr = GetPointerOperand(MemI);
    assert(BasePtr && "No pointer operand");

    Type *I8Ty = Type::getInt8Ty(MemI->getParent()->getContext());
    Type *I8PtrTy = Type::getInt8PtrTy(MemI->getParent()->getContext(),
      BasePtr->getType()->getPointerAddressSpace());

    const SCEV *BasePtrStartSCEV = BasePtrSCEV->getStart();
    if (!SE->isLoopInvariant(BasePtrStartSCEV, L))
      continue;

    const SCEVConstant *BasePtrIncSCEV =
      dyn_cast<SCEVConstant>(BasePtrSCEV->getStepRecurrence(*SE));
    if (!BasePtrIncSCEV)
      continue;
    BasePtrStartSCEV = SE->getMinusSCEV(BasePtrStartSCEV, BasePtrIncSCEV);
    if (!isSafeToExpand(BasePtrStartSCEV, *SE))
      continue;

    DEBUG(dbgs() << "PIP: New start is: " << *BasePtrStartSCEV << "\n");

    PHINode *NewPHI = PHINode::Create(I8PtrTy, HeaderLoopPredCount,
      MemI->hasName() ? MemI->getName() + ".phi" : "",
      Header->getFirstNonPHI());

    SCEVExpander SCEVE(*SE, Header->getModule()->getDataLayout(), "pistart");
    Value *BasePtrStart = SCEVE.expandCodeFor(BasePtrStartSCEV, I8PtrTy,
      LoopPredecessor->getTerminator());

    // Note that LoopPredecessor might occur in the predecessor list multiple
    // times, and we need to add it the right number of times.
    for (pred_iterator PI = pred_begin(Header), PE = pred_end(Header);
         PI != PE; ++PI) {
      if (*PI != LoopPredecessor)
        continue;

      NewPHI->addIncoming(BasePtrStart, LoopPredecessor);
    }

    Instruction *InsPoint = &*Header->getFirstInsertionPt();
    GetElementPtrInst *PtrInc = GetElementPtrInst::Create(
        I8Ty, NewPHI, BasePtrIncSCEV->getValue(),
        MemI->hasName() ? MemI->getName() + ".inc" : "", InsPoint);
    PtrInc->setIsInBounds(IsPtrInBounds(BasePtr));
    for (pred_iterator PI = pred_begin(Header), PE = pred_end(Header);
         PI != PE; ++PI) {
      if (*PI == LoopPredecessor)
        continue;

      NewPHI->addIncoming(PtrInc, *PI);
    }

    Instruction *NewBasePtr;
    if (PtrInc->getType() != BasePtr->getType())
      NewBasePtr = new BitCastInst(PtrInc, BasePtr->getType(),
        PtrInc->hasName() ? PtrInc->getName() + ".cast" : "", InsPoint);
    else
      NewBasePtr = PtrInc;

    if (Instruction *IDel = dyn_cast<Instruction>(BasePtr))
      BBChanged.insert(IDel->getParent());
    BasePtr->replaceAllUsesWith(NewBasePtr);
    RecursivelyDeleteTriviallyDeadInstructions(BasePtr);

    // Keep track of the replacement pointer values we've inserted so that we
    // don't generate more pointer values than necessary.
    SmallPtrSet<Value *, 16> NewPtrs;
    NewPtrs.insert( NewBasePtr);

    for (auto I = std::next(Buckets[i].Elements.begin()),
         IE = Buckets[i].Elements.end(); I != IE; ++I) {
      Value *Ptr = GetPointerOperand(I->Instr);
      assert(Ptr && "No pointer operand");
      if (NewPtrs.count(Ptr))
        continue;

      Instruction *RealNewPtr;
      if (!I->Offset || I->Offset->getValue()->isZero()) {
        RealNewPtr = NewBasePtr;
      } else {
        Instruction *PtrIP = dyn_cast<Instruction>(Ptr);
        if (PtrIP && isa<Instruction>(NewBasePtr) &&
            cast<Instruction>(NewBasePtr)->getParent() == PtrIP->getParent())
          PtrIP = nullptr;
        else if (isa<PHINode>(PtrIP))
          PtrIP = &*PtrIP->getParent()->getFirstInsertionPt();
        else if (!PtrIP)
          PtrIP = I->Instr;

        GetElementPtrInst *NewPtr = GetElementPtrInst::Create(
            I8Ty, PtrInc, I->Offset->getValue(),
            I->Instr->hasName() ? I->Instr->getName() + ".off" : "", PtrIP);
        if (!PtrIP)
          NewPtr->insertAfter(cast<Instruction>(PtrInc));
        NewPtr->setIsInBounds(IsPtrInBounds(Ptr));
        RealNewPtr = NewPtr;
      }

      if (Instruction *IDel = dyn_cast<Instruction>(Ptr))
        BBChanged.insert(IDel->getParent());

      Instruction *ReplNewPtr;
      if (Ptr->getType() != RealNewPtr->getType()) {
        ReplNewPtr = new BitCastInst(RealNewPtr, Ptr->getType(),
          Ptr->hasName() ? Ptr->getName() + ".cast" : "");
        ReplNewPtr->insertAfter(RealNewPtr);
      } else
        ReplNewPtr = RealNewPtr;

      Ptr->replaceAllUsesWith(ReplNewPtr);
      RecursivelyDeleteTriviallyDeadInstructions(Ptr);

      NewPtrs.insert(RealNewPtr);
    }

    MadeChange = true;
  }

  for (Loop::block_iterator I = L->block_begin(), IE = L->block_end();
       I != IE; ++I) {
    if (BBChanged.count(*I))
      DeleteDeadPHIs(*I);
  }

  return MadeChange;
}