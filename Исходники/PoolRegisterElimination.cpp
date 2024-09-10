void
PoolRegisterElimination::removeSingletonRegistrations (const char * name) {
  //
  // Scan through all uses of the registration function and see if it can be
  // safely removed.  If so, schedule it for removal.
  //
  std::vector<CallInst*> toBeRemoved;
  Function * F = intrinsic->getIntrinsic(name).F;

  //
  // Look for and record all registrations that can be deleted.
  //
  for (Value::use_iterator UI=F->use_begin(), UE=F->use_end();
       UI != UE;
       ++UI) {
    //
    // Get the pointer to the registered object.
    //
    CallInst * CI = cast<CallInst>(*UI);
    Value * Ptr = intrinsic->getValuePointer(CI);

    //
    // Lookup the DSNode for the value in the function's DSGraph.
    //
    DSGraph * TDG = dsaPass->getDSGraph(*(CI->getParent()->getParent()));
    DSNodeHandle DSH = TDG->getNodeForValue(Ptr);
    assert ((!(DSH.isNull())) && "No DSNode for Value!\n");

    //
    // If the object being registered is the same size as that found in the
    // DSNode, then we know it's a singleton object.  The run-time doesn't need
    // such objects registered in the splay trees, so we can remove the
    // registration function.
    //
    DSNode * N = DSH.getNode();
    Value * Size = intrinsic->getObjectSize (Ptr->stripPointerCasts());
    if (Size) {
      if (ConstantInt * C = dyn_cast<ConstantInt>(Size)) {
        unsigned long size = C->getZExtValue();
        if (size == N->getSize()) {
          toBeRemoved.push_back(CI);
          continue;
        }
      }
    }
  }

  //
  // Update the statistics.
  //
  if (toBeRemoved.size()) {
    RemovedRegistration += toBeRemoved.size();
    SingletonRegistrations += toBeRemoved.size();
  }

  //
  // Remove the unnecesary registrations.
  //
  std::vector<CallInst*>::iterator it, end;
  for (it = toBeRemoved.begin(), end = toBeRemoved.end(); it != end; ++it) {
    (*it)->eraseFromParent();
  }
}