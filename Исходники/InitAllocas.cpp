//
// Method: visitAllocaInst()
//
// Description:
//  This method instruments an alloca instruction so that it is zero'ed out
//  before any data is loaded from it.
//
void
InitAllocas::visitAllocaInst (AllocaInst & AI) {
  //
  // Scan for a place to insert the instruction to initialize the
  // allocated memory.
  //
  Instruction * InsertPt = getInsertionPoint (AI);

  //
  // Zero the alloca with a memset.  If this is done more efficiently with stores
  // SelectionDAG will lower it appropriately based on target information.
  //
  TargetData & TD = getAnalysis<TargetData>();

  //
  // Get various types that we'll need.
  //
  Type * Int1Type    = IntegerType::getInt1Ty(AI.getContext());
  Type * Int8Type    = IntegerType::getInt8Ty(AI.getContext());
  Type * Int32Type   = IntegerType::getInt32Ty(AI.getContext());
  Type * VoidPtrType = getVoidPtrType (AI.getContext());
  Type * AllocType = AI.getAllocatedType();

  //
  // Create a call to memset.
  //
  Module * M = AI.getParent()->getParent()->getParent();
  Function * Memset = cast<Function>(M->getFunction ("llvm.memset.p0i8.i32"));
  std::vector<Value *> args;
  args.push_back (castTo (&AI, VoidPtrType, AI.getName().str(), InsertPt));
  args.push_back (ConstantInt::get(Int8Type, 0));
  args.push_back (ConstantInt::get(Int32Type,TD.getTypeAllocSize(AllocType)));
  args.push_back (ConstantInt::get(Int32Type,
                                   TD.getABITypeAlignment(AllocType)));
  args.push_back (ConstantInt::get(Int1Type, 0));
  CallInst::Create (Memset, args, "", InsertPt);

  //
  // Update statistics.
  //
  ++InitedAllocas;
  return;
}