 /// Set each node's subtree ID to the representative ID and record connections
 /// between trees.
 void finalize() {
   SubtreeClasses.compress();
   R.SubtreeConnections.resize(SubtreeClasses.getNumClasses());
   R.SubtreeConnectLevels.resize(SubtreeClasses.getNumClasses());
   DEBUG(dbgs() << R.getNumSubtrees() << " subtrees:\n");
   for (unsigned Idx = 0, End = R.DFSData.size(); Idx != End; ++Idx) {
     R.DFSData[Idx].SubtreeID = SubtreeClasses[Idx];
     DEBUG(dbgs() << "  SU(" << Idx << ") in tree "
           << R.DFSData[Idx].SubtreeID << '\n');
   }
   for (std::vector<std::pair<const SUnit*, const SUnit*> >::const_iterator
          I = ConnectionPairs.begin(), E = ConnectionPairs.end();
        I != E; ++I) {
     unsigned PredTree = SubtreeClasses[I->first->NodeNum];
     unsigned SuccTree = SubtreeClasses[I->second->NodeNum];
     if (PredTree == SuccTree)
       continue;
     unsigned Depth = I->first->getDepth();
     addConnection(PredTree, SuccTree, Depth);
     addConnection(SuccTree, PredTree, Depth);
   }
 }