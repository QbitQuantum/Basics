bool LAMPLoopProfiler::runOnLoop(Loop *Lp, LPPassManager &LPM) {
	BasicBlock *preHeader;
	BasicBlock *header;
	BasicBlock *latch;
	
	LdStCallCounter& lscnts = getAnalysis<LdStCallCounter>();
	
	if(!IDInitFlag)
	{
		loop_id = lscnts.getCountInsts()-1;	// first id will begin after instruction ids
		IDInitFlag = true;
	}
	
	SmallVector<BasicBlock*, 8> exitBlocks;			// assuming max 8 exit blocks.  Is this wise?
								// TRM 7/24/08 removed exiting blocks instrumentation
								  // in favor of placing iter end prior loop exit
	header = Lp->getHeader();
	preHeader = Lp->getLoopPreheader();
	latch = Lp->getLoopLatch();
	
	Lp->getExitBlocks(exitBlocks);
	
	Module *M = (header->getParent())->getParent();
	
	numLoops++;
	
	lscnts.num_loops = numLoops;
	
		// insert invocation function at end of preheader (called once prior to loop)
	const char* InvocName = "LAMP_loop_invocation";
	Constant *InvocFn = M->getOrInsertFunction(InvocName, llvm::Type::getVoidTy(M->getContext()), llvm::Type::getInt32Ty(M->getContext()), (Type *)0);
	std::vector<Value*> Args(1);
	Args[0] = ConstantInt::get(llvm::Type::getInt32Ty(M->getContext()), ++loop_id);
	
	
	if (!preHeader->empty())
		
		CallInst::Create(InvocFn, Args.begin(), Args.end(), "", (preHeader->getTerminator()));
	else
		CallInst::Create(InvocFn, Args.begin(), Args.end(), "", (preHeader));
	
	
		// insert iteration begin function at beginning of header (called each loop)
	const char* IterBeginName = "LAMP_loop_iteration_begin";
	Constant *IterBeginFn = M->getOrInsertFunction(IterBeginName, llvm::Type::getVoidTy(M->getContext()), (Type *)0);	
	
	// find insertion point (after PHI nodes) -KF 11/18/2008
	for (BasicBlock::iterator ii = header->begin(), ie = header->end(); ii != ie; ++ii) {
	  if (!isa<PHINode>(ii)) {
	    CallInst::Create(IterBeginFn, "", ii);
	    break;
	  }
	}
	
	// insert iteration at cannonical backedge.  exiting block insertions removed in favor of exit block
	const char* IterEndName = "LAMP_loop_iteration_end";
	Constant *IterEndFn = M->getOrInsertFunction(IterEndName, llvm::Type::getVoidTy(M->getContext()), (Type *)0);	
	
		// cannonical backedge
	if (!latch->empty())
			CallInst::Create(IterEndFn, "", (latch->getTerminator()));
		else
			CallInst::Create(IterEndFn, "", (latch));
	
	
		// insert loop end at beginning of exit blocks
	const char* LoopEndName = "LAMP_loop_exit";
	Constant *LoopEndFn = M->getOrInsertFunction(LoopEndName, llvm::Type::getVoidTy(M->getContext()), (Type *)0);	
		
	set <BasicBlock*> BBSet; 
	BBSet.clear();
	for(unsigned int i = 0; i != exitBlocks.size(); i++){		
			// this ordering places iteration end before loop exit
			// make sure not inserting the same exit block more than once for a loop -PC 2/5/2009
		if (BBSet.find(exitBlocks[i])!=BBSet.end()) continue;
		BBSet.insert(exitBlocks[i]);
			// find insertion point (after PHI nodes) -PC 2/2/2009  -TODO: there is some function to do this.
		BasicBlock::iterator ii =  exitBlocks[i]->begin();
	  while (isa<PHINode>(ii)) { ii++; }
		CallInst::Create(IterEndFn, "", ii);	// iter end placed before exit call
		CallInst::Create(LoopEndFn, "", ii);	// loop exiting
	}
  	
	//DOUT << "Num Loops Processed: " << numLoops << "  Loop ID: " << loop_id << std::endl;
	return true;	
}