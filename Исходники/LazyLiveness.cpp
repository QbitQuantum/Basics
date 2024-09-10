bool LazyLiveness::vregLiveIntoMBB(unsigned vreg, MachineBasicBlock* MBB) {
  MachineDominatorTree& MDT = getAnalysis<MachineDominatorTree>();
  
  MachineBasicBlock* DefMBB = MRI->def_begin(vreg)->getParent();
  unsigned def = preorder[DefMBB];
  unsigned max_dom = 0;
  for (df_iterator<MachineDomTreeNode*> DI = df_begin(MDT[DefMBB]),
       DE = df_end(MDT[DefMBB]); DI != DE; ++DI) {
    if (preorder[DI->getBlock()] > max_dom) {
      max_dom = preorder[(*DI)->getBlock()];
    }
  }
  
  if (preorder[MBB] <= def || max_dom < preorder[MBB])
    return false;
  
  SparseBitVector<128>::iterator I = tv[MBB].begin();
  while (I != tv[MBB].end() && *I <= def) ++I;
  while (I != tv[MBB].end() && *I < max_dom) {
    for (MachineRegisterInfo::use_iterator UI = MRI->use_begin(vreg),
         UE = MachineRegisterInfo::use_end(); UI != UE; ++UI) {
      MachineBasicBlock* UseMBB = UI->getParent();
      if (rv[rev_preorder[*I]].test(preorder[UseMBB]))
        return true;
      
      unsigned t_dom = 0;
      for (df_iterator<MachineDomTreeNode*> DI =
           df_begin(MDT[rev_preorder[*I]]), DE = df_end(MDT[rev_preorder[*I]]); 
           DI != DE; ++DI)
        if (preorder[DI->getBlock()] > t_dom) {
          max_dom = preorder[(*DI)->getBlock()];
        }
      I = tv[MBB].begin();
      while (I != tv[MBB].end() && *I < t_dom) ++I;
    }
  }
  
  return false;
}