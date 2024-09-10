void RegionGenerator::generateScalarStores(ScopStmt &Stmt, BasicBlock *BB,
                                           ValueMapT &BBMap,
                                           ValueMapT &GlobalMap) {
  const Region &R = Stmt.getParent()->getRegion();

  Region *StmtR = Stmt.getRegion();
  assert(StmtR && "Block statements need to use the generateScalarStores() "
                  "function in the BlockGenerator");

  BasicBlock *ExitBB = StmtR->getExit();

  // For region statements three kinds of scalar stores exists:
  //  (1) A definition used by a non-phi instruction outside the region.
  //  (2) A phi-instruction in the region entry.
  //  (3) A write to a phi instruction in the region exit.
  // The last case is the tricky one since we do not know anymore which
  // predecessor of the exit needs to store the operand value that doesn't
  // have a definition in the region. Therefore, we have to check in each
  // block in the region if we should store the value or not.

  // Iterate over all accesses in the given statement.
  for (MemoryAccess *MA : Stmt) {

    // Skip non-scalar and read accesses.
    if (!MA->isScalar() || MA->isRead())
      continue;

    Instruction *ScalarBase = cast<Instruction>(MA->getBaseAddr());
    Instruction *ScalarInst = MA->getAccessInstruction();
    PHINode *ScalarBasePHI = dyn_cast<PHINode>(ScalarBase);

    Value *ScalarValue = nullptr;
    AllocaInst *ScalarAddr = nullptr;

    if (!ScalarBasePHI) {
      // Case (1)
      ScalarAddr = getOrCreateAlloca(ScalarBase, ScalarMap, ".s2a");
      ScalarValue = ScalarInst;
    } else if (ScalarBasePHI->getParent() != ExitBB) {
      // Case (2)
      assert(ScalarBasePHI->getParent() == StmtR->getEntry() &&
             "Bad PHI self write in non-affine region");
      assert(ScalarBase == ScalarInst &&
             "Bad PHI self write in non-affine region");
      ScalarAddr = getOrCreateAlloca(ScalarBase, ScalarMap, ".s2a");
      ScalarValue = ScalarInst;
    } else {
      int PHIIdx = ScalarBasePHI->getBasicBlockIndex(BB);
      // Skip accesses we will not handle in this basic block but in another one
      // in the statement region.
      if (PHIIdx < 0)
        continue;

      // Case (3)
      ScalarAddr = getOrCreateAlloca(ScalarBase, PHIOpMap, ".phiops");
      ScalarValue = ScalarBasePHI->getIncomingValue(PHIIdx);
    }

    ScalarValue =
        getNewScalarValue(ScalarValue, R, ScalarMap, BBMap, GlobalMap);
    Builder.CreateStore(ScalarValue, ScalarAddr);
  }
}