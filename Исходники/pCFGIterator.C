// transfer function
// decides if the given pSet is blocked or split or dead
// if needs to split, pushes the descendants into splitPSetNodes
// if split -> pushes the ConstrGraph corresponding to that into splitConditions
bool pCFGIterator::transfer(const pCFGNode& n, 
                            unsigned int pSet, 
                            const Function& func,                  
                            NodeState& state, 
                            const vector<Lattice*>& dfInfo,
                            bool& isDeadPSet, 
                            bool& isSplitPSet, 
                            vector<DataflowNode>& splitPSetNodes,
                            bool& isSplitPNode,                             
                            bool& isBlockPSet,
                            bool& isMergePSet)
{
    bool modified = false;
    // Get the ROSE_VisitorPattern instance
    boost::shared_ptr<IntraPCFGTransferVisitor> 
        transferVisitor = boost::shared_ptr<IntraPCFGTransferVisitor> 
        (new pCFGIteratorTransfer (n, pSet, func, state, dfInfo, isDeadPSet, isSplitPSet, splitPSetNodes, isSplitPNode, isBlockPSet, isMergePSet, this->mda));

    // get the node on which visitor pattern needs to applied
    const DataflowNode& dfNode = n.getCurNode(pSet);

    // get the node
    SgNode* sgn = dfNode.getNode();

    // set the handler
    sgn->accept(*transferVisitor);

    modified = transferVisitor->finish() || modified;

    return modified;    
}