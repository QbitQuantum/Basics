void DSGraphStats::visitStore(StoreInst &SI) {
  if (isNodeForValueUntyped(SI.getOperand(1), 0,SI.getParent()->getParent())) {
    NumUntypedMemAccesses++;
  } else {
    NumTypedMemAccesses++;
  }
}