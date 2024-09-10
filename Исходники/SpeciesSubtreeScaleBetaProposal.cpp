/**
 * Perform the proposal.
 *
 * \return The hastings ratio.
 */
double SpeciesSubtreeScaleBetaProposal::doProposal( void )
{
    
    // Get random number generator
    RandomNumberGenerator* rng     = GLOBAL_RNG;
    
    Tree& tau = speciesTree->getValue();
    
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
    
    // draw new ages
    double current_value = my_age / (parent_age - min_age);
    double a = alpha + 1.0;
    double b = (a-1.0) / current_value - a + 2.0;
    double new_value = RbStatistics::Beta::rv(a, b, *rng);

    // Sebastian: This is for debugging to test if the proposal's acceptance rate is 1.0 as it should be!
//    new_value = current_value;
    
    double my_new_age = new_value * (parent_age - min_age);
    
    double scaling_factor = my_new_age / my_age;
    
    size_t num_nodes = node->getNumberOfNodesInSubtree( false );
    
    for ( size_t i=0; i<geneTrees.size(); ++i )
    {
        // get the i-th gene tree
        Tree& gene_tree = geneTrees[i]->getValue();
        
        std::vector<TopologyNode*> nodes = getOldestNodesInPopulation(gene_tree, *node );
        
        for (size_t j=0; j<nodes.size(); ++j)
        {
            // add the number of nodes that we are going to scale in the subtree
            num_nodes += nodes[j]->getNumberOfNodesInSubtree( false );
            
            if ( nodes[j]->isTip() == true )
            {
                std::cerr << "Trying to scale a tip\n";
            }
            
            if ( nodes[j]->isRoot() == true )
            {
                std::cerr << "Trying to scale the root\n";
            }
            
            // rescale the subtree of this gene tree
            TreeUtilities::rescaleSubtree(&gene_tree, nodes[j], scaling_factor );
            
        }
        
        // Sebastian: This is only for debugging. It makes the code slower. Hopefully it is not necessary anymore.
//        geneTrees[i]->touch( true );
        
    }
    
    // Sebastian: We need to work on a mechanism to make these proposal safe for non-ultrametric trees!
    //    if (min_age != 0.0)
    //    {
    //        for (size_t i = 0; i < tau.getNumberOfTips(); i++)
    //        {
    //            if (tau.getNode(i).getAge() < 0.0)
    //            {
    //                return RbConstants::Double::neginf;
    //            }
    //        }
    //    }
    
    // rescale the subtree of the species tree
    TreeUtilities::rescaleSubtree(&tau, node, scaling_factor );
    
    // compute the Hastings ratio
    double forward = RbStatistics::Beta::lnPdf(a, b, new_value);
    double new_a = alpha + 1.0;
    double new_b = (a-1.0) / new_value - a + 2.0;
    double backward = RbStatistics::Beta::lnPdf(new_a, new_b, current_value);
    double lnHastingsratio = (backward - forward) * (num_nodes-1);
    
    return lnHastingsratio;
}