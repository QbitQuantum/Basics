/** Perform the move */
void RateAgeBetaShift::performMove( double heat, bool raiseLikelihoodOnly )
{

    // Get random number generator
    RandomNumberGenerator* rng     = GLOBAL_RNG;

    TimeTree& tau = tree->getValue();

    // pick a random node which is not the root and neithor the direct descendant of the root
    TopologyNode* node;
    size_t nodeIdx = 0;
    do {
        double u = rng->uniform01();
        nodeIdx = size_t( std::floor(tau.getNumberOfNodes() * u) );
        node = &tau.getNode(nodeIdx);
    } while ( node->isRoot() || node->isTip() );

    TopologyNode& parent = node->getParent();

    // we need to work with the times
    double parent_age  = parent.getAge();
    double my_age      = node->getAge();
    double child_Age   = node->getChild( 0 ).getAge();
    if ( child_Age < node->getChild( 1 ).getAge())
    {
        child_Age = node->getChild( 1 ).getAge();
    }

    // now we store all necessary values
    storedNode = node;
    storedAge = my_age;


    storedRates[nodeIdx] = rates[nodeIdx]->getValue();
    for (size_t i = 0; i < node->getNumberOfChildren(); i++)
    {
        size_t childIdx = node->getChild(i).getIndex();
        storedRates[childIdx] = rates[childIdx]->getValue();
    }


    // draw new ages and compute the hastings ratio at the same time
    double m = (my_age-child_Age) / (parent_age-child_Age);
    double a = delta * m + 1.0;
    double b = delta * (1.0-m) + 1.0;
    double new_m = RbStatistics::Beta::rv(a, b, *rng);
    double my_new_age = (parent_age-child_Age) * new_m + child_Age;

    // compute the Hastings ratio
    double forward = RbStatistics::Beta::lnPdf(a, b, new_m);
    double new_a = delta * new_m + 1.0;
    double new_b = delta * (1.0-new_m) + 1.0;
    double backward = RbStatistics::Beta::lnPdf(new_a, new_b, m);

    // set the age
    tau.setAge( node->getIndex(), my_new_age );
    tree->touch();

    double treeProbRatio = tree->getLnProbabilityRatio();


    // set the rates
    rates[nodeIdx]->setValue( new double((node->getParent().getAge() - my_age) * storedRates[nodeIdx] / (node->getParent().getAge() - my_new_age)));
    double ratesProbRatio = rates[nodeIdx]->getLnProbabilityRatio();

    for (size_t i = 0; i < node->getNumberOfChildren(); i++)
    {
        size_t childIdx = node->getChild(i).getIndex();
        rates[childIdx]->setValue( new double((my_age - node->getChild(i).getAge()) * storedRates[childIdx] / (my_new_age - node->getChild(i).getAge())));
        ratesProbRatio += rates[childIdx]->getLnProbabilityRatio();

    }

    std::set<DagNode*> affected;
    tree->getAffectedNodes( affected );
    double lnProbRatio = 0;
    for (std::set<DagNode*>::iterator it = affected.begin(); it != affected.end(); ++it)
    {
        (*it)->touch();
        lnProbRatio += (*it)->getLnProbabilityRatio();
    }

    if ( fabs(lnProbRatio) > 1E-6 ) {
//        throw RbException("Likelihood shortcut computation failed in rate-age-proposal.");
        std::cout << "Likelihood shortcut computation failed in rate-age-proposal." << std::endl;
    }

    double hastingsRatio = backward - forward;
    double lnAcceptanceRatio = treeProbRatio + ratesProbRatio + hastingsRatio;

    if (lnAcceptanceRatio >= 0.0)
    {
        numAccepted++;

        tree->keep();
        rates[nodeIdx]->keep();
        for (size_t i = 0; i < node->getNumberOfChildren(); i++)
        {
            size_t childIdx = node->getChild(i).getIndex();
            rates[childIdx]->keep();
        }
    }
    else if (lnAcceptanceRatio < -300.0)
    {
        reject();
        tree->restore();
        rates[nodeIdx]->restore();
        for (size_t i = 0; i < node->getNumberOfChildren(); i++)
        {
            size_t childIdx = node->getChild(i).getIndex();
            rates[childIdx]->restore();
        }
    }
    else
    {
        double r = exp(lnAcceptanceRatio);
        // Accept or reject the move
        double u = GLOBAL_RNG->uniform01();
        if (u < r)
        {
            numAccepted++;

            //keep
            tree->keep();
            rates[nodeIdx]->keep();
            for (size_t i = 0; i < node->getNumberOfChildren(); i++)
            {
                size_t childIdx = node->getChild(i).getIndex();
                rates[childIdx]->keep();
            }
        }
        else
        {
            reject();
            tree->restore();
            rates[nodeIdx]->restore();
            for (size_t i = 0; i < node->getNumberOfChildren(); i++)
            {
                size_t childIdx = node->getChild(i).getIndex();
                rates[childIdx]->restore();
            }
        }
    }

}