bool RangedAddressSanitizer::runOnFunction(Function &F) {
    if (getenv("FASAN_DISABLE")) {
      SPM_DEBUG( dbgs() << "FASan : disabled\n" );
      return false;
    }

    DL_  = &getAnalysis<DataLayout>();
    DT_  = &getAnalysis<DominatorTree>();
    LI_  = &getAnalysis<LoopInfo>();
    RI_  = &getAnalysis<ReduceIndexation>();
#ifdef ENABLE_REUSE
    RE_  = &getAnalysis<RelativeExecutions>();
#endif
    RMM_ = &getAnalysis<RelativeMinMax>();

    Module_  = F.getParent();
    Context_ = &Module_->getContext();

    Type        *VoidTy    = Type::getVoidTy(*Context_);
    IntegerType *IntTy     = IntegerType::getInt64Ty(*Context_);
    IntegerType *BoolTy     = IntegerType::getInt1Ty(*Context_);
    PointerType *IntPtrTy  = PointerType::getUnqual(IntTy);
    PointerType *VoidPtrTy = PointerType::getInt8PtrTy(*Context_);

    SPM_DEBUG( F.dump() );
    outs() << "[IterationInfo]\n";
    for (Loop * loop : *LI_) {
            ii_visitLoop(loop);
    }
    outs() << "[EndOfIterationInfo]\n";
    
#if 0 // disabled initialization,shutdown sequence for FASan
  if (F.getName() == "main") {
    SPM_DEBUG(dbgs() << "RangedAddressSanitizer: inserting hwloc calls into "
                        "main function\n");

    FunctionType *FnType = FunctionType::get(VoidTy, ArrayRef<Type*>(), false);
    IRBuilder<> IRB(&(*F.getEntryBlock().begin()));

    Constant *Init = Module_->getOrInsertFunction("__spm_init", FnType);
    IRB.CreateCall(Init);

    Constant *End = Module_->getOrInsertFunction("__spm_end", FnType);
    for (auto &BB : F) {
      TerminatorInst *TI = BB.getTerminator();
      if (isa<ReturnInst>(TI)) {
        IRB.SetInsertPoint(TI);
        IRB.CreateCall(End);
      }
    }
  }
#endif

  if (!ClFunc.empty() && F.getName() != ClFunc) {
    SPM_DEBUG(dbgs() << "RangedAddressSanitizer: skipping function "
                     << F.getName() << "\n");
    return false;
  }

  Calls_.clear();

  SPM_DEBUG(dbgs() << "RangedAddressSanitizer: processing function "
                   << F.getName() << "\n");

  std::vector<Type*> ReuseFnFormals = { VoidPtrTy, IntTy, IntTy, IntTy };
  FunctionType *ReuseFnType = FunctionType::get(BoolTy, ReuseFnFormals, false);
  ReuseFn_ =
    F.getParent()->getOrInsertFunction("__fasan_check", ReuseFnType);
  ReuseFnDestroy_ =
    F.getParent()->getOrInsertFunction("__spm_give", ReuseFnType);

// Visit all loops in bottom-up order (innter-most loops first)
  std::set<BasicBlock*> Processed;
  auto Entry = DT_->getRootNode();
  for (auto ET = po_begin(Entry), EE = po_end(Entry); ET != EE; ++ET) {
    BasicBlock *Header = (*ET)->getBlock();

    if (LI_->isLoopHeader(Header)) {
      SPM_DEBUG(dbgs() << "RangedAddressSanitizer: processing loop at "
                       << Header->getName() << "\n");
      Loop *L = LI_->getLoopFor(Header);

      if (L->getNumBackEdges() != 1 ||
          std::distance(pred_begin(Header), pred_end(Header)) != 2) {
        SPM_DEBUG(dbgs() << "RangedAddressSanitizer: loop has multiple "
                         << "backedges or multiple incoming outer blocks\n");
        continue;
      }

      SPM_DEBUG(dbgs() << "RangedAddressSanitizer: processing loop at "
                       << Header->getName() << "\n");

    // visit all memory acccesses in this loop
      for (auto BB = L->block_begin(), BE = L->block_end(); BB != BE; ++BB) {
        if (!Processed.count(*BB)) {
          Processed.insert(*BB);
          for (auto &I : *(*BB))
            generateCallFor(L, &I);
        }
      }
    }
  }

  // FAsan logic goes here

  std::map<const BasicBlock*,BasicBlock*> clonedBlockMap; // keeps track of cloned regions to avoid redundant cloning

  std::vector<CallInst*> ToInline;

  for (auto &CI : Calls_) {
    BasicBlock * Preheader = CI.Preheader;
    
  // TODO decide whether it is worthwhile to optimize for this case

  // insert range check
    IRBuilder<> IRB(Preheader->getTerminator());
    Value *VoidArray = IRB.CreateBitCast(CI.Array, VoidPtrTy);
    std::vector<Value*> Args = { VoidArray, CI.Min, CI.Max, CI.Reuse };
    CallInst *CR = IRB.CreateCall(ReuseFn_, Args);
    ToInline.push_back(CR);
    
 // verify if this loop was already instrumented
    TerminatorInst * preHeaderTerm = CR->getParent()->getTerminator();
    BranchInst * preHeaderBranch = dyn_cast<BranchInst>(preHeaderTerm);

    if (preHeaderBranch && preHeaderBranch->isConditional()) {

    // discover the structure of the instrumented code (safe and default region)
    // abort, if this does not look like instrumented code
    	BasicBlock * firstTarget = preHeaderBranch->getSuccessor(0);
    	BasicBlock * secondTarget = preHeaderBranch->getSuccessor(1);
    	BasicBlock * safeHeader, * defHeader;
    	if (clonedBlockMap.count(firstTarget)) {
    		defHeader = firstTarget;
    		safeHeader = clonedBlockMap[firstTarget];
    		assert(safeHeader == secondTarget);
    	} else {
    		assert(clonedBlockMap.count(secondTarget));
    		defHeader = secondTarget;
			safeHeader = clonedBlockMap[secondTarget];
			assert(safeHeader == firstTarget);
    	}

    	SPM_DEBUG( dbgs() << "FASan: (Unsupported) second array in safe region controlled by " << * preHeaderBranch << "\n" );
    	Loop * defLoop = LI_->getLoopFor(defHeader);
    	assert(defLoop && "default region is not a loop!");

		Loop::block_iterator itBodyBlock,S,E;
		S = defLoop->block_begin();
		E = defLoop->block_end();

	// mark accesses in cloned region as safe
    	for (itBodyBlock = S;itBodyBlock != E; ++itBodyBlock) {
    		BasicBlock * defBodyBlock = *itBodyBlock;
    		BasicBlock * safeBodyBlock = clonedBlockMap[defBodyBlock];

    		for(auto & inst : *safeBodyBlock) {
				markSafeArrayUse(&inst, CI.Array);
			}
    	}

    // add conjunctive test
    	Value * oldCond = preHeaderBranch->getCondition();
    	Value * joinedCond = IRB.CreateAnd(oldCond, CR, "allsafe");
    	preHeaderBranch->setCondition(joinedCond);

    } else {

	  // get loop
		Loop* finalLoop = CI.FinalLoop;
		Loop::block_iterator itBodyBlock,S,E;
		S = finalLoop->block_begin();
		E = finalLoop->block_end();

	  // clone loop body (cloned loop will run unchecked)
		ValueToValueMapTy cloneMap;

		BasicBlock * clonedHeader = 0;
		std::vector<BasicBlock*> clonedBlocks;

		for (itBodyBlock = S;itBodyBlock != E; ++itBodyBlock) {

			const BasicBlock * bodyBlock = *itBodyBlock;
			BasicBlock * clonedBlock = CloneBasicBlock(bodyBlock, cloneMap, "_checked", &F, 0);

			cloneMap[bodyBlock] = clonedBlock;
			clonedBlockMap[bodyBlock] = clonedBlock;
			clonedBlocks.push_back(clonedBlock);

			if (bodyBlock == finalLoop->getHeader()) {
				clonedHeader = clonedBlock;
				SPM_DEBUG( dbgs() << "FASan: loop header case at " << bodyBlock->getName() << "\n" );
			} else {
				SPM_DEBUG( dbgs() << "FASan: non-header block at " << bodyBlock->getName() << "\n" );
			}
		}

		if (!clonedHeader) {
			// TODO run clean-up code
			SPM_DEBUG( dbgs() << "FASan: could not find header!\n");
			abort();
		}

	  // Remap uses inside cloned region (mark pointers in the region as unguarded)
		for (BasicBlock * block : clonedBlocks) {
			for(auto & inst : *block) {
				RemapInstruction(&inst, cloneMap, RF_IgnoreMissingEntries);
				markSafeArrayUse(&inst, CI.Array);
			}
		}

	   // TODO fix PHI-nodes in exit blocks

	   // Rewire terminator of the range check to branch to the cloned region
		TerminatorInst * checkTermInst = CR->getParent()->getTerminator();

		if (BranchInst * checkBranchInst = dyn_cast<BranchInst>(checkTermInst)) {
			if (checkBranchInst->isUnconditional()) {
				BasicBlock * defTarget = checkBranchInst->getSuccessor(0);
				BranchInst * modifiedBranchInst = BranchInst::Create(clonedHeader, defTarget, CR, checkBranchInst);
				checkBranchInst->replaceAllUsesWith(modifiedBranchInst);
				checkBranchInst->eraseFromParent();
			} else {
				SPM_DEBUG( dbgs() << "FASan: Unexpected conditional branch (preheader should branch unconditional, other array checks will introduce conditional branches) " << * checkTermInst << "\n" );
				abort();
			}
		} else {
			SPM_DEBUG( dbgs() << "FASan: unsupported terminator type " << * checkTermInst << "\n" );
			abort();
		}
    }
    
#if 0
    IRB.SetInsertPoint(&(*CI.Final->begin()));
    IRB.CreateCall(ReuseFnDestroy_, Args);
#endif
    SPM_DEBUG(dbgs() << "RangedAddressSanitizer: call instruction: " << *CR
                     << "\n");
  }


  // inline calls
#ifdef FASAN_INLINE_RUNTIME
  for (CallInst * call : ToInline) {
	assert(call);
	InlineFunctionInfo IFI;
	InlineFunction(call, IFI, false);
  }
#endif

  SPM_DEBUG( F.dump() );
  return true;
}