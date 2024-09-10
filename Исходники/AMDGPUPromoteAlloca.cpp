// FIXME: Should try to pick the most likely to be profitable allocas first.
bool AMDGPUPromoteAlloca::handleAlloca(AllocaInst &I, bool SufficientLDS) {
  // Array allocations are probably not worth handling, since an allocation of
  // the array type is the canonical form.
  if (!I.isStaticAlloca() || I.isArrayAllocation())
    return false;

  IRBuilder<> Builder(&I);

  // First try to replace the alloca with a vector
  Type *AllocaTy = I.getAllocatedType();

  DEBUG(dbgs() << "Trying to promote " << I << '\n');

  if (tryPromoteAllocaToVector(&I, AS))
    return true; // Promoted to vector.

  const Function &ContainingFunction = *I.getParent()->getParent();
  CallingConv::ID CC = ContainingFunction.getCallingConv();

  // Don't promote the alloca to LDS for shader calling conventions as the work
  // item ID intrinsics are not supported for these calling conventions.
  // Furthermore not all LDS is available for some of the stages.
  switch (CC) {
  case CallingConv::AMDGPU_KERNEL:
  case CallingConv::SPIR_KERNEL:
    break;
  default:
    DEBUG(dbgs() << " promote alloca to LDS not supported with calling convention.\n");
    return false;
  }

  // Not likely to have sufficient local memory for promotion.
  if (!SufficientLDS)
    return false;

  const AMDGPUSubtarget &ST =
    TM->getSubtarget<AMDGPUSubtarget>(ContainingFunction);
  unsigned WorkGroupSize = ST.getFlatWorkGroupSizes(ContainingFunction).second;

  const DataLayout &DL = Mod->getDataLayout();

  unsigned Align = I.getAlignment();
  if (Align == 0)
    Align = DL.getABITypeAlignment(I.getAllocatedType());

  // FIXME: This computed padding is likely wrong since it depends on inverse
  // usage order.
  //
  // FIXME: It is also possible that if we're allowed to use all of the memory
  // could could end up using more than the maximum due to alignment padding.

  uint32_t NewSize = alignTo(CurrentLocalMemUsage, Align);
  uint32_t AllocSize = WorkGroupSize * DL.getTypeAllocSize(AllocaTy);
  NewSize += AllocSize;

  if (NewSize > LocalMemLimit) {
    DEBUG(dbgs() << "  " << AllocSize
          << " bytes of local memory not available to promote\n");
    return false;
  }

  CurrentLocalMemUsage = NewSize;

  std::vector<Value*> WorkList;

  if (!collectUsesWithPtrTypes(&I, &I, WorkList)) {
    DEBUG(dbgs() << " Do not know how to convert all uses\n");
    return false;
  }

  DEBUG(dbgs() << "Promoting alloca to local memory\n");

  Function *F = I.getParent()->getParent();

  Type *GVTy = ArrayType::get(I.getAllocatedType(), WorkGroupSize);
  GlobalVariable *GV = new GlobalVariable(
      *Mod, GVTy, false, GlobalValue::InternalLinkage,
      UndefValue::get(GVTy),
      Twine(F->getName()) + Twine('.') + I.getName(),
      nullptr,
      GlobalVariable::NotThreadLocal,
      AS.LOCAL_ADDRESS);
  GV->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
  GV->setAlignment(I.getAlignment());

  Value *TCntY, *TCntZ;

  std::tie(TCntY, TCntZ) = getLocalSizeYZ(Builder);
  Value *TIdX = getWorkitemID(Builder, 0);
  Value *TIdY = getWorkitemID(Builder, 1);
  Value *TIdZ = getWorkitemID(Builder, 2);

  Value *Tmp0 = Builder.CreateMul(TCntY, TCntZ, "", true, true);
  Tmp0 = Builder.CreateMul(Tmp0, TIdX);
  Value *Tmp1 = Builder.CreateMul(TIdY, TCntZ, "", true, true);
  Value *TID = Builder.CreateAdd(Tmp0, Tmp1);
  TID = Builder.CreateAdd(TID, TIdZ);

  Value *Indices[] = {
    Constant::getNullValue(Type::getInt32Ty(Mod->getContext())),
    TID
  };

  Value *Offset = Builder.CreateInBoundsGEP(GVTy, GV, Indices);
  I.mutateType(Offset->getType());
  I.replaceAllUsesWith(Offset);
  I.eraseFromParent();

  for (Value *V : WorkList) {
    CallInst *Call = dyn_cast<CallInst>(V);
    if (!Call) {
      if (ICmpInst *CI = dyn_cast<ICmpInst>(V)) {
        Value *Src0 = CI->getOperand(0);
        Type *EltTy = Src0->getType()->getPointerElementType();
        PointerType *NewTy = PointerType::get(EltTy, AS.LOCAL_ADDRESS);

        if (isa<ConstantPointerNull>(CI->getOperand(0)))
          CI->setOperand(0, ConstantPointerNull::get(NewTy));

        if (isa<ConstantPointerNull>(CI->getOperand(1)))
          CI->setOperand(1, ConstantPointerNull::get(NewTy));

        continue;
      }

      // The operand's value should be corrected on its own and we don't want to
      // touch the users.
      if (isa<AddrSpaceCastInst>(V))
        continue;

      Type *EltTy = V->getType()->getPointerElementType();
      PointerType *NewTy = PointerType::get(EltTy, AS.LOCAL_ADDRESS);

      // FIXME: It doesn't really make sense to try to do this for all
      // instructions.
      V->mutateType(NewTy);

      // Adjust the types of any constant operands.
      if (SelectInst *SI = dyn_cast<SelectInst>(V)) {
        if (isa<ConstantPointerNull>(SI->getOperand(1)))
          SI->setOperand(1, ConstantPointerNull::get(NewTy));

        if (isa<ConstantPointerNull>(SI->getOperand(2)))
          SI->setOperand(2, ConstantPointerNull::get(NewTy));
      } else if (PHINode *Phi = dyn_cast<PHINode>(V)) {
        for (unsigned I = 0, E = Phi->getNumIncomingValues(); I != E; ++I) {
          if (isa<ConstantPointerNull>(Phi->getIncomingValue(I)))
            Phi->setIncomingValue(I, ConstantPointerNull::get(NewTy));
        }
      }

      continue;
    }

    IntrinsicInst *Intr = cast<IntrinsicInst>(Call);
    Builder.SetInsertPoint(Intr);
    switch (Intr->getIntrinsicID()) {
    case Intrinsic::lifetime_start:
    case Intrinsic::lifetime_end:
      // These intrinsics are for address space 0 only
      Intr->eraseFromParent();
      continue;
    case Intrinsic::memcpy: {
      MemCpyInst *MemCpy = cast<MemCpyInst>(Intr);
      Builder.CreateMemCpy(MemCpy->getRawDest(), MemCpy->getDestAlignment(),
                           MemCpy->getRawSource(), MemCpy->getSourceAlignment(),
                           MemCpy->getLength(), MemCpy->isVolatile());
      Intr->eraseFromParent();
      continue;
    }
    case Intrinsic::memmove: {
      MemMoveInst *MemMove = cast<MemMoveInst>(Intr);
      Builder.CreateMemMove(MemMove->getRawDest(), MemMove->getDestAlignment(),
                            MemMove->getRawSource(), MemMove->getSourceAlignment(),
                            MemMove->getLength(), MemMove->isVolatile());
      Intr->eraseFromParent();
      continue;
    }
    case Intrinsic::memset: {
      MemSetInst *MemSet = cast<MemSetInst>(Intr);
      Builder.CreateMemSet(MemSet->getRawDest(), MemSet->getValue(),
                           MemSet->getLength(), MemSet->getDestAlignment(),
                           MemSet->isVolatile());
      Intr->eraseFromParent();
      continue;
    }
    case Intrinsic::invariant_start:
    case Intrinsic::invariant_end:
    case Intrinsic::invariant_group_barrier:
      Intr->eraseFromParent();
      // FIXME: I think the invariant marker should still theoretically apply,
      // but the intrinsics need to be changed to accept pointers with any
      // address space.
      continue;
    case Intrinsic::objectsize: {
      Value *Src = Intr->getOperand(0);
      Type *SrcTy = Src->getType()->getPointerElementType();
      Function *ObjectSize = Intrinsic::getDeclaration(Mod,
        Intrinsic::objectsize,
        { Intr->getType(), PointerType::get(SrcTy, AS.LOCAL_ADDRESS) }
      );

      CallInst *NewCall = Builder.CreateCall(
          ObjectSize, {Src, Intr->getOperand(1), Intr->getOperand(2)});
      Intr->replaceAllUsesWith(NewCall);
      Intr->eraseFromParent();
      continue;
    }
    default:
      Intr->print(errs());
      llvm_unreachable("Don't know how to promote alloca intrinsic use.");
    }
  }
  return true;
}