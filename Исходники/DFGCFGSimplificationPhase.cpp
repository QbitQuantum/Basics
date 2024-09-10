    void mergeBlocks(
        BasicBlock* firstBlock, BasicBlock* secondBlock,
        Vector<BasicBlock*, 1> jettisonedBlocks)
    {
        // This will add all of the nodes in secondBlock to firstBlock, but in so doing
        // it will also ensure that any GetLocals from the second block that refer to
        // SetLocals in the first block are relinked. If jettisonedBlock is not NoBlock,
        // then Phantoms are inserted for anything that the jettisonedBlock would have
        // kept alive.
        
        // Remove the terminal of firstBlock since we don't need it anymore. Well, we don't
        // really remove it; we actually turn it into a check.
        Node* terminal = firstBlock->terminal();
        ASSERT(terminal->isTerminal());
        NodeOrigin boundaryNodeOrigin = terminal->origin;
        terminal->remove();
        ASSERT(terminal->refCount() == 1);
        
        for (unsigned i = jettisonedBlocks.size(); i--;) {
            BasicBlock* jettisonedBlock = jettisonedBlocks[i];
            
            // Time to insert ghosties for things that need to be kept alive in case we OSR
            // exit prior to hitting the firstBlock's terminal, and end up going down a
            // different path than secondBlock.
            
            for (size_t i = 0; i < jettisonedBlock->variablesAtHead.numberOfArguments(); ++i)
                keepOperandAlive(firstBlock, jettisonedBlock, boundaryNodeOrigin, virtualRegisterForArgument(i));
            for (size_t i = 0; i < jettisonedBlock->variablesAtHead.numberOfLocals(); ++i)
                keepOperandAlive(firstBlock, jettisonedBlock, boundaryNodeOrigin, virtualRegisterForLocal(i));
        }
        
        for (size_t i = 0; i < secondBlock->phis.size(); ++i)
            firstBlock->phis.append(secondBlock->phis[i]);

        for (size_t i = 0; i < secondBlock->size(); ++i)
            firstBlock->append(secondBlock->at(i));
        
        ASSERT(firstBlock->terminal()->isTerminal());
        
        // Fix the predecessors of my new successors. This is tricky, since we are going to reset
        // all predecessors anyway due to reachability analysis. But we need to fix the
        // predecessors eagerly to ensure that we know what they are in case the next block we
        // consider in this phase wishes to query the predecessors of one of the blocks we
        // affected.
        for (unsigned i = firstBlock->numSuccessors(); i--;) {
            BasicBlock* successor = firstBlock->successor(i);
            for (unsigned j = 0; j < successor->predecessors.size(); ++j) {
                if (successor->predecessors[j] == secondBlock)
                    successor->predecessors[j] = firstBlock;
            }
        }
        
        // Fix the predecessors of my former successors. Again, we'd rather not do this, but it's
        // an unfortunate necessity. See above comment.
        for (unsigned i = jettisonedBlocks.size(); i--;)
            fixJettisonedPredecessors(firstBlock, jettisonedBlocks[i]);
        
        firstBlock->valuesAtTail = secondBlock->valuesAtTail;
        firstBlock->cfaBranchDirection = secondBlock->cfaBranchDirection;
        
        m_graph.killBlock(secondBlock);
    }