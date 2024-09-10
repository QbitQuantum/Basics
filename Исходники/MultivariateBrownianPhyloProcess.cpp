double MultivariateBrownianPhyloProcess::recursiveLnProb( const TopologyNode& from ) {
    
    double lnProb = 0.0;
    size_t index = from.getIndex();
    std::vector<double> val = (*value)[index];
    
    if (! from.isRoot()) {
        
        if (1)  {
//        if (dirtyNodes[index])  {

            // x ~ normal(x_up, sigma^2 * branchLength)

            size_t upindex = from.getParent().getIndex();
            std::vector<double> upval = (*value)[upindex];

            const MatrixReal& om = sigma->getValue().getInverse();

            double s2 = 0;
            for (size_t i = 0; i < getDim(); i++) {
                double tmp = 0;
                for (size_t j = 0; j < getDim(); j++) {
                    tmp += om[i][j] * (val[j] - upval[j]);
                }
                s2 += (val[i] - upval[i]) * tmp;
            }

            double logprob = 0;
            logprob -= 0.5 * s2 / from.getBranchLength();
            logprob -= 0.5 * (sigma->getValue().getLogDet() + sigma->getValue().getDim() * log(from.getBranchLength()));
            nodeLogProbs[index] = logprob;
            dirtyNodes[index] = false;
        }
        lnProb += nodeLogProbs[index];
    }
    
    // propagate forward
    size_t numChildren = from.getNumberOfChildren();
    
    for (size_t i = 0; i < numChildren; ++i) {
        lnProb += recursiveLnProb(from.getChild(i));
    }
    
    return lnProb;
    
}