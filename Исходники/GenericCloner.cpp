void GenericCloner::populateCloned() {
  SILFunction *Cloned = getCloned();

  // Create arguments for the entry block.
  SILBasicBlock *OrigEntryBB = &*Original.begin();
  SILBasicBlock *ClonedEntryBB = Cloned->createBasicBlock();
  getBuilder().setInsertionPoint(ClonedEntryBB);

  llvm::SmallVector<AllocStackInst *, 8> AllocStacks;
  AllocStackInst *ReturnValueAddr = nullptr;

  // Create the entry basic block with the function arguments.
  auto origConv = Original.getConventions();
  unsigned ArgIdx = 0;
  for (auto &OrigArg : OrigEntryBB->getArguments()) {
    RegularLocation Loc((Decl *)OrigArg->getDecl());
    AllocStackInst *ASI = nullptr;
    SILType mappedType = remapType(OrigArg->getType());

    auto createAllocStack = [&]() {
      // We need an alloc_stack as a replacement for the indirect parameter.
      assert(mappedType.isAddress());
      mappedType = mappedType.getObjectType();
      ASI = getBuilder().createAllocStack(Loc, mappedType);
      ValueMap[OrigArg] = ASI;
      AllocStacks.push_back(ASI);
    };
    auto handleConversion = [&]() {
      if (!origConv.useLoweredAddresses())
        return false;

      if (ArgIdx < origConv.getSILArgIndexOfFirstParam()) {
        // Handle result arguments.
        unsigned formalIdx =
            origConv.getIndirectFormalResultIndexForSILArg(ArgIdx);
        if (ReInfo.isFormalResultConverted(formalIdx)) {
          // This result is converted from indirect to direct. The return inst
          // needs to load the value from the alloc_stack. See below.
          createAllocStack();
          assert(!ReturnValueAddr);
          ReturnValueAddr = ASI;
          return true;
        }
      } else {
        // Handle arguments for formal parameters.
        unsigned paramIdx = ArgIdx - origConv.getSILArgIndexOfFirstParam();
        if (ReInfo.isParamConverted(paramIdx)) {
          // Store the new direct parameter to the alloc_stack.
          createAllocStack();
          auto *NewArg = ClonedEntryBB->createFunctionArgument(
              mappedType, OrigArg->getDecl());
          getBuilder().createStore(Loc, NewArg, ASI,
                                   StoreOwnershipQualifier::Unqualified);

          // Try to create a new debug_value from an existing debug_value_addr.
          for (Operand *ArgUse : OrigArg->getUses()) {
            if (auto *DVAI = dyn_cast<DebugValueAddrInst>(ArgUse->getUser())) {
              getBuilder().setCurrentDebugScope(remapScope(DVAI->getDebugScope()));
              getBuilder().createDebugValue(DVAI->getLoc(), NewArg,
                                            DVAI->getVarInfo());
              getBuilder().setCurrentDebugScope(nullptr);
              break;
            }
          }
          return true;
        }
      }
      return false; // No conversion.
    };
    if (!handleConversion()) {
      auto *NewArg =
          ClonedEntryBB->createFunctionArgument(mappedType, OrigArg->getDecl());
      ValueMap[OrigArg] = NewArg;
    }
    ++ArgIdx;
  }

  BBMap.insert(std::make_pair(OrigEntryBB, ClonedEntryBB));
  // Recursively visit original BBs in depth-first preorder, starting with the
  // entry block, cloning all instructions other than terminators.
  visitSILBasicBlock(OrigEntryBB);

  // Now iterate over the BBs and fix up the terminators.
  for (auto BI = BBMap.begin(), BE = BBMap.end(); BI != BE; ++BI) {
    getBuilder().setInsertionPoint(BI->second);
    TermInst *OrigTermInst = BI->first->getTerminator();
    if (auto *RI = dyn_cast<ReturnInst>(OrigTermInst)) {
      SILValue ReturnValue;
      if (ReturnValueAddr) {
        // The result is converted from indirect to direct. We have to load the
        // returned value from the alloc_stack.
        ReturnValue =
            getBuilder().createLoad(ReturnValueAddr->getLoc(), ReturnValueAddr,
                                    LoadOwnershipQualifier::Unqualified);
      }
      for (AllocStackInst *ASI : reverse(AllocStacks)) {
        getBuilder().createDeallocStack(ASI->getLoc(), ASI);
      }
      if (ReturnValue) {
        getBuilder().createReturn(RI->getLoc(), ReturnValue);
        continue;
      }
    } else if (isa<ThrowInst>(OrigTermInst)) {
      for (AllocStackInst *ASI : reverse(AllocStacks)) {
        getBuilder().createDeallocStack(ASI->getLoc(), ASI);
      }
    }
    visit(BI->first->getTerminator());
  }
}