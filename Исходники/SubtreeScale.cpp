/** Perform the move */
double SubtreeScale::performSimpleMove( void ) {
    
    // Get random number generator    
    RandomNumberGenerator* rng     = GLOBAL_RNG;
    
    TimeTree& tau = variable->getValue();
    
    // pick a random node which is not the root and neither the direct descendant of the root
    TopologyNode* node;
    do {
        double u = rng->uniform01();
        size_t index = size_t( std::floor(tau.getNumberOfNodes() * u) );
        node = &tau.getNode(index);
    } while ( node->isRoot() || node->isTip() );
    
    TopologyNode& parent = node->getParent();
    
    // we need to work with the times
    double parent_age  = parent.getAge();
    double my_age      = node->getAge();
    
    // now we store all necessary values
    storedNode = node;
    storedAge = my_age;
        
    // draw new ages and compute the hastings ratio at the same time
    double my_new_age = parent_age * rng->uniform01();
    
    double scalingFactor = my_new_age / my_age;
    
    size_t nNodes = node->getNumberOfNodesInSubtree(false);
    
    // rescale the subtrees
    TreeUtilities::rescaleSubtree(&tau, node, scalingFactor );
    
    // compute the Hastings ratio
    double lnHastingsratio = (nNodes > 1 ? log( scalingFactor ) * (nNodes-1) : 0.0 );
    
    return lnHastingsratio;
}