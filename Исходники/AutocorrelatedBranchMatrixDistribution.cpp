void AutocorrelatedBranchMatrixDistribution::recursiveSimulate(const TopologyNode& node, RbVector< RateMatrix > *values, const std::vector< double > &scaledParent) {
    
    // get the index
    size_t nodeIndex = node.getIndex();
    
    // first we simulate our value
    RandomNumberGenerator* rng = GLOBAL_RNG;
    // do we keep our parents values?
    double u = rng->uniform01();
    if ( u < changeProbability->getValue() ) {
        // change
        
        // draw a new value for the base frequencies
        std::vector<double> newParent = RbStatistics::Dirichlet::rv(scaledParent, *rng);
        std::vector<double> newScaledParent = newParent;
        
        // compute the new scaled parent
        std::vector<double>::iterator end = newScaledParent.end();
        for (std::vector<double>::iterator it = newScaledParent.begin(); it != end; ++it) {
            (*it) *= alpha->getValue();
        }
        
        RateMatrix_GTR rm = RateMatrix_GTR( newParent.size() );
        RbPhylogenetics::Gtr::computeRateMatrix( exchangeabilityRates->getValue(), newParent, &rm );
        
        uniqueBaseFrequencies.push_back( newParent );
        uniqueMatrices.push_back( rm );
        matrixIndex[nodeIndex] = uniqueMatrices.size()-1;
        values->insert(nodeIndex, rm);
        
        size_t numChildren = node.getNumberOfChildren();
        if ( numChildren > 0 ) {
            
            for (size_t i = 0; i < numChildren; ++i) {
                const TopologyNode& child = node.getChild(i);
                recursiveSimulate(child,values,newScaledParent);
            }
        }
        
    }
    else {
        // no change
        size_t parentIndex = node.getParent().getIndex();
        values->insert(nodeIndex, uniqueMatrices[ matrixIndex[ parentIndex ] ]);
        
        size_t numChildren = node.getNumberOfChildren();
        if ( numChildren > 0 ) {
            
            for (size_t i = 0; i < numChildren; ++i) {
                const TopologyNode& child = node.getChild(i);
                recursiveSimulate(child,values,scaledParent);
            }
        }
    }
    
}