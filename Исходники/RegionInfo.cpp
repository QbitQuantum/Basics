BasicBlock *RegionInfo::getMaxRegionExit(BasicBlock *BB) const {
  BasicBlock *Exit = NULL;

  while (true) {
    // Get largest region that starts at BB.
    Region *R = getRegionFor(BB);
    while (R && R->getParent() && R->getParent()->getEntry() == BB)
      R = R->getParent();

    // Get the single exit of BB.
    if (R && R->getEntry() == BB)
      Exit = R->getExit();
    else if (++succ_begin(BB) == succ_end(BB))
      Exit = *succ_begin(BB);
    else // No single exit exists.
      return Exit;

    // Get largest region that starts at Exit.
    Region *ExitR = getRegionFor(Exit);
    while (ExitR && ExitR->getParent()
           && ExitR->getParent()->getEntry() == Exit)
      ExitR = ExitR->getParent();

    for (pred_iterator PI = pred_begin(Exit), PE = pred_end(Exit); PI != PE;
         ++PI)
      if (!R->contains(*PI) && !ExitR->contains(*PI))
        break;

    // This stops infinite cycles.
    if (DT->dominates(Exit, BB))
      break;

    BB = Exit;
  }

  return Exit;
}