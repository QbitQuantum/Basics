// Decides whether V is an addrspacecast and shortcutting V in load/store is
// valid and beneficial.
static bool isEliminableAddrSpaceCast(Value *V) {
  // Returns false if V is not even an addrspacecast.
  Operator *Cast = dyn_cast<Operator>(V);
  if (Cast == nullptr || Cast->getOpcode() != Instruction::AddrSpaceCast)
    return false;

  Value *Src = Cast->getOperand(0);
  PointerType *SrcTy = cast<PointerType>(Src->getType());
  PointerType *DestTy = cast<PointerType>(Cast->getType());
  // TODO: For now, we only handle the case where the addrspacecast only changes
  // the address space but not the type. If the type also changes, we could
  // still get rid of the addrspacecast by adding an extra bitcast, but we
  // rarely see such scenarios.
  if (SrcTy->getElementType() != DestTy->getElementType())
    return false;

  // Checks whether the addrspacecast is from a non-generic address space to the
  // generic address space.
  return (SrcTy->getAddressSpace() != AddressSpace::ADDRESS_SPACE_GENERIC &&
          DestTy->getAddressSpace() == AddressSpace::ADDRESS_SPACE_GENERIC);
}