bool NVVMReflect::runOnFunction(Function &F) {
  if (!NVVMReflectEnabled)
    return false;

  if (F.getName() == NVVM_REFLECT_FUNCTION) {
    assert(F.isDeclaration() && "_reflect function should not have a body");
    assert(F.getReturnType()->isIntegerTy() &&
           "_reflect's return type should be integer");
    return false;
  }

  SmallVector<Instruction *, 4> ToRemove;

  // Go through the calls in this function.  Each call to __nvvm_reflect or
  // llvm.nvvm.reflect should be a CallInst with a ConstantArray argument.
  // First validate that. If the c-string corresponding to the ConstantArray can
  // be found successfully, see if it can be found in VarMap. If so, replace the
  // uses of CallInst with the value found in VarMap. If not, replace the use
  // with value 0.

  // The IR for __nvvm_reflect calls differs between CUDA versions.
  //
  // CUDA 6.5 and earlier uses this sequence:
  //    %ptr = tail call i8* @llvm.nvvm.ptr.constant.to.gen.p0i8.p4i8
  //        (i8 addrspace(4)* getelementptr inbounds
  //           ([8 x i8], [8 x i8] addrspace(4)* @str, i32 0, i32 0))
  //    %reflect = tail call i32 @__nvvm_reflect(i8* %ptr)
  //
  // The value returned by Sym->getOperand(0) is a Constant with a
  // ConstantDataSequential operand which can be converted to string and used
  // for lookup.
  //
  // CUDA 7.0 does it slightly differently:
  //   %reflect = call i32 @__nvvm_reflect(i8* addrspacecast
  //        (i8 addrspace(1)* getelementptr inbounds
  //           ([8 x i8], [8 x i8] addrspace(1)* @str, i32 0, i32 0) to i8*))
  //
  // In this case, we get a Constant with a GlobalVariable operand and we need
  // to dig deeper to find its initializer with the string we'll use for lookup.
  for (Instruction &I : instructions(F)) {
    CallInst *Call = dyn_cast<CallInst>(&I);
    if (!Call)
      continue;
    Function *Callee = Call->getCalledFunction();
    if (!Callee || (Callee->getName() != NVVM_REFLECT_FUNCTION &&
                    Callee->getIntrinsicID() != Intrinsic::nvvm_reflect))
      continue;

    // FIXME: Improve error handling here and elsewhere in this pass.
    assert(Call->getNumOperands() == 2 &&
           "Wrong number of operands to __nvvm_reflect function");

    // In cuda 6.5 and earlier, we will have an extra constant-to-generic
    // conversion of the string.
    const Value *Str = Call->getArgOperand(0);
    if (const CallInst *ConvCall = dyn_cast<CallInst>(Str)) {
      // FIXME: Add assertions about ConvCall.
      Str = ConvCall->getArgOperand(0);
    }
    assert(isa<ConstantExpr>(Str) &&
           "Format of __nvvm__reflect function not recognized");
    const ConstantExpr *GEP = cast<ConstantExpr>(Str);

    const Value *Sym = GEP->getOperand(0);
    assert(isa<Constant>(Sym) &&
           "Format of __nvvm_reflect function not recognized");

    const Value *Operand = cast<Constant>(Sym)->getOperand(0);
    if (const GlobalVariable *GV = dyn_cast<GlobalVariable>(Operand)) {
      // For CUDA-7.0 style __nvvm_reflect calls, we need to find the operand's
      // initializer.
      assert(GV->hasInitializer() &&
             "Format of _reflect function not recognized");
      const Constant *Initializer = GV->getInitializer();
      Operand = Initializer;
    }

    assert(isa<ConstantDataSequential>(Operand) &&
           "Format of _reflect function not recognized");
    assert(cast<ConstantDataSequential>(Operand)->isCString() &&
           "Format of _reflect function not recognized");

    StringRef ReflectArg = cast<ConstantDataSequential>(Operand)->getAsString();
    ReflectArg = ReflectArg.substr(0, ReflectArg.size() - 1);
    LLVM_DEBUG(dbgs() << "Arg of _reflect : " << ReflectArg << "\n");

    int ReflectVal = 0; // The default value is 0
    if (ReflectArg == "__CUDA_FTZ") {
      // Try to pull __CUDA_FTZ from the nvvm-reflect-ftz module flag.  Our
      // choice here must be kept in sync with AutoUpgrade, which uses the same
      // technique to detect whether ftz is enabled.
      if (auto *Flag = mdconst::extract_or_null<ConstantInt>(
              F.getParent()->getModuleFlag("nvvm-reflect-ftz")))
        ReflectVal = Flag->getSExtValue();
    } else if (ReflectArg == "__CUDA_ARCH") {
      ReflectVal = SmVersion * 10;
    }
    Call->replaceAllUsesWith(ConstantInt::get(Call->getType(), ReflectVal));
    ToRemove.push_back(Call);
  }

  for (Instruction *I : ToRemove)
    I->eraseFromParent();

  return ToRemove.size() > 0;
}