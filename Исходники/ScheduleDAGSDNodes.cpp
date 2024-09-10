/// EmitSchedule - Emit the machine code in scheduled order. Return the new
/// InsertPos and MachineBasicBlock that contains this insertion
/// point. ScheduleDAGSDNodes holds a BB pointer for convenience, but this does
/// not necessarily refer to returned BB. The emitter may split blocks.
MachineBasicBlock *ScheduleDAGSDNodes::
EmitSchedule(MachineBasicBlock::iterator &InsertPos) {
  InstrEmitter Emitter(BB, InsertPos);
  DenseMap<SDValue, unsigned> VRBaseMap;
  DenseMap<SUnit*, unsigned> CopyVRBaseMap;
  SmallVector<std::pair<unsigned, MachineInstr*>, 32> Orders;
  SmallSet<unsigned, 8> Seen;
  bool HasDbg = DAG->hasDebugValues();

  // If this is the first BB, emit byval parameter dbg_value's.
  if (HasDbg && BB->getParent()->begin() == MachineFunction::iterator(BB)) {
    SDDbgInfo::DbgIterator PDI = DAG->ByvalParmDbgBegin();
    SDDbgInfo::DbgIterator PDE = DAG->ByvalParmDbgEnd();
    for (; PDI != PDE; ++PDI) {
      MachineInstr *DbgMI= Emitter.EmitDbgValue(*PDI, VRBaseMap);
      if (DbgMI)
        BB->insert(InsertPos, DbgMI);
    }
  }

  for (unsigned i = 0, e = Sequence.size(); i != e; i++) {
    SUnit *SU = Sequence[i];
    if (!SU) {
      // Null SUnit* is a noop.
      TII->insertNoop(*Emitter.getBlock(), InsertPos);
      continue;
    }

    // For pre-regalloc scheduling, create instructions corresponding to the
    // SDNode and any glued SDNodes and append them to the block.
    if (!SU->getNode()) {
      // Emit a copy.
      EmitPhysRegCopy(SU, CopyVRBaseMap, InsertPos);
      continue;
    }

    SmallVector<SDNode *, 4> GluedNodes;
    for (SDNode *N = SU->getNode()->getGluedNode(); N;
         N = N->getGluedNode())
      GluedNodes.push_back(N);
    while (!GluedNodes.empty()) {
      SDNode *N = GluedNodes.back();
      Emitter.EmitNode(GluedNodes.back(), SU->OrigNode != SU, SU->isCloned,
                       VRBaseMap);
      // Remember the source order of the inserted instruction.
      if (HasDbg)
        ProcessSourceNode(N, DAG, Emitter, VRBaseMap, Orders, Seen);
      GluedNodes.pop_back();
    }
    Emitter.EmitNode(SU->getNode(), SU->OrigNode != SU, SU->isCloned,
                     VRBaseMap);
    // Remember the source order of the inserted instruction.
    if (HasDbg)
      ProcessSourceNode(SU->getNode(), DAG, Emitter, VRBaseMap, Orders,
                        Seen);
  }

  // Insert all the dbg_values which have not already been inserted in source
  // order sequence.
  if (HasDbg) {
    MachineBasicBlock::iterator BBBegin = BB->getFirstNonPHI();

    // Sort the source order instructions and use the order to insert debug
    // values.
    std::sort(Orders.begin(), Orders.end(), OrderSorter());

    SDDbgInfo::DbgIterator DI = DAG->DbgBegin();
    SDDbgInfo::DbgIterator DE = DAG->DbgEnd();
    // Now emit the rest according to source order.
    unsigned LastOrder = 0;
    for (unsigned i = 0, e = Orders.size(); i != e && DI != DE; ++i) {
      unsigned Order = Orders[i].first;
      MachineInstr *MI = Orders[i].second;
      // Insert all SDDbgValue's whose order(s) are before "Order".
      if (!MI)
        continue;
      for (; DI != DE &&
             (*DI)->getOrder() >= LastOrder && (*DI)->getOrder() < Order; ++DI) {
        if ((*DI)->isInvalidated())
          continue;
        MachineInstr *DbgMI = Emitter.EmitDbgValue(*DI, VRBaseMap);
        if (DbgMI) {
          if (!LastOrder)
            // Insert to start of the BB (after PHIs).
            BB->insert(BBBegin, DbgMI);
          else {
            // Insert at the instruction, which may be in a different
            // block, if the block was split by a custom inserter.
            MachineBasicBlock::iterator Pos = MI;
            MI->getParent()->insert(llvm::next(Pos), DbgMI);
          }
        }
      }
      LastOrder = Order;
    }
    // Add trailing DbgValue's before the terminator. FIXME: May want to add
    // some of them before one or more conditional branches?
    SmallVector<MachineInstr*, 8> DbgMIs;
    while (DI != DE) {
      if (!(*DI)->isInvalidated())
        if (MachineInstr *DbgMI = Emitter.EmitDbgValue(*DI, VRBaseMap))
          DbgMIs.push_back(DbgMI);
      ++DI;
    }

    MachineBasicBlock *InsertBB = Emitter.getBlock();
    MachineBasicBlock::iterator Pos = InsertBB->getFirstTerminator();
    InsertBB->insert(Pos, DbgMIs.begin(), DbgMIs.end());
  }

  InsertPos = Emitter.getInsertPos();
  return Emitter.getBlock();
}