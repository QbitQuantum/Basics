/// processByValArgument - This is called on every byval argument in call sites.
bool MemCpyOpt::processByValArgument(CallSite CS, unsigned ArgNo) {
  const DataLayout &DL = CS.getCaller()->getParent()->getDataLayout();
  // Find out what feeds this byval argument.
  Value *ByValArg = CS.getArgument(ArgNo);
  Type *ByValTy = cast<PointerType>(ByValArg->getType())->getElementType();
  uint64_t ByValSize = DL.getTypeAllocSize(ByValTy);
  MemDepResult DepInfo =
    MD->getPointerDependencyFrom(AliasAnalysis::Location(ByValArg, ByValSize),
                                 true, CS.getInstruction(),
                                 CS.getInstruction()->getParent());
  if (!DepInfo.isClobber())
    return false;

  // If the byval argument isn't fed by a memcpy, ignore it.  If it is fed by
  // a memcpy, see if we can byval from the source of the memcpy instead of the
  // result.
  MemCpyInst *MDep = dyn_cast<MemCpyInst>(DepInfo.getInst());
  if (!MDep || MDep->isVolatile() ||
      ByValArg->stripPointerCasts() != MDep->getDest())
    return false;

  // The length of the memcpy must be larger or equal to the size of the byval.
  ConstantInt *C1 = dyn_cast<ConstantInt>(MDep->getLength());
  if (!C1 || C1->getValue().getZExtValue() < ByValSize)
    return false;

  // Get the alignment of the byval.  If the call doesn't specify the alignment,
  // then it is some target specific value that we can't know.
  unsigned ByValAlign = CS.getParamAlignment(ArgNo+1);
  if (ByValAlign == 0) return false;

  // If it is greater than the memcpy, then we check to see if we can force the
  // source of the memcpy to the alignment we need.  If we fail, we bail out.
  AssumptionCache &AC =
      getAnalysis<AssumptionCacheTracker>().getAssumptionCache(
          *CS->getParent()->getParent());
  DominatorTree &DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
  if (MDep->getAlignment() < ByValAlign &&
      getOrEnforceKnownAlignment(MDep->getSource(), ByValAlign, DL,
                                 CS.getInstruction(), &AC, &DT) < ByValAlign)
    return false;

  // Verify that the copied-from memory doesn't change in between the memcpy and
  // the byval call.
  //    memcpy(a <- b)
  //    *b = 42;
  //    foo(*a)
  // It would be invalid to transform the second memcpy into foo(*b).
  //
  // NOTE: This is conservative, it will stop on any read from the source loc,
  // not just the defining memcpy.
  MemDepResult SourceDep =
    MD->getPointerDependencyFrom(AliasAnalysis::getLocationForSource(MDep),
                                 false, CS.getInstruction(), MDep->getParent());
  if (!SourceDep.isClobber() || SourceDep.getInst() != MDep)
    return false;

  Value *TmpCast = MDep->getSource();
  if (MDep->getSource()->getType() != ByValArg->getType())
    TmpCast = new BitCastInst(MDep->getSource(), ByValArg->getType(),
                              "tmpcast", CS.getInstruction());

  DEBUG(dbgs() << "MemCpyOpt: Forwarding memcpy to byval:\n"
               << "  " << *MDep << "\n"
               << "  " << *CS.getInstruction() << "\n");

  // Otherwise we're good!  Update the byval argument.
  CS.setArgument(ArgNo, TmpCast);
  ++NumMemCpyInstr;
  return true;
}