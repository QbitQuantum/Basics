void BBCloner::UpdateSSA(Function &F) {
  DominatorTree &DT = getAnalysis<DominatorTree>();
  // The function has been greatly modified since the beginning.
  DT.runOnFunction(F);

  vector<pair<Instruction *, Use *> > ToResolve;
  for (ValueToValueMapTy::iterator I = CloneMap.begin();
       I != CloneMap.end();
       ++I) {
    Value *Key = const_cast<Value *>(I->first);
    if (Instruction *OldIns = dyn_cast<Instruction>(Key)) {
      for (Value::use_iterator UI = OldIns->use_begin();
           UI != OldIns->use_end();
           ++UI) {
        if (Instruction *User = dyn_cast<Instruction>(*UI)) {
          if (!DT.dominates(OldIns, User))
            ToResolve.push_back(make_pair(OldIns, &UI.getUse()));
        }
      }
      Instruction *NewIns = cast<Instruction>(I->second);
      for (Value::use_iterator UI = NewIns->use_begin();
           UI != NewIns->use_end();
           ++UI) {
        if (Instruction *User = dyn_cast<Instruction>(*UI)) {
          if (!DT.dominates(NewIns, User)) {
            // Use OldIns intentionally.
            ToResolve.push_back(make_pair(OldIns, &UI.getUse()));
          }
        }
      }
    }
  }

  for (size_t i = 0; i < ToResolve.size(); ) {
    Instruction *OldIns = ToResolve[i].first;
    Instruction *NewIns = cast<Instruction>(CloneMap.lookup(OldIns));
    SSAUpdater SU;
    SU.Initialize(OldIns->getType(), OldIns->getName());
    SU.AddAvailableValue(OldIns->getParent(), OldIns);
    SU.AddAvailableValue(NewIns->getParent(), NewIns);
    size_t j = i;
    while (j < ToResolve.size() && ToResolve[j].first == ToResolve[i].first) {
      SU.RewriteUse(*ToResolve[j].second);
      ++j;
    }
    i = j;
  }
}