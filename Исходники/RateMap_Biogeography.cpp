void RateMap_Biogeography::calculateTransitionProbabilities(const TopologyNode& node, TransitionProbabilityMatrix &P, size_t charIdx) const
{

    double startAge = ( node.isRoot() ? 1e10 : node.getParent().getAge() );
    double endAge = node.getAge();
    double currAge = startAge;
    
    double r = ( branchHeterogeneousClockRates ? heterogeneousClockRates[node.getIndex()] : homogeneousClockRate );
    const std::vector<double>& glr = ( branchHeterogeneousGainLossRates ? heterogeneousGainLossRates[node.getIndex()] : homogeneousGainLossRates );
    
    // start at earliest epoch
    int epochIdx = getEpochIndex(startAge);
    

    // initialize P = I
    P[0][0] = 1.0;
    P[0][1] = 0.0;
    P[1][0] = 0.0;
    P[1][1] = 1.0;
    

    
    bool stop = false;
    while (!stop)
    {
        // get dispersal and extinction rates for site
        size_t idx = this->numCharacters * epochIdx + charIdx;
        
        double dispersalRate  = ( (availableAreaVector[ idx ] > 0) ? 1.0 : 0.0);
        double extinctionRate = ( (availableAreaVector[ idx ] > 0) ? 1.0 : 1e10);
        
        // get age of start of next oldest epoch
        double epochAge = epochs[ epochIdx ];
        
        // get next oldest age boundary (node or epoch)
        double incrAge = epochAge;
        
        // no more epochs, exit loop after computation
        if (endAge >= epochAge)
        {
            incrAge = endAge;
            stop = true;
        }
        
        // get branch length
        double diffAge = currAge - incrAge;
        
        // transition probabilities w/ sum-product
        double glr0 = glr[0] * extinctionRate;
        double glr1 = glr[1] * dispersalRate;
        double expPart = exp( -(glr0 + glr1) * r * diffAge);
        double p = glr0 / (glr0 + glr1);
        double q = 1.0 - p;
        
        double p00 = (p + q * expPart);
        double p01 = (q - q * expPart);
        double p10 = (p - p * expPart);
        double p11 = (q + p * expPart);

        double q00 = P[0][0];
        double q01 = P[0][1];
        double q10 = P[1][0];
        double q11 = P[1][1];
        
        P[0][0] = p00 * q00 + p01 * q10;
        P[0][1] = p00 * q01 + p01 * q11;
        P[1][0] = p10 * q00 + p11 * q10;
        P[1][1] = p10 * q01 + p11 * q11;
        
//        std::cout << P[0][0] << "," << P[0][1] << ";" << P[1][0] << "," << P[1][1] << "\n";
        
        
        
        if (!stop)
        {
            epochIdx += 1;
            currAge = epochAge;
        }
    }
}