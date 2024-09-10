void BrownianPhyloProcess::recursiveSimulate(const TopologyNode& from)  {
    
    size_t index = from.getIndex();
    
    if (! from.isRoot())    {
        
        // x ~ normal(x_up, sigma^2 * branchLength)
        
        size_t upindex = from.getParent().getIndex();
        double standDev = sigma->getValue() * sqrt(from.getBranchLength());
        double mean = (*value)[upindex] + drift->getValue() * from.getBranchLength();

        // simulate the new Val
        RandomNumberGenerator* rng = GLOBAL_RNG;
        (*value)[index] = RbStatistics::Normal::rv( mean, standDev, *rng);
     
    }
    
    // propagate forward
    size_t numChildren = from.getNumberOfChildren();
    for (size_t i = 0; i < numChildren; ++i) {
        recursiveSimulate(from.getChild(i));
    }
    
}