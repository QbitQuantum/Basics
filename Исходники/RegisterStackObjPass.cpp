//
// Function: insertPoolFrees()
//
// Description:
//  This function takes a list of alloca instructions and inserts code to
//  unregister them at every unwind and return instruction.
//
// Inputs:
//  PoolRegisters - The list of calls to poolregister() inserted for stack
//                  objects.
//  ExitPoints    - The list of instructions that can cause the function to
//                  return.
//  Context       - The LLVM Context in which to insert instructions.
//
void
RegisterStackObjPass::insertPoolFrees
  (const std::vector<CallInst *> & PoolRegisters,
   const std::vector<Instruction *> & ExitPoints,
   LLVMContext * Context) {
  // List of alloca instructions we create to store the pointers to be
  // deregistered.
  std::vector<AllocaInst *> PtrList;

  // List of pool handles; this is a parallel array to PtrList
  std::vector<Value *> PHList;

  // The infamous void pointer type
  PointerType * VoidPtrTy = getVoidPtrType(*Context);

  //
  // Create alloca instructions for every registered alloca.  These will hold
  // a pointer to the registered stack objects and will be referenced by
  // poolunregister().
  //
  for (unsigned index = 0; index < PoolRegisters.size(); ++index) {
    //
    // Take the first element off of the worklist.
    //
    CallInst * CI = PoolRegisters[index];
    CallSite CS(CI);

    //
    // Get the pool handle and allocated pointer from the poolregister() call.
    //
    Value * PH  = CS.getArgument(0);
    Value * Ptr = CS.getArgument(1);

    //
    // Create a place to store the pointer returned from alloca.  Initialize it
    // with a null pointer.
    //
    BasicBlock & EntryBB = CI->getParent()->getParent()->getEntryBlock();
    Instruction * InsertPt = &(EntryBB.front());
    AllocaInst * PtrLoc = new AllocaInst (VoidPtrTy,
                                          Ptr->getName() + ".st",
                                          InsertPt);
    Value * NullPointer = ConstantPointerNull::get(VoidPtrTy);
    new StoreInst (NullPointer, PtrLoc, InsertPt);

    //
    // Store the registered pointer into the memory we allocated in the entry
    // block.
    //
    new StoreInst (Ptr, PtrLoc, CI);

    //
    // Record the alloca that stores the pointer to deregister.
    // Record the pool handle with it.
    //
    PtrList.push_back (PtrLoc);
    PHList.push_back (PH);
  }

  //
  // For each point where the function can exit, insert code to deregister all
  // stack objects.
  //
  for (unsigned index = 0; index < ExitPoints.size(); ++index) {
    //
    // Take the first element off of the worklist.
    //
    Instruction * Return = ExitPoints[index];

    //
    // Deregister each registered stack object.
    //
    for (unsigned i = 0; i < PtrList.size(); ++i) {
      //
      // Get the location holding the pointer and the pool handle associated
      // with it.
      //
      AllocaInst * PtrLoc = PtrList[i];
      Value * PH = PHList[i];

      //
      // Generate a load instruction to get the registered pointer.
      //
      LoadInst * Ptr = new LoadInst (PtrLoc, "", Return);

      //
      // Create the call to poolunregister().
      //
      std::vector<Value *> args;
      args.push_back (PH);
      args.push_back (Ptr);
      CallInst::Create (StackFree, args, "", Return);
    }
  }

  //
  // Lastly, promote the allocas we created into LLVM virtual registers.
  //
  PromoteMemToReg(PtrList, *DT);
}