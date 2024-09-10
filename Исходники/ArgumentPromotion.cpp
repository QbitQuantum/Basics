/// PromoteArguments - This method checks the specified function to see if there
/// are any promotable arguments and if it is safe to promote the function (for
/// example, all callers are direct).  If safe to promote some arguments, it
/// calls the DoPromotion method.
///
CallGraphNode *ArgPromotion::PromoteArguments(CallGraphNode *CGN) {
  Function *F = CGN->getFunction();

  // Make sure that it is local to this module.
  if (!F || !F->hasLocalLinkage()) return nullptr;

  // Don't promote arguments for variadic functions. Adding, removing, or
  // changing non-pack parameters can change the classification of pack
  // parameters. Frontends encode that classification at the call site in the
  // IR, while in the callee the classification is determined dynamically based
  // on the number of registers consumed so far.
  if (F->isVarArg()) return nullptr;

  // First check: see if there are any pointer arguments!  If not, quick exit.
  SmallVector<Argument*, 16> PointerArgs;
  for (Function::arg_iterator I = F->arg_begin(), E = F->arg_end(); I != E; ++I)
    if (I->getType()->isPointerTy())
      PointerArgs.push_back(I);
  if (PointerArgs.empty()) return nullptr;

  // Second check: make sure that all callers are direct callers.  We can't
  // transform functions that have indirect callers.  Also see if the function
  // is self-recursive.
  bool isSelfRecursive = false;
  for (Use &U : F->uses()) {
    CallSite CS(U.getUser());
    // Must be a direct call.
    if (CS.getInstruction() == nullptr || !CS.isCallee(&U)) return nullptr;
    
    if (CS.getInstruction()->getParent()->getParent() == F)
      isSelfRecursive = true;
  }
  
  const DataLayout &DL = F->getParent()->getDataLayout();

  // Check to see which arguments are promotable.  If an argument is promotable,
  // add it to ArgsToPromote.
  SmallPtrSet<Argument*, 8> ArgsToPromote;
  SmallPtrSet<Argument*, 8> ByValArgsToTransform;
  for (unsigned i = 0, e = PointerArgs.size(); i != e; ++i) {
    Argument *PtrArg = PointerArgs[i];
    Type *AgTy = cast<PointerType>(PtrArg->getType())->getElementType();

    // If this is a byval argument, and if the aggregate type is small, just
    // pass the elements, which is always safe, if the passed value is densely
    // packed or if we can prove the padding bytes are never accessed. This does
    // not apply to inalloca.
    bool isSafeToPromote =
        PtrArg->hasByValAttr() &&
        (isDenselyPacked(AgTy, DL) || !canPaddingBeAccessed(PtrArg));
    if (isSafeToPromote) {
      if (StructType *STy = dyn_cast<StructType>(AgTy)) {
        if (maxElements > 0 && STy->getNumElements() > maxElements) {
          DEBUG(dbgs() << "argpromotion disable promoting argument '"
                << PtrArg->getName() << "' because it would require adding more"
                << " than " << maxElements << " arguments to the function.\n");
          continue;
        }
        
        // If all the elements are single-value types, we can promote it.
        bool AllSimple = true;
        for (unsigned i = 0, e = STy->getNumElements(); i != e; ++i) {
          if (!STy->getElementType(i)->isSingleValueType()) {
            AllSimple = false;
            break;
          }
        }

        // Safe to transform, don't even bother trying to "promote" it.
        // Passing the elements as a scalar will allow scalarrepl to hack on
        // the new alloca we introduce.
        if (AllSimple) {
          ByValArgsToTransform.insert(PtrArg);
          continue;
        }
      }
    }

    // If the argument is a recursive type and we're in a recursive
    // function, we could end up infinitely peeling the function argument.
    if (isSelfRecursive) {
      if (StructType *STy = dyn_cast<StructType>(AgTy)) {
        bool RecursiveType = false;
        for (unsigned i = 0, e = STy->getNumElements(); i != e; ++i) {
          if (STy->getElementType(i) == PtrArg->getType()) {
            RecursiveType = true;
            break;
          }
        }
        if (RecursiveType)
          continue;
      }
    }
    
    // Otherwise, see if we can promote the pointer to its value.
    if (isSafeToPromoteArgument(PtrArg, PtrArg->hasByValOrInAllocaAttr()))
      ArgsToPromote.insert(PtrArg);
  }

  // No promotable pointer arguments.
  if (ArgsToPromote.empty() && ByValArgsToTransform.empty()) 
    return nullptr;

  return DoPromotion(F, ArgsToPromote, ByValArgsToTransform);
}