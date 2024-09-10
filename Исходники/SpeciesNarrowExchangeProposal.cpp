/**
 * Perform the proposal.
 *
 * \return The hastings ratio.
 */
double SpeciesNarrowExchangeProposal::doProposal( void )
{
    
    // empty the previous vectors
    storedGeneTreeNodes.clear();
    storedOldBrothers.clear();
    
    // Get random number generator
    RandomNumberGenerator* rng     = GLOBAL_RNG;
    
    Tree& tau = speciesTree->getValue();
    
    // pick a random node which is not the root and neithor a direct descendant of the root
    TopologyNode* node;
    do {
        double u = rng->uniform01();
        size_t index = size_t( std::floor(tau.getNumberOfNodes() * u) );
        node = &tau.getNode(index);
    } while ( node->isRoot() || node->getParent().isRoot() );
    
    TopologyNode& parent = node->getParent();
    TopologyNode& grandparent = parent.getParent();
    TopologyNode* uncle = &grandparent.getChild( 0 );
    // check if we got the correct child
    if ( uncle == &parent )
    {
        uncle = &grandparent.getChild( 1 );
    }
    TopologyNode* brother = &parent.getChild( 0 );
    // check if we got the correct child
    if ( brother == node )
    {
        brother = &parent.getChild( 1 );
    }
    
    // we need to work with the times
    double parent_age   = parent.getAge();
    double uncles_age   = uncle->getAge();
    
    if( uncles_age < parent_age )
    {
        failed = false;
        
        double lnHastingsRatio = 0.0;
        
        // now we store all necessary values
        storedChoosenNode   = node;
        storedUncle         = uncle;
        
        // now we need to find for each gene tree the nodes that need to be moved as well
        // only nodes that have a coalescent event within the lifetime of the parents populations
        // from lineages belonging to the chosen node with lineages belonging to the brother population
        // need to be changed
        for ( size_t i=0; i<geneTrees.size(); ++i )
        {
            // get the i-th gene tree
            Tree& geneTree = geneTrees[i]->getValue();
            
            std::vector<TopologyNode*> nodes = getNodesToChange(geneTree, *node, *brother );
            
            // get the set of nodes in my uncles populations
            // these are the nodes that are possible re-attachment points
            std::set<TopologyNode*> new_siblings = getOldestSubtreesNodesInPopulation(geneTree, *uncle);
            std::set<TopologyNode*> old_siblings = getOldestSubtreesNodesInPopulation(geneTree, *brother);
            
            for (size_t j=0; j<nodes.size(); ++j)
            {
                
                TopologyNode *the_gene_node = nodes[i];

                // first we need to compute the backward probability
                std::set<TopologyNode*> old_candidate_siblings = getPossibleSiblings(the_gene_node, old_siblings);
                
                // add the backward probability to the hastings ratio
                lnHastingsRatio += log( old_siblings.size() );
                
                // then we need to compute the forward probability
                std::set<TopologyNode*> new_candidate_siblings = getPossibleSiblings(the_gene_node, new_siblings);
                
                // add the forward  probability to the hastings ratio
                lnHastingsRatio += log( new_candidate_siblings.size() );
                
                // actually pick a new sibling
                size_t new_index = size_t( floor(rng->uniform01() * new_candidate_siblings.size() ) );
                std::set<TopologyNode*>::iterator it = new_candidate_siblings.begin();
                std::advance(it,new_index);
                TopologyNode *new_child = *it;
                
                // store nodes
                storedGeneTreeNodes.push_back( the_gene_node );
                TopologyNode &the_parent = the_gene_node->getParent();
                TopologyNode *old_brother = &the_parent.getChild( 0 );
                if ( old_brother == the_gene_node )
                {
                    old_brother = &the_parent.getChild( 1 );
                }
                storedOldBrothers.push_back( old_brother );
                
                // perform a prune and regraft move
                prune( &the_parent, the_gene_node );
                regraft( the_gene_node, new_child );
                
            }
            
            // Sebastian: This is only for debugging. It makes the code slower. Hopefully it is not necessary anymore.
            //        geneTrees[i]->touch( true );
            
        }
        
        
        // now exchange the two nodes
        grandparent.removeChild( uncle );
        parent.removeChild( node );
        grandparent.addChild( node );
        parent.addChild( uncle );
        node->setParent( &grandparent );
        uncle->setParent( &parent );
        
        return 0.0;
    }
    else
    {
        failed = true;
        return RbConstants::Double::neginf;
    }
    
}