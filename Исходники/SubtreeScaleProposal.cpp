/**
 * Perform the proposal.
 *
 * A Beta-simplex proposal randomly changes some values of a simplex, although the other values
 * change too because of the renormalization.
 * First, some random indices are drawn. Then, the proposal draws a new somplex
 *   u ~ Beta(val[index] * alpha)
 * where alpha is the tuning parameter.The new value is set to u.
 * The simplex is then renormalized.
 *
 * \return The hastings ratio.
 */
double SubtreeScaleProposal::doProposal( void )
{
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
    
    // lower bound
    double min_age = 0.0;
    TreeUtilities::getOldestTip(&tau, node, min_age);
    
    // draw new ages and compute the hastings ratio at the same time
    double my_new_age = min_age + (parent_age - min_age) * rng->uniform01();
    
    double scalingFactor = my_new_age / my_age;
    
    size_t nNodes = node->getNumberOfNodesInSubtree(false);
    
    // rescale the subtrees
    TreeUtilities::rescaleSubtree(&tau, node, scalingFactor );
    
    if (min_age != 0.0)
    {
        for (size_t i = 0; i < tau.getNumberOfTips(); i++)
        {
            if (tau.getNode(i).getAge() < 0.0) {
                return RbConstants::Double::neginf;
            }
        }
    }
    
    // compute the Hastings ratio
    double lnHastingsratio = (nNodes > 1 ? log( scalingFactor ) * (nNodes-1) : 0.0 );
    
    return lnHastingsratio;
    
}