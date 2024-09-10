bool RCIdentityFunctionInfo::
findDominatingNonPayloadedEdge(SILBasicBlock *IncomingEdgeBB,
                               SILValue RCIdentity) {
  // First grab the NonPayloadedEnumBB and RCIdentityBB. If we cannot find
  // either of them, return false.
  SILBasicBlock *RCIdentityBB = RCIdentity->getParentBlock();
  if (!RCIdentityBB)
    return false;

  // Make sure that the incoming edge bb is not the RCIdentityBB. We are not
  // trying to handle this case here, so simplify by just bailing if we detect
  // it.
  //
  // I think the only way this can happen is if we have a switch_enum of some
  // sort with multiple incoming values going into the destination BB. We are
  // not interested in handling that case anyways.
  //
  // FIXME: If we ever split all critical edges, this should be relooked at.
  if (IncomingEdgeBB == RCIdentityBB)
    return false;

  // Now we know that RCIdentityBB and IncomingEdgeBB are different. Prove that
  // RCIdentityBB dominates IncomingEdgeBB.
  SILFunction *F = RCIdentityBB->getParent();

  // First make sure that IncomingEdgeBB dominates NonPayloadedEnumBB. If not,
  // return false.
  DominanceInfo *DI = DA->get(F);
  if (!DI->dominates(RCIdentityBB, IncomingEdgeBB))
    return false;

  // Now walk up the dominator tree from IncomingEdgeBB to RCIdentityBB and see
  // if we can find a use of RCIdentity that dominates IncomingEdgeBB and
  // enables us to know that RCIdentity must be a no-payload enum along
  // IncomingEdge. We don't care if the case or enum of RCIdentity match the
  // case or enum along RCIdentityBB since a pairing of retain, release of two
  // non-payloaded enums can always be eliminated (since we can always eliminate
  // ref count operations on non-payloaded enums).

  // RCIdentityBB must have a valid dominator tree node.
  auto *EndDomNode = DI->getNode(RCIdentityBB);
  if (!EndDomNode)
    return false;

  for (auto *Node = DI->getNode(IncomingEdgeBB); Node; Node = Node->getIDom()) {
    // Search for uses of RCIdentity in Node->getBlock() that will enable us to
    // know that it has a non-payloaded enum case.
    SILBasicBlock *DominatingBB = Node->getBlock();
    llvm::Optional<bool> Result =
        proveNonPayloadedEnumCase(DominatingBB, RCIdentity);

    // If we found either a signal of a payloaded or a non-payloaded enum,
    // return that value.
    if (Result.hasValue())
      return Result.getValue();

    // If we didn't reach RCIdentityBB, keep processing up the DomTree.
    if (DominatingBB != RCIdentityBB)
      continue;

    // Otherwise, we failed to find any interesting information, return false.
    return false;
  }

  return false;
}