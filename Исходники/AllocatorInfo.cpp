Value *
StringAllocatorInfo::getOrCreateAllocSize (Value * AllocSite) const {
  //
  // See if this is a call to the allocator.  If not, return NULL.
  //
  CallInst * CI = dyn_cast<CallInst>(AllocSite);
  if (!CI)
    return NULL;

  Function * F  = dyn_cast<Function>(CI->getCalledValue()->stripPointerCasts());
  if (!F || F->getName() != allocCallName) 
    return NULL;

  //
  // See if this call has an argument.  If not, ignore it.  We do this because
  // autoconf configure scripts will create calls to string functions with zero
  // arguments just to see if the function exists.
  //
  CallSite CS(CI);
  if (CS.arg_size() == 0)
    return NULL;

  //
  // Insert a call to strlen() to determine the length of the string that was
  // allocated.  Use a version of strlen() in the SAFECode library that can
  // handle NULL pointers.
  //
  Module * M = CI->getParent()->getParent()->getParent();
  Function * Strlen = M->getFunction ("nullstrlen");
  assert (Strlen && "No nullstrlen function in the module");
  BasicBlock::iterator InsertPt = CI;
  ++InsertPt;
  Instruction * Length =
    CallInst::Create (Strlen, CS.getInstruction(), "", InsertPt);

  //
  // The size of the allocation is the string length plus one.
  //
  IntegerType * LengthType = dyn_cast<IntegerType>(Length->getType());
  assert (LengthType && "nullstrlen doesn't return an integer?");
  Value * One = ConstantInt::get (LengthType, 1);
  Instruction * Size = BinaryOperator::Create (Instruction::Add, Length, One);
  Size->insertAfter (Length);
  return Size;
}