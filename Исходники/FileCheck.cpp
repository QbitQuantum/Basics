size_t CheckString::CheckDag(const SourceMgr &SM, StringRef Buffer,
                             std::vector<const Pattern *> &NotStrings,
                             StringMap<StringRef> &VariableTable) const {
  if (DagNotStrings.empty())
    return 0;

  size_t LastPos = 0;
  size_t StartPos = LastPos;

  for (unsigned ChunkNo = 0, e = DagNotStrings.size();
       ChunkNo != e; ++ChunkNo) {
    const Pattern &Pat = DagNotStrings[ChunkNo];

    assert((Pat.getCheckTy() == Check::CheckDAG ||
            Pat.getCheckTy() == Check::CheckNot) &&
           "Invalid CHECK-DAG or CHECK-NOT!");

    if (Pat.getCheckTy() == Check::CheckNot) {
      NotStrings.push_back(&Pat);
      continue;
    }

    assert((Pat.getCheckTy() == Check::CheckDAG) && "Expect CHECK-DAG!");

    size_t MatchLen = 0, MatchPos;

    // CHECK-DAG always matches from the start.
    StringRef MatchBuffer = Buffer.substr(StartPos);
    MatchPos = Pat.Match(MatchBuffer, MatchLen, VariableTable);
    // With a group of CHECK-DAGs, a single mismatching means the match on
    // that group of CHECK-DAGs fails immediately.
    if (MatchPos == StringRef::npos) {
      PrintCheckFailed(SM, Pat.getLoc(), Pat, MatchBuffer, VariableTable);
      return StringRef::npos;
    }
    // Re-calc it as the offset relative to the start of the original string.
    MatchPos += StartPos;

    if (!NotStrings.empty()) {
      if (MatchPos < LastPos) {
        // Reordered?
        SM.PrintMessage(SMLoc::getFromPointer(Buffer.data() + MatchPos),
                        SourceMgr::DK_Error,
                        Prefix + "-DAG: found a match of CHECK-DAG"
                        " reordering across a CHECK-NOT");
        SM.PrintMessage(SMLoc::getFromPointer(Buffer.data() + LastPos),
                        SourceMgr::DK_Note,
                        Prefix + "-DAG: the farthest match of CHECK-DAG"
                        " is found here");
        SM.PrintMessage(NotStrings[0]->getLoc(), SourceMgr::DK_Note,
                        Prefix + "-NOT: the crossed pattern specified"
                        " here");
        SM.PrintMessage(Pat.getLoc(), SourceMgr::DK_Note,
                        Prefix + "-DAG: the reordered pattern specified"
                        " here");
        return StringRef::npos;
      }
      // All subsequent CHECK-DAGs should be matched from the farthest
      // position of all precedent CHECK-DAGs (including this one.)
      StartPos = LastPos;
      // If there's CHECK-NOTs between two CHECK-DAGs or from CHECK to
      // CHECK-DAG, verify that there's no 'not' strings occurred in that
      // region.
      StringRef SkippedRegion = Buffer.substr(LastPos, MatchPos);
      if (CheckNot(SM, SkippedRegion, NotStrings, VariableTable))
        return StringRef::npos;
      // Clear "not strings".
      NotStrings.clear();
    }

    // Update the last position with CHECK-DAG matches.
    LastPos = std::max(MatchPos + MatchLen, LastPos);
  }

  return LastPos;
}