/// updateCallSites - Update all sites that call F to use NF.
CallGraphNode *SRETPromotion::updateCallSites(Function *F, Function *NF) {
  CallGraph &CG = getAnalysis<CallGraph>();
  SmallVector<Value*, 16> Args;

  // Attributes - Keep track of the parameter attributes for the arguments.
  SmallVector<AttributeWithIndex, 8> ArgAttrsVec;

  // Get a new callgraph node for NF.
  CallGraphNode *NF_CGN = CG.getOrInsertFunction(NF);

  while (!F->use_empty()) {
    CallSite CS(*F->use_begin());
    Instruction *Call = CS.getInstruction();

    const AttrListPtr &PAL = F->getAttributes();
    // Add any return attributes.
    if (Attributes attrs = PAL.getRetAttributes())
      ArgAttrsVec.push_back(AttributeWithIndex::get(0, attrs));

    // Copy arguments, however skip first one.
    CallSite::arg_iterator AI = CS.arg_begin(), AE = CS.arg_end();
    Value *FirstCArg = *AI;
    ++AI;
    // 0th parameter attribute is reserved for return type.
    // 1th parameter attribute is for first 1st sret argument.
    unsigned ParamIndex = 2; 
    while (AI != AE) {
      Args.push_back(*AI); 
      if (Attributes Attrs = PAL.getParamAttributes(ParamIndex))
        ArgAttrsVec.push_back(AttributeWithIndex::get(ParamIndex - 1, Attrs));
      ++ParamIndex;
      ++AI;
    }

    // Add any function attributes.
    if (Attributes attrs = PAL.getFnAttributes())
      ArgAttrsVec.push_back(AttributeWithIndex::get(~0, attrs));
    
    AttrListPtr NewPAL = AttrListPtr::get(ArgAttrsVec.begin(), ArgAttrsVec.end());
    
    // Build new call instruction.
    Instruction *New;
    if (InvokeInst *II = dyn_cast<InvokeInst>(Call)) {
      New = InvokeInst::Create(NF, II->getNormalDest(), II->getUnwindDest(),
                               Args.begin(), Args.end(), "", Call);
      cast<InvokeInst>(New)->setCallingConv(CS.getCallingConv());
      cast<InvokeInst>(New)->setAttributes(NewPAL);
    } else {
      New = CallInst::Create(NF, Args.begin(), Args.end(), "", Call);
      cast<CallInst>(New)->setCallingConv(CS.getCallingConv());
      cast<CallInst>(New)->setAttributes(NewPAL);
      if (cast<CallInst>(Call)->isTailCall())
        cast<CallInst>(New)->setTailCall();
    }
    Args.clear();
    ArgAttrsVec.clear();
    New->takeName(Call);

    // Update the callgraph to know that the callsite has been transformed.
    CallGraphNode *CalleeNode = CG[Call->getParent()->getParent()];
    CalleeNode->removeCallEdgeFor(Call);
    CalleeNode->addCalledFunction(New, NF_CGN);
    
    // Update all users of sret parameter to extract value using extractvalue.
    for (Value::use_iterator UI = FirstCArg->use_begin(), 
           UE = FirstCArg->use_end(); UI != UE; ) {
      User *U2 = *UI++;
      CallInst *C2 = dyn_cast<CallInst>(U2);
      if (C2 && (C2 == Call))
        continue;
      
      GetElementPtrInst *UGEP = cast<GetElementPtrInst>(U2);
      ConstantInt *Idx = cast<ConstantInt>(UGEP->getOperand(2));
      Value *GR = ExtractValueInst::Create(New, Idx->getZExtValue(),
                                           "evi", UGEP);
      while(!UGEP->use_empty()) {
        // isSafeToUpdateAllCallers has checked that all GEP uses are
        // LoadInsts
        LoadInst *L = cast<LoadInst>(*UGEP->use_begin());
        L->replaceAllUsesWith(GR);
        L->eraseFromParent();
      }
      UGEP->eraseFromParent();
      continue;
    }
    Call->eraseFromParent();
  }
  
  return NF_CGN;
}