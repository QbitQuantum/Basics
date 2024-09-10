bool RegToMem::runOnFunction(Function &F) {
  if (F.isDeclaration())
    return false;

  // Insert all new allocas into entry block.
  BasicBlock *BBEntry = &F.getEntryBlock();
  assert(pred_begin(BBEntry) == pred_end(BBEntry) &&
         "Entry block to function must not have predecessors!");

  // Find first non-alloca instruction and create insertion point. This is
  // safe if block is well-formed: it always have terminator, otherwise
  // we'll get and assertion.
  BasicBlock::iterator I = BBEntry->begin();
  while (isa<AllocaInst>(I)) ++I;

  CastInst *AllocaInsertionPoint =
    new BitCastInst(Constant::getNullValue(Type::getInt32Ty(F.getContext())),
                    Type::getInt32Ty(F.getContext()),
                    "reg2mem alloca point", I);

  // Find the escaped instructions. But don't create stack slots for
  // allocas in entry block.
  std::list<Instruction*> WorkList;
  for (Function::iterator ibb = F.begin(), ibe = F.end();
       ibb != ibe; ++ibb)
    for (BasicBlock::iterator iib = ibb->begin(), iie = ibb->end();
         iib != iie; ++iib) {
      if (!(isa<AllocaInst>(iib) && iib->getParent() == BBEntry) &&
          valueEscapes(iib)) {
        WorkList.push_front(&*iib);
      }
    }

  // Demote escaped instructions
  NumRegsDemoted += WorkList.size();
  for (std::list<Instruction*>::iterator ilb = WorkList.begin(),
       ile = WorkList.end(); ilb != ile; ++ilb)
    DemoteRegToStack(**ilb, false, AllocaInsertionPoint);

  WorkList.clear();

  // Find all phi's
  for (Function::iterator ibb = F.begin(), ibe = F.end();
       ibb != ibe; ++ibb)
    for (BasicBlock::iterator iib = ibb->begin(), iie = ibb->end();
         iib != iie; ++iib)
      if (isa<PHINode>(iib))
        WorkList.push_front(&*iib);

  // Demote phi nodes
  NumPhisDemoted += WorkList.size();
  for (std::list<Instruction*>::iterator ilb = WorkList.begin(),
       ile = WorkList.end(); ilb != ile; ++ilb)
    DemotePHIToStack(cast<PHINode>(*ilb), AllocaInsertionPoint);

  return true;
}