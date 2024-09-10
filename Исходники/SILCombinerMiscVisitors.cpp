/// Simplify the following two frontend patterns:
///
///   %payload_addr = init_enum_data_addr %payload_allocation
///   store %payload to %payload_addr
///   inject_enum_addr %payload_allocation, $EnumType.case
///
///   inject_enum_add %nopayload_allocation, $EnumType.case
///
/// for a concrete enum type $EnumType.case to:
///
///   %1 = enum $EnumType, $EnumType.case, %payload
///   store %1 to %payload_addr
///
///   %1 = enum $EnumType, $EnumType.case
///   store %1 to %nopayload_addr
///
/// We leave the cleaning up to mem2reg.
SILInstruction *
SILCombiner::visitInjectEnumAddrInst(InjectEnumAddrInst *IEAI) {
  // Given an inject_enum_addr of a concrete type without payload, promote it to
  // a store of an enum. Mem2reg/load forwarding will clean things up for us. We
  // can't handle the payload case here due to the flow problems caused by the
  // dependency in between the enum and its data.

  assert(IEAI->getOperand()->getType().isAddress() && "Must be an address");
  Builder.setCurrentDebugScope(IEAI->getDebugScope());

  if (IEAI->getOperand()->getType().isAddressOnly(IEAI->getModule())) {
    // Check for the following pattern inside the current basic block:
    // inject_enum_addr %payload_allocation, $EnumType.case1
    // ... no insns storing anything into %payload_allocation
    // select_enum_addr  %payload_allocation,
    //                   case $EnumType.case1: %Result1,
    //                   case case $EnumType.case2: %bResult2
    //                   ...
    //
    // Replace the select_enum_addr by %Result1

    auto *Term = IEAI->getParent()->getTerminator();
    if (isa<CondBranchInst>(Term) || isa<SwitchValueInst>(Term)) {
      auto BeforeTerm = std::prev(std::prev(IEAI->getParent()->end()));
      auto *SEAI = dyn_cast<SelectEnumAddrInst>(BeforeTerm);
      if (!SEAI)
        return nullptr;

      if (SEAI->getOperand() != IEAI->getOperand())
        return nullptr;

      SILBasicBlock::iterator II = IEAI->getIterator();
      StoreInst *SI = nullptr;
      for (;;) {
        SILInstruction *CI = &*II;
        if (CI == SEAI)
          break;
        ++II;
        SI = dyn_cast<StoreInst>(CI);
        if (SI) {
          if (SI->getDest() == IEAI->getOperand())
            return nullptr;
        }
        // Allow all instructions in between, which don't have any dependency to
        // the store.
        if (AA->mayWriteToMemory(&*II, IEAI->getOperand()))
          return nullptr;
      }

      auto *InjectedEnumElement = IEAI->getElement();
      auto Result = SEAI->getCaseResult(InjectedEnumElement);

      // Replace select_enum_addr by the result
      replaceInstUsesWith(*SEAI, Result);
      return nullptr;
    }

    // Check for the following pattern inside the current basic block:
    // inject_enum_addr %payload_allocation, $EnumType.case1
    // ... no insns storing anything into %payload_allocation
    // switch_enum_addr  %payload_allocation,
    //                   case $EnumType.case1: %bbX,
    //                   case case $EnumType.case2: %bbY
    //                   ...
    //
    // Replace the switch_enum_addr by select_enum_addr, switch_value.
    if (auto *SEI = dyn_cast<SwitchEnumAddrInst>(Term)) {
      if (SEI->getOperand() != IEAI->getOperand())
        return nullptr;

      SILBasicBlock::iterator II = IEAI->getIterator();
      StoreInst *SI = nullptr;
      for (;;) {
        SILInstruction *CI = &*II;
        if (CI == SEI)
          break;
        ++II;
        SI = dyn_cast<StoreInst>(CI);
        if (SI) {
          if (SI->getDest() == IEAI->getOperand())
            return nullptr;
        }
        // Allow all instructions in between, which don't have any dependency to
        // the store.
        if (AA->mayWriteToMemory(&*II, IEAI->getOperand()))
          return nullptr;
      }

      // Replace switch_enum_addr by a branch instruction.
      SILBuilderWithScope B(SEI);
      SmallVector<std::pair<EnumElementDecl *, SILValue>, 8> CaseValues;
      SmallVector<std::pair<SILValue, SILBasicBlock *>, 8> CaseBBs;

      auto IntTy = SILType::getBuiltinIntegerType(32, B.getASTContext());

      for (int i = 0, e = SEI->getNumCases(); i < e; ++i) {
        auto Pair = SEI->getCase(i);
        auto *IL = B.createIntegerLiteral(SEI->getLoc(), IntTy, APInt(32, i, false));
        SILValue ILValue = SILValue(IL);
        CaseValues.push_back(std::make_pair(Pair.first, ILValue));
        CaseBBs.push_back(std::make_pair(ILValue, Pair.second));
      }

      SILValue DefaultValue;
      SILBasicBlock *DefaultBB = nullptr;

      if (SEI->hasDefault()) {
        auto *IL = B.createIntegerLiteral(
          SEI->getLoc(), IntTy,
          APInt(32, static_cast<uint64_t>(SEI->getNumCases()), false));
        DefaultValue = SILValue(IL);
        DefaultBB = SEI->getDefaultBB();
      }

      auto *SEAI = B.createSelectEnumAddr(SEI->getLoc(), SEI->getOperand(), IntTy, DefaultValue, CaseValues);

      B.createSwitchValue(SEI->getLoc(), SILValue(SEAI), DefaultBB, CaseBBs);

      return eraseInstFromFunction(*SEI);
    }

    return nullptr;
  }

  // If the enum does not have a payload create the enum/store since we don't
  // need to worry about payloads.
  if (!IEAI->getElement()->hasArgumentType()) {
    EnumInst *E =
      Builder.createEnum(IEAI->getLoc(), SILValue(), IEAI->getElement(),
                          IEAI->getOperand()->getType().getObjectType());
    Builder.createStore(IEAI->getLoc(), E, IEAI->getOperand(),
                        StoreOwnershipQualifier::Unqualified);
    return eraseInstFromFunction(*IEAI);
  }

  // Ok, we have a payload enum, make sure that we have a store previous to
  // us...
  SILValue ASO = IEAI->getOperand();
  if (!isa<AllocStackInst>(ASO)) {
    return nullptr;
  }
  InitEnumDataAddrInst *DataAddrInst = nullptr;
  InjectEnumAddrInst *EnumAddrIns = nullptr;
  llvm::SmallPtrSet<SILInstruction *, 32> WriteSet;
  for (auto UsersIt : ASO->getUses()) {
    SILInstruction *CurrUser = UsersIt->getUser();
    if (CurrUser->isDeallocatingStack()) {
      // we don't care about the dealloc stack instructions
      continue;
    }
    if (isDebugInst(CurrUser) || isa<LoadInst>(CurrUser)) {
      // These Instructions are a non-risky use we can ignore
      continue;
    }
    if (auto *CurrInst = dyn_cast<InitEnumDataAddrInst>(CurrUser)) {
      if (DataAddrInst) {
        return nullptr;
      }
      DataAddrInst = CurrInst;
      continue;
    }
    if (auto *CurrInst = dyn_cast<InjectEnumAddrInst>(CurrUser)) {
      if (EnumAddrIns) {
        return nullptr;
      }
      EnumAddrIns = CurrInst;
      continue;
    }
    if (isa<StoreInst>(CurrUser)) {
      // The only MayWrite Instruction we can safely handle
      WriteSet.insert(CurrUser);
      continue;
    }
    // It is too risky to continue if it is any other instruction.
    return nullptr;
  }

  if (!DataAddrInst || !EnumAddrIns) {
    return nullptr;
  }
  assert((EnumAddrIns == IEAI) &&
         "Found InitEnumDataAddrInst differs from IEAI");
  // Found the DataAddrInst to this enum payload. Check if it has only use.
  if (!hasOneNonDebugUse(DataAddrInst))
    return nullptr;

  StoreInst *SI = dyn_cast<StoreInst>(getSingleNonDebugUser(DataAddrInst));
  ApplyInst *AI = dyn_cast<ApplyInst>(getSingleNonDebugUser(DataAddrInst));
  if (!SI && !AI) {
    return nullptr;
  }

  // Make sure the enum pattern instructions are the only ones which write to
  // this location
  if (!WriteSet.empty()) {
    // Analyze the instructions (implicit dominator analysis)
    // If we find any of MayWriteSet, return nullptr
    SILBasicBlock *InitEnumBB = DataAddrInst->getParent();
    assert(InitEnumBB && "DataAddrInst is not in a valid Basic Block");
    llvm::SmallVector<SILInstruction *, 64> Worklist;
    Worklist.push_back(IEAI);
    llvm::SmallPtrSet<SILBasicBlock *, 16> Preds;
    Preds.insert(IEAI->getParent());
    while (!Worklist.empty()) {
      SILInstruction *CurrIns = Worklist.pop_back_val();
      SILBasicBlock *CurrBB = CurrIns->getParent();

      if (CurrBB->isEntry() && CurrBB != InitEnumBB) {
        // reached prologue without encountering the init bb
        return nullptr;
      }

      for (auto InsIt = ++CurrIns->getIterator().getReverse();
           InsIt != CurrBB->rend(); ++InsIt) {
        SILInstruction *Ins = &*InsIt;
        if (Ins == DataAddrInst) {
          // don't care about what comes before init enum in the basic block
          break;
        }
        if (WriteSet.count(Ins) != 0) {
          return nullptr;
        }
      }

      if (CurrBB == InitEnumBB) {
        continue;
      }

      // Go to predecessors and do all that again
      for (SILBasicBlock *Pred : CurrBB->getPredecessorBlocks()) {
        // If it's already in the set, then we've already queued and/or
        // processed the predecessors.
        if (Preds.insert(Pred).second) {
          Worklist.push_back(&*Pred->rbegin());
        }
      }
    }
  }

  if (SI) {
    assert((SI->getDest() == DataAddrInst) &&
           "Can't find StoreInst with DataAddrInst as its destination");
    // In that case, create the payload enum/store.
    EnumInst *E = Builder.createEnum(
        DataAddrInst->getLoc(), SI->getSrc(), DataAddrInst->getElement(),
        DataAddrInst->getOperand()->getType().getObjectType());
    Builder.createStore(DataAddrInst->getLoc(), E, DataAddrInst->getOperand(),
                        StoreOwnershipQualifier::Unqualified);
    // Cleanup.
    eraseInstFromFunction(*SI);
    eraseInstFromFunction(*DataAddrInst);
    return eraseInstFromFunction(*IEAI);
  }

  // Check whether we have an apply initializing the enum.
  //  %iedai = init_enum_data_addr %enum_addr
  //         = apply(%iedai,...)
  //  inject_enum_addr %enum_addr
  //
  // We can localize the store to an alloc_stack.
  // Allowing us to perform the same optimization as for the store.
  //
  //  %alloca = alloc_stack
  //            apply(%alloca,...)
  //  %load = load %alloca
  //  %1 = enum $EnumType, $EnumType.case, %load
  //  store %1 to %nopayload_addr
  //
  assert(AI && "Must have an apply");
  unsigned ArgIdx = 0;
  Operand *EnumInitOperand = nullptr;
  for (auto &Opd : AI->getArgumentOperands()) {
    // Found an apply that initializes the enum. We can optimize this by
    // localizing the initialization to an alloc_stack and loading from it.
    DataAddrInst = dyn_cast<InitEnumDataAddrInst>(Opd.get());
    if (DataAddrInst && DataAddrInst->getOperand() == IEAI->getOperand() &&
        ArgIdx < AI->getSubstCalleeType()->getNumIndirectResults()) {
      EnumInitOperand = &Opd;
      break;
    }
    ++ArgIdx;
  }

  if (!EnumInitOperand) {
    return nullptr;
  }

  // Localize the address access.
  Builder.setInsertionPoint(AI);
  auto *AllocStack = Builder.createAllocStack(DataAddrInst->getLoc(),
                                              EnumInitOperand->get()->getType());
  EnumInitOperand->set(AllocStack);
  Builder.setInsertionPoint(std::next(SILBasicBlock::iterator(AI)));
  SILValue Load(Builder.createLoad(DataAddrInst->getLoc(), AllocStack,
                                   LoadOwnershipQualifier::Unqualified));
  EnumInst *E = Builder.createEnum(
      DataAddrInst->getLoc(), Load, DataAddrInst->getElement(),
      DataAddrInst->getOperand()->getType().getObjectType());
  Builder.createStore(DataAddrInst->getLoc(), E, DataAddrInst->getOperand(),
                      StoreOwnershipQualifier::Unqualified);
  Builder.createDeallocStack(DataAddrInst->getLoc(), AllocStack);
  eraseInstFromFunction(*DataAddrInst);
  return eraseInstFromFunction(*IEAI);
}