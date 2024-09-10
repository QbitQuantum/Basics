/// Handle a rare case where the disintegrated nodes instructions
/// no longer dominate all their uses. Not sure if this is really nessasary
void StructurizeCFG::rebuildSSA() {
  SSAUpdater Updater;
  for (Region::block_iterator I = ParentRegion->block_begin(),
                              E = ParentRegion->block_end();
       I != E; ++I) {

    BasicBlock *BB = *I;
    for (BasicBlock::iterator II = BB->begin(), IE = BB->end();
         II != IE; ++II) {

      bool Initialized = false;
      for (Use *I = &II->use_begin().getUse(), *Next; I; I = Next) {

        Next = I->getNext();

        Instruction *User = cast<Instruction>(I->getUser());
        if (User->getParent() == BB) {
          continue;

        } else if (PHINode *UserPN = dyn_cast<PHINode>(User)) {
          if (UserPN->getIncomingBlock(*I) == BB)
            continue;
        }

        if (DT->dominates(II, User))
          continue;

        if (!Initialized) {
          Value *Undef = UndefValue::get(II->getType());
          Updater.Initialize(II->getType(), "");
          Updater.AddAvailableValue(&Func->getEntryBlock(), Undef);
          Updater.AddAvailableValue(BB, II);
          Initialized = true;
        }
        Updater.RewriteUseAfterInsertions(*I);
      }
    }
  }
}