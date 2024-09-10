void LowerIntrinsics::AutomaticallyRootValue(AllocaInst &AI, Type *Ty,
                                             ArrayRef<Value *> Indices) {
  Module *M = AI.getParent()->getParent()->getParent();
  LLVMContext &C = M->getContext();
  Type *Int32Ty = Type::getInt32Ty(C);

  switch (Ty->getTypeID()) {
  case Type::PointerTyID: {
    if (cast<PointerType>(Ty)->getAddressSpace() < 1)
      break;

    // Create the GEP, if necessary.
    Instruction *BaseInst = &AI;
    if (Indices.size() > 1) {
      BaseInst = GetElementPtrInst::Create(&AI, Indices);
      BaseInst->insertAfter(&AI);
    }

    // Cast the value to an i8** to make a type-compatible intrinsic call.
    Type *PtrTy = PointerType::get(Type::getInt8PtrTy(C), 0);
    Instruction *GCRootArg = new BitCastInst(BaseInst, PtrTy);
    GCRootArg->insertAfter(BaseInst);

    // Cast the addrspace of the root to i8* to make type-compatible with call.
    Constant *AddressSpace =
      ConstantInt::get(Type::getInt64Ty(C), cast<PointerType>(Ty)->getAddressSpace());
    Constant *GCMetadataArg =
      ConstantExpr::getIntToPtr(AddressSpace, Type::getInt8PtrTy(C));

    // Create an intrinsic call.
    Value *Args[2];
    Args[0] = GCRootArg;
    Args[1] = GCMetadataArg;
    Function *GCRootFn = Intrinsic::getDeclaration(M, Intrinsic::gcroot);
    CallInst *Call = CallInst::Create(GCRootFn, Args);
    Call->insertAfter(GCRootArg);
    break;
  }

  case Type::StructTyID:
  case Type::ArrayTyID:
  case Type::VectorTyID: {
    // Skip auto-rooting structs for because we explicitly root these
    // by allocaing pointers on the stack.
    /*
    SmallVector<Value *, 8> NewIndices(Indices.begin(), Indices.end());
    NewIndices.push_back(ConstantInt::get(Int32Ty, 0));
    for (unsigned i = 0; i < Ty->getNumContainedTypes(); ++i) {
      NewIndices[NewIndices.size() - 1] = ConstantInt::get(Int32Ty, i);
      AutomaticallyRootValue(AI, Ty->getContainedType(i), NewIndices);
    }
    */
    break;
  }

  default:
    break;
  }
}