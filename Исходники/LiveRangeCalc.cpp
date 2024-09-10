bool LiveRangeCalc::findReachingDefs(LiveRange &LR, MachineBasicBlock &UseMBB,
                                     SlotIndex Use, unsigned PhysReg,
                                     ArrayRef<SlotIndex> Undefs) {
  unsigned UseMBBNum = UseMBB.getNumber();

  // Block numbers where LR should be live-in.
  SmallVector<unsigned, 16> WorkList(1, UseMBBNum);

  // Remember if we have seen more than one value.
  bool UniqueVNI = true;
  VNInfo *TheVNI = nullptr;

  bool FoundUndef = false;

  // Using Seen as a visited set, perform a BFS for all reaching defs.
  for (unsigned i = 0; i != WorkList.size(); ++i) {
    MachineBasicBlock *MBB = MF->getBlockNumbered(WorkList[i]);

#ifndef NDEBUG
    if (Undefs.size() > 0 && MBB->pred_empty()) {
      MBB->getParent()->verify();
      errs() << "Use of " << PrintReg(PhysReg)
             << " does not have a corresponding definition on every path:\n";
      const MachineInstr *MI = Indexes->getInstructionFromIndex(Use);
      if (MI != nullptr)
        errs() << Use << " " << *MI;
      llvm_unreachable("Use not jointly dominated by defs.");
    }

    if (TargetRegisterInfo::isPhysicalRegister(PhysReg) &&
        !MBB->isLiveIn(PhysReg)) {
      MBB->getParent()->verify();
      const TargetRegisterInfo *TRI = MRI->getTargetRegisterInfo();
      errs() << "The register " << PrintReg(PhysReg, TRI)
             << " needs to be live in to BB#" << MBB->getNumber()
             << ", but is missing from the live-in list.\n";
      llvm_unreachable("Invalid global physical register");
    }
#endif
    FoundUndef |= MBB->pred_empty();

    for (MachineBasicBlock::pred_iterator PI = MBB->pred_begin(),
         PE = MBB->pred_end(); PI != PE; ++PI) {
       MachineBasicBlock *Pred = *PI;

       // Is this a known live-out block?
       if (Seen.test(Pred->getNumber())) {
         if (VNInfo *VNI = Map[Pred].first) {
           if (TheVNI && TheVNI != VNI)
             UniqueVNI = false;
           TheVNI = VNI;
         }
         continue;
       }

       SlotIndex Start, End;
       std::tie(Start, End) = Indexes->getMBBRange(Pred);

       // First time we see Pred.  Try to determine the live-out value, but set
       // it as null if Pred is live-through with an unknown value.
       auto EP = LR.extendInBlock(Undefs, Start, End);
       VNInfo *VNI = EP.first;
       FoundUndef |= EP.second;
       setLiveOutValue(Pred, VNI);
       if (VNI) {
         if (TheVNI && TheVNI != VNI)
           UniqueVNI = false;
         TheVNI = VNI;
       }
       if (VNI || EP.second)
         continue;

       // No, we need a live-in value for Pred as well
       if (Pred != &UseMBB)
         WorkList.push_back(Pred->getNumber());
       else
          // Loopback to UseMBB, so value is really live through.
         Use = SlotIndex();
    }
  }

  LiveIn.clear();
  FoundUndef |= (TheVNI == nullptr);
  if (Undefs.size() > 0 && FoundUndef)
    UniqueVNI = false;

  // Both updateSSA() and LiveRangeUpdater benefit from ordered blocks, but
  // neither require it. Skip the sorting overhead for small updates.
  if (WorkList.size() > 4)
    array_pod_sort(WorkList.begin(), WorkList.end());

  // If a unique reaching def was found, blit in the live ranges immediately.
  if (UniqueVNI) {
    assert(TheVNI != nullptr);
    LiveRangeUpdater Updater(&LR);
    for (unsigned BN : WorkList) {
      SlotIndex Start, End;
      std::tie(Start, End) = Indexes->getMBBRange(BN);
      // Trim the live range in UseMBB.
      if (BN == UseMBBNum && Use.isValid())
        End = Use;
      else
        Map[MF->getBlockNumbered(BN)] = LiveOutPair(TheVNI, nullptr);
      Updater.add(Start, End, TheVNI);
    }
    return true;
  }

  // Prepare the defined/undefined bit vectors.
  auto EF = EntryInfoMap.find(&LR);
  if (EF == EntryInfoMap.end()) {
    unsigned N = MF->getNumBlockIDs();
    EF = EntryInfoMap.insert({&LR, {BitVector(), BitVector()}}).first;
    EF->second.first.resize(N);
    EF->second.second.resize(N);
  }
  BitVector &DefOnEntry = EF->second.first;
  BitVector &UndefOnEntry = EF->second.second;

  // Multiple values were found, so transfer the work list to the LiveIn array
  // where UpdateSSA will use it as a work list.
  LiveIn.reserve(WorkList.size());
  for (unsigned BN : WorkList) {
    MachineBasicBlock *MBB = MF->getBlockNumbered(BN);
    if (Undefs.size() > 0 && !isDefOnEntry(LR, Undefs, *MBB, DefOnEntry, UndefOnEntry))
      continue;
    addLiveInBlock(LR, DomTree->getNode(MBB));
    if (MBB == &UseMBB)
      LiveIn.back().Kill = Use;
  }

  return false;
}