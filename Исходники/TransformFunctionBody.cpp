//
// Method: visitCallSite()
//
// Description:
//  This method transforms a call site.  A call site may either be a call
//  instruction or an invoke instruction.
//
// Inputs:
//  CS - The call site representing the instruction that should be transformed.
//
void FuncTransform::visitCallSite(CallSite& CS) {
  const Function *CF = CS.getCalledFunction();
  Instruction *TheCall = CS.getInstruction();
  bool thread_creation_point = false;

  //
  // Get the value that is called at this call site.  Strip away any pointer
  // casts that do not change the representation of the data (i.e., are
  // lossless casts).
  //
  Value * CalledValue = CS.getCalledValue()->stripPointerCasts();

  //
  // The CallSite::getCalledFunction() method is not guaranteed to strip off
  // pointer casts.  If no called function was found, manually strip pointer
  // casts off of the called value and see if we get a function.  If so, this
  // is a direct call, and we want to update CF accordingly.
  //
  if (!CF) CF = dyn_cast<Function>(CalledValue);

  //
  // Do not change any inline assembly code.
  //
  if (isa<InlineAsm>(TheCall->getOperand(0))) {
    errs() << "INLINE ASM: ignoring.  Hoping that's safe.\n";
    return;
  }

  //
  // Ignore calls to NULL pointers or undefined values.
  //
  if ((isa<ConstantPointerNull>(CalledValue)) ||
      (isa<UndefValue>(CalledValue))) {
    errs() << "WARNING: Ignoring call using NULL/Undef function pointer.\n";
    return;
  }

  // If this function is one of the memory manipulating functions built into
  // libc, emulate it with pool calls as appropriate.
  if (CF && CF->isDeclaration()) {
    std::string Name = CF->getName();

    if (Name == "free" || Name == "cfree") {
      visitFreeCall(CS);
      return;
    } else if (Name == "malloc") {
      visitMallocCall(CS);
      return;
    } else if (Name == "calloc") {
      visitCallocCall(CS);
      return;
    } else if (Name == "realloc") {
      visitReallocCall(CS);
      return;
    } else if (Name == "memalign" || Name == "posix_memalign") {
      visitMemAlignCall(CS);
      return;
    } else if (Name == "strdup") {
      visitStrdupCall(CS);
      return;
    } else if (Name == "valloc") {
      errs() << "VALLOC USED BUT NOT HANDLED!\n";
      abort();
    } else if (unsigned PoolArgc = PAInfo.getNumInitialPoolArguments(Name)) {
      visitRuntimeCheck(CS, PoolArgc);
      return;
    } else if (Name == "pthread_create") {
      thread_creation_point = true;

      //
      // Get DSNode representing the DSNode of the function pointer Value of
      // the pthread_create call
      //
      DSNode* thread_callee_node = G->getNodeForValue(CS.getArgument(2)).getNode();
      if (!thread_callee_node) {
    	  assert(0 && "apparently you need this code");
    	  FuncInfo *CFI = PAInfo.getFuncInfo(*CF);
    	  thread_callee_node = G->getNodeForValue(CFI->MapValueToOriginal(CS.getArgument(2))).getNode();
      }

      // Fill in CF with the name of one of the functions in thread_callee_node
      CF = const_cast<Function*>(dyn_cast<Function>(*thread_callee_node->globals_begin()));
    }
  }

  //
  // We need to figure out which local pool descriptors correspond to the pool
  // descriptor arguments passed into the function call.  Calculate a mapping
  // from callee DSNodes to caller DSNodes.  We construct a partial isomophism
  // between the graphs to figure out which pool descriptors need to be passed
  // in.  The roots of this mapping is found from arguments and return values.
  //
  DataStructures& Graphs = PAInfo.getGraphs();
  DSGraph::NodeMapTy NodeMapping;
  Instruction *NewCall;
  Value *NewCallee;
  std::vector<const DSNode*> ArgNodes;
  DSGraph *CalleeGraph;  // The callee graph

  // For indirect callees, find any callee since all DS graphs have been
  // merged.
  if (CF) {   // Direct calls are nice and simple.
    DEBUG(errs() << "  Handling direct call: " << *TheCall << "\n");

    //
    // Do not try to add pool handles to the function if it:
    //  a) Already calls a cloned function; or
    //  b) Calls a function which was never cloned.
    //
    // For such a call, just replace any arguments that take original functions
    // with their cloned function poiner values.
    //
    FuncInfo *CFI = PAInfo.getFuncInfo(*CF);
    if (CFI == 0 || CFI->Clone == 0) {   // Nothing to transform...
      visitInstruction(*TheCall);
      return;
    }

    //
    // Oh, dear.  We must add pool descriptors to this direct call.
    //
    NewCallee = CFI->Clone;
    ArgNodes = CFI->ArgNodes;
    
    assert ((Graphs.hasDSGraph (*CF)) && "Function has no ECGraph!\n");
    CalleeGraph = Graphs.getDSGraph(*CF);
  } else {
    DEBUG(errs() << "  Handling indirect call: " << *TheCall << "\n");
    DSGraph *G =  Graphs.getGlobalsGraph();
    DSGraph::ScalarMapTy& SM = G->getScalarMap();

    // Here we fill in CF with one of the possible called functions.  Because we
    // merged together all of the arguments to all of the functions in the
    // equivalence set, it doesn't really matter which one we pick.
    // (If the function was cloned, we have to map the cloned call instruction
    // in CS back to the original call instruction.)
    Instruction *OrigInst =
      cast<Instruction>(getOldValueIfAvailable(CS.getInstruction()));

    //
    // Attempt to get one of the function targets of this indirect call site by
    // looking at the call graph constructed by the points-to analysis.  Be
    // sure to use the original call site from the original function; the
    // points-to analysis has no information on the clones we've created.
    //
    // Also, look for the target that has the greatest number of arguments that
    // have associated DSNodes.  This ensures that we pass the maximum number
    // of pools possible and prevents us from eliding a pool because we're
    // examining a target that doesn't need it.
    //
    const DSCallGraph & callGraph = Graphs.getCallGraph();

    DSCallGraph::callee_iterator I = callGraph.callee_begin(OrigInst);
    for (; I != callGraph.callee_end(OrigInst); ++I) {
      for(DSCallGraph::scc_iterator sccii = callGraph.scc_begin(*I),
                           sccee = callGraph.scc_end(*I); sccii != sccee; ++sccii){
        if(SM.find(SM.getLeaderForGlobal(*sccii)) == SM.end())
          continue;
        //
        // Get the information for this function.  Since this is coming from
        // DSA, it should be an original function.
        //
        // This call site calls a function, that is not defined in this module
        if (!(Graphs.hasDSGraph(**sccii))) return;

        // For all other cases Func Info must exist.
        PAInfo.getFuncInfo(**sccii);

        //
        // If this target takes more DSNodes than the last one we found, then
        // make *this* target our canonical target.
        //
        CF = *sccii;
        break;
      }
    }
    if(!CF){
    const Function *F1 = OrigInst->getParent()->getParent();
    F1 = callGraph.sccLeader(&*F1);

    for(DSCallGraph::scc_iterator sccii = callGraph.scc_begin(F1),
                           sccee = callGraph.scc_end(F1); sccii != sccee; ++sccii){
        if(SM.find(SM.getLeaderForGlobal(*sccii)) == SM.end())
          continue;
        //
        // Get the information for this function.  Since this is coming from DSA,
        // it should be an original function.
        //
        // This call site calls a function, that is not defined in this module
        if (!(Graphs.hasDSGraph(**sccii))) return;
        // For all other cases Func Info must exist.
        PAInfo.getFuncInfo(**sccii);

        //
        // If this target takes more DSNodes than the last one we found, then
        // make *this* target our canonical target.
        //
        CF = *sccii;
      }
    }
    
    // Assuming the call graph is always correct. And if the call graph reports,
    // no callees, we can assume that it is right.
    //
    // If we didn't find the callee in the constructed call graph, try
    // checking in the DSNode itself.
    // This isn't ideal as it means that this call site didn't have inlining
    // happen.
    //

    //
    // If we still haven't been able to find a target function of the call site
    // to transform, do nothing.
    //
    // One may be tempted to think that we should always have at least one
    // target, but this is not true.  There are perfectly acceptable (but
    // strange) programs for which no function targets exist.  Function
    // pointers loaded from undef values, for example, will have no targets.
    //
    if (!CF) return;

    //
    // It's possible that this program has indirect call targets that are
    // not defined in this module.  Do not transformation for such functions.
    //
    if (!(Graphs.hasDSGraph(*CF))) return;

    //
    // Get the common graph for the set of functions this call may invoke.
    //
    assert ((Graphs.hasDSGraph(*CF)) && "Function has no DSGraph!\n");
    CalleeGraph = Graphs.getDSGraph(*CF);

#ifndef NDEBUG
    // Verify that all potential callees at call site have the same DS graph.
    DSCallGraph::callee_iterator E = Graphs.getCallGraph().callee_end(OrigInst);
    for (; I != E; ++I) {
      const Function * F = *I;
      assert (F);
      if (!(F)->isDeclaration())
        assert(CalleeGraph == Graphs.getDSGraph(**I) &&
               "Callees at call site do not have a common graph!");
    }
#endif    

    // Find the DS nodes for the arguments that need to be added, if any.
    FuncInfo *CFI = PAInfo.getFuncInfo(*CF);
    assert(CFI && "No function info for callee at indirect call?");
    ArgNodes = CFI->ArgNodes;

    if (ArgNodes.empty())
      return;           // No arguments to add?  Transformation is a noop!

    // Cast the function pointer to an appropriate type!
    std::vector<Type*> ArgTys(ArgNodes.size(),
                                    PoolAllocate::PoolDescPtrTy);
    for (CallSite::arg_iterator I = CS.arg_begin(), E = CS.arg_end();
         I != E; ++I)
      ArgTys.push_back((*I)->getType());
    
    FunctionType *FTy = FunctionType::get(TheCall->getType(), ArgTys, false);
    PointerType *PFTy = PointerType::getUnqual(FTy);
    
    // If there are any pool arguments cast the func ptr to the right type.
    NewCallee = CastInst::CreatePointerCast(CS.getCalledValue(), PFTy, "tmp", TheCall);
  }

  //
  // FIXME: Why do we disable strict checking when calling the
  //        DSGraph::computeNodeMapping() method?
  //
  Function::const_arg_iterator FAI = CF->arg_begin(), E = CF->arg_end();
  CallSite::arg_iterator AI = CS.arg_begin() + (thread_creation_point ? 3 : 0);
  CallSite::arg_iterator AE = CS.arg_end();
  for ( ; FAI != E && AI != AE; ++FAI, ++AI)
    if (!isa<Constant>(*AI)) {
      DSGraph::computeNodeMapping(CalleeGraph->getNodeForValue(FAI),
                                  getDSNodeHFor(*AI), NodeMapping, false);
    }

  //assert(AI == AE && "Varargs calls not handled yet!");

  // Map the return value as well...
  if (isa<PointerType>(TheCall->getType()))
    DSGraph::computeNodeMapping(CalleeGraph->getReturnNodeFor(*CF),
                                getDSNodeHFor(TheCall), NodeMapping, false);

  // This code seems redundant (and crashes occasionally)
  // There is no reason to map globals here, since they are not passed as
  // arguments

//   // Map the nodes that are pointed to by globals.
//    DSScalarMap &CalleeSM = CalleeGraph->getScalarMap();
//    for (DSScalarMap::global_iterator GI = G.getScalarMap().global_begin(), 
//           E = G.getScalarMap().global_end(); GI != E; ++GI)
//      if (CalleeSM.count(*GI))
//        DSGraph::computeNodeMapping(CalleeGraph->getNodeForValue(*GI),
//                                    getDSNodeHFor(*GI),
//                                    NodeMapping, false);

  //
  // Okay, now that we have established our mapping, we can figure out which
  // pool descriptors to pass in...
  //
  // Note:
  // There used to be code here that would create a new pool before the
  // function call and destroy it after the function call.  This could would
  // get triggered if bounds checking was disbled or the DSNode for the
  // argument was an array value.
  //
  // I believe that code was incorrect; an argument may have a NULL pool handle
  // (i.e., no pool handle) because the pool allocation heuristic used simply
  // decided not to assign that value a pool.  The argument may alias data
  // that should not be freed after the function call is complete, so calling
  // pooldestroy() after the call would free data, causing dangling pointer
  // dereference errors.
  //
  std::vector<Value*> Args;
  for (unsigned i = 0, e = ArgNodes.size(); i != e; ++i) {
    Value *ArgVal = Constant::getNullValue(PoolAllocate::PoolDescPtrTy);
    if (NodeMapping.count(ArgNodes[i])) {
      if (DSNode *LocalNode = NodeMapping[ArgNodes[i]].getNode())
        if (FI.PoolDescriptors.count(LocalNode))
          ArgVal = FI.PoolDescriptors.find(LocalNode)->second;
    }
    Args.push_back(ArgVal);
  }

  // Add the rest of the arguments unless we're a thread creation point, in which case we only need the pools
  if(!thread_creation_point)
	  Args.insert(Args.end(), CS.arg_begin(), CS.arg_end());
    
  //
  // There are circumstances where a function is casted to another type and
  // then called (que horible).  We need to perform a similar cast if the
  // type doesn't match the number of arguments.
  //
  if (Function * NewFunction = dyn_cast<Function>(NewCallee)) {
    FunctionType * NewCalleeType = NewFunction->getFunctionType();
    if (NewCalleeType->getNumParams() != Args.size()) {
      std::vector<Type *> Types;
      Type * FuncTy = FunctionType::get (NewCalleeType->getReturnType(),
                                         Types,
                                         true);
      FuncTy = PointerType::getUnqual (FuncTy);
      NewCallee = new BitCastInst (NewCallee, FuncTy, "", TheCall);
    }
  }

  std::string Name = TheCall->getName();    TheCall->setName("");

  if(thread_creation_point) {
	Module *M = CS.getInstruction()->getParent()->getParent()->getParent();
	Value* pthread_replacement = M->getFunction("poolalloc_pthread_create");
	std::vector<Value*> thread_args;

	//Push back original thread arguments through the callee
	thread_args.push_back(CS.getArgument(0));
	thread_args.push_back(CS.getArgument(1));
	thread_args.push_back(CS.getArgument(2));

	//Push back the integer argument saying how many uses there are
	thread_args.push_back(Constant::getIntegerValue(llvm::Type::getInt32Ty(M->getContext()),APInt(32,Args.size())));
	thread_args.insert(thread_args.end(),Args.begin(),Args.end());
	thread_args.push_back(CS.getArgument(3));

	//Make the thread creation call
	NewCall = CallInst::Create(pthread_replacement,
							   thread_args,
							   Name,TheCall);
  }
  else if (InvokeInst *II = dyn_cast<InvokeInst>(TheCall)) {
    NewCall = InvokeInst::Create (NewCallee, II->getNormalDest(),
                                  II->getUnwindDest(),
                                  Args, Name, TheCall);
  } else {
    NewCall = CallInst::Create (NewCallee, Args, Name,
                                TheCall);
  }

  // Add all of the uses of the pool descriptor
  for (unsigned i = 0, e = ArgNodes.size(); i != e; ++i)
    AddPoolUse(*NewCall, Args[i], PoolUses);

  TheCall->replaceAllUsesWith(NewCall);
  DEBUG(errs() << "  Result Call: " << *NewCall << "\n");

  if (!TheCall->getType()->isVoidTy()) {
    // If we are modifying the original function, update the DSGraph... 
    DSGraph::ScalarMapTy &SM = G->getScalarMap();
    DSGraph::ScalarMapTy::iterator CII = SM.find(TheCall);
    if (CII != SM.end()) {
      SM[NewCall] = CII->second;
      SM.erase(CII);                     // Destroy the CallInst
    } else if (!FI.NewToOldValueMap.empty()) {
      // Otherwise, if this is a clone, update the NewToOldValueMap with the new
      // CI return value.
      UpdateNewToOldValueMap(TheCall, NewCall);
    }
  } else if (!FI.NewToOldValueMap.empty()) {
    UpdateNewToOldValueMap(TheCall, NewCall);
  }

  //
  // Copy over the calling convention and attributes of the original call
  // instruction to the new call instruction.
  //
  CallSite(NewCall).setCallingConv(CallSite(TheCall).getCallingConv());

  TheCall->eraseFromParent();
  visitInstruction(*NewCall);
}