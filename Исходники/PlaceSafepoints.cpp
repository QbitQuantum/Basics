/// Replaces the given call site (Call or Invoke) with a gc.statepoint
/// intrinsic with an empty deoptimization arguments list.  This does
/// NOT do explicit relocation for GC support.
static Value *ReplaceWithStatepoint(const CallSite &CS, /* to replace */
                                    Pass *P) {
  BasicBlock *BB = CS.getInstruction()->getParent();
  Function *F = BB->getParent();
  Module *M = F->getParent();
  assert(M && "must be set");

  // TODO: technically, a pass is not allowed to get functions from within a
  // function pass since it might trigger a new function addition.  Refactor
  // this logic out to the initialization of the pass.  Doesn't appear to
  // matter in practice.

  // Fill in the one generic type'd argument (the function is also vararg)
  std::vector<Type *> argTypes;
  argTypes.push_back(CS.getCalledValue()->getType());

  Function *gc_statepoint_decl = Intrinsic::getDeclaration(
      M, Intrinsic::experimental_gc_statepoint, argTypes);

  // Then go ahead and use the builder do actually do the inserts.  We insert
  // immediately before the previous instruction under the assumption that all
  // arguments will be available here.  We can't insert afterwards since we may
  // be replacing a terminator.
  Instruction *insertBefore = CS.getInstruction();
  IRBuilder<> Builder(insertBefore);
  // First, create the statepoint (with all live ptrs as arguments).
  std::vector<llvm::Value *> args;
  // target, #args, unused, args
  Value *Target = CS.getCalledValue();
  args.push_back(Target);
  int callArgSize = CS.arg_size();
  args.push_back(
      ConstantInt::get(Type::getInt32Ty(M->getContext()), callArgSize));
  // TODO: add a 'Needs GC-rewrite' later flag
  args.push_back(ConstantInt::get(Type::getInt32Ty(M->getContext()), 0));

  // Copy all the arguments of the original call
  args.insert(args.end(), CS.arg_begin(), CS.arg_end());

  // Create the statepoint given all the arguments
  Instruction *token = nullptr;
  AttributeSet return_attributes;
  if (CS.isCall()) {
    CallInst *toReplace = cast<CallInst>(CS.getInstruction());
    CallInst *call =
        Builder.CreateCall(gc_statepoint_decl, args, "safepoint_token");
    call->setTailCall(toReplace->isTailCall());
    call->setCallingConv(toReplace->getCallingConv());

    // Before we have to worry about GC semantics, all attributes are legal
    AttributeSet new_attrs = toReplace->getAttributes();
    // In case if we can handle this set of sttributes - set up function attrs
    // directly on statepoint and return attrs later for gc_result intrinsic.
    call->setAttributes(new_attrs.getFnAttributes());
    return_attributes = new_attrs.getRetAttributes();
    // TODO: handle param attributes

    token = call;

    // Put the following gc_result and gc_relocate calls immediately after the
    // the old call (which we're about to delete)
    BasicBlock::iterator next(toReplace);
    assert(BB->end() != next && "not a terminator, must have next");
    next++;
    Instruction *IP = &*(next);
    Builder.SetInsertPoint(IP);
    Builder.SetCurrentDebugLocation(IP->getDebugLoc());

  } else if (CS.isInvoke()) {
    InvokeInst *toReplace = cast<InvokeInst>(CS.getInstruction());

    // Insert the new invoke into the old block.  We'll remove the old one in a
    // moment at which point this will become the new terminator for the
    // original block.
    InvokeInst *invoke = InvokeInst::Create(
        gc_statepoint_decl, toReplace->getNormalDest(),
        toReplace->getUnwindDest(), args, "", toReplace->getParent());
    invoke->setCallingConv(toReplace->getCallingConv());

    // Currently we will fail on parameter attributes and on certain
    // function attributes.
    AttributeSet new_attrs = toReplace->getAttributes();
    // In case if we can handle this set of sttributes - set up function attrs
    // directly on statepoint and return attrs later for gc_result intrinsic.
    invoke->setAttributes(new_attrs.getFnAttributes());
    return_attributes = new_attrs.getRetAttributes();

    token = invoke;

    // We'll insert the gc.result into the normal block
    BasicBlock *normalDest = normalizeBBForInvokeSafepoint(
        toReplace->getNormalDest(), invoke->getParent());
    Instruction *IP = &*(normalDest->getFirstInsertionPt());
    Builder.SetInsertPoint(IP);
  } else {
    llvm_unreachable("unexpect type of CallSite");
  }
  assert(token);

  // Handle the return value of the original call - update all uses to use a
  // gc_result hanging off the statepoint node we just inserted

  // Only add the gc_result iff there is actually a used result
  if (!CS.getType()->isVoidTy() && !CS.getInstruction()->use_empty()) {
    Instruction *gc_result = nullptr;
    std::vector<Type *> types;     // one per 'any' type
    types.push_back(CS.getType()); // result type
    auto get_gc_result_id = [&](Type &Ty) {
      if (Ty.isIntegerTy()) {
        return Intrinsic::experimental_gc_result_int;
      } else if (Ty.isFloatingPointTy()) {
        return Intrinsic::experimental_gc_result_float;
      } else if (Ty.isPointerTy()) {
        return Intrinsic::experimental_gc_result_ptr;
      } else {
        llvm_unreachable("non java type encountered");
      }
    };
    Intrinsic::ID Id = get_gc_result_id(*CS.getType());
    Value *gc_result_func = Intrinsic::getDeclaration(M, Id, types);

    std::vector<Value *> args;
    args.push_back(token);
    gc_result = Builder.CreateCall(
        gc_result_func, args,
        CS.getInstruction()->hasName() ? CS.getInstruction()->getName() : "");

    cast<CallInst>(gc_result)->setAttributes(return_attributes);
    return gc_result;
  } else {
    // No return value for the call.
    return nullptr;
  }
}