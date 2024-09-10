void StackAllocationPromoter::promoteAllocationToPhi() {
  DEBUG(llvm::dbgs() << "*** Placing Phis for : " << *ASI);

  // A list of blocks that will require new Phi values.
  BlockSet PhiBlocks;

  // The "piggy-bank" data-structure that we use for processing the dom-tree
  // bottom-up.
  NodePriorityQueue PQ;

  // Collect all of the stores into the AllocStack. We know that at this point
  // we have at most one store per block.
  for (auto UI = ASI->use_begin(), E = ASI->use_end(); UI != E; ++UI) {
    SILInstruction *II = UI->getUser();
    // We need to place Phis for this block.
    if (isa<StoreInst>(II)) {
      // If the block is in the dom tree (dominated by the entry block).
      if (DomTreeNode *Node = DT->getNode(II->getParent()))
        PQ.push(std::make_pair(Node, DomTreeLevels[Node]));
    }
  }

  DEBUG(llvm::dbgs() << "*** Found: " << PQ.size() << " Defs\n");

  // A list of nodes for which we already calculated the dominator frontier.
  llvm::SmallPtrSet<DomTreeNode *, 32> Visited;

  SmallVector<DomTreeNode *, 32> Worklist;

  // Scan all of the definitions in the function bottom-up using the priority
  // queue.
  while (!PQ.empty()) {
    DomTreeNodePair RootPair = PQ.top();
    PQ.pop();
    DomTreeNode *Root = RootPair.first;
    unsigned RootLevel = RootPair.second;

    // Walk all dom tree children of Root, inspecting their successors. Only
    // J-edges, whose target level is at most Root's level are added to the
    // dominance frontier.
    Worklist.clear();
    Worklist.push_back(Root);

    while (!Worklist.empty()) {
      DomTreeNode *Node = Worklist.pop_back_val();
      SILBasicBlock *BB = Node->getBlock();

      // For all successors of the node:
      for (auto &Succ : BB->getSuccessors()) {
        DomTreeNode *SuccNode = DT->getNode(Succ);

        // Skip D-edges (edges that are dom-tree edges).
        if (SuccNode->getIDom() == Node)
          continue;

        // Ignore J-edges that point to nodes that are not smaller or equal
        // to the root level.
        unsigned SuccLevel = DomTreeLevels[SuccNode];
        if (SuccLevel > RootLevel)
          continue;

        // Ignore visited nodes.
        if (!Visited.insert(SuccNode).second)
          continue;

        // If the new PHInode is not dominated by the allocation then it's dead.
        if (!DT->dominates(ASI->getParent(), SuccNode->getBlock()))
            continue;

        // If the new PHInode is properly dominated by the deallocation then it
        // is obviously a dead PHInode, so we don't need to insert it.
        if (DSI && DT->properlyDominates(DSI->getParent(),
                                         SuccNode->getBlock()))
          continue;

        // The successor node is a new PHINode. If this is a new PHI node
        // then it may require additional definitions, so add it to the PQ.
        if (PhiBlocks.insert(Succ).second)
          PQ.push(std::make_pair(SuccNode, SuccLevel));
      }

      // Add the children in the dom-tree to the worklist.
      for (auto CI = Node->begin(), CE = Node->end(); CI != CE; ++CI)
        if (!Visited.count(*CI))
          Worklist.push_back(*CI);
    }
  }

  DEBUG(llvm::dbgs() << "*** Found: " << PhiBlocks.size() << " new PHIs\n");
  NumPhiPlaced += PhiBlocks.size();

  // At this point we calculated the locations of all of the new Phi values.
  // Next, add the Phi values and promote all of the loads and stores into the
  // new locations.

  // Replace the dummy values with new block arguments.
  addBlockArguments(PhiBlocks);

  // Hook up the Phi nodes, loads, and debug_value_addr with incoming values.
  fixBranchesAndUses(PhiBlocks);

  DEBUG(llvm::dbgs() << "*** Finished placing Phis ***\n");
}