bool TestFilteredStandardLikelihood::run( void ) {
    std::cerr << "  starting TestFilteredStandardLikelihood...\n" ;
    /* First, we read in the data */
    // the matrix
    NclReader reader = NclReader();
    std::vector<AbstractCharacterData*> data = reader.readMatrices(alignmentFilename);
    AbstractDiscreteCharacterData * discrD = dynamic_cast<AbstractDiscreteCharacterData *>(data[0]);
#   if defined(USE_TIME_TREE)
        std::vector<TimeTree*> trees = reader.readTimeTrees( treeFilename );
        ConstantNode<TimeTree> *tau = new ConstantNode<TimeTree>( "tau", new TimeTree( *trees[0] ) );
#   else
        std::vector<BranchLengthTree*> *trees = reader.readBranchLengthTrees( treeFilename );
        ConstantNode<BranchLengthTree> *tau = new ConstantNode<BranchLengthTree>( "tau", new BranchLengthTree( *(*trees)[0] ) );
#   endif
    std::cout << "tau:\t" << tau->getValue() << std::endl;
#   if defined(USE_3_STATES)
        const size_t numStates = 3;
#   else
        const size_t numStates = 4;
#   endif
    size_t numChar = discrD->getNumberOfCharacters();

#   if defined(USE_RATE_HET)
        ConstantNode<double>* shape = new ConstantNode<double>("alpha", new double(0.5) );
        ConstantNode<double>* rate = new ConstantNode<double>("", new double(0.5) );
        ConstantNode<int>* numCats = new ConstantNode<int>("ncat", new int(4) );

        DiscretizeGammaFunction *dFunc = new DiscretizeGammaFunction( shape, rate, numCats, false );
        DeterministicNode<RbVector<double> > *site_rates_norm_2 = new DeterministicNode<RbVector<double> >( "site_rates_norm", dFunc );
        std::cout << "rates:\t" << site_rates_norm_2->getValue() << std::endl;
#   endif

#if defined(USE_3_STATES) && defined(USE_NUCLEOTIDE)
#error "cannot use 3 state and nucleotide type"
#endif
#if defined(USE_3_STATES) && defined(USE_GTR_RATE_MAT)
#error "cannot use 3 state and USE_GTR_RATE_MAT"
#endif

#   if defined(USE_GTR_RATE_MAT)
        ConstantNode<RbVector<double> > *pi = new ConstantNode<RbVector<double> >( "pi", new RbVector<double>(4, 1.0/4.0) );
        ConstantNode<RbVector<double> > *er = new ConstantNode<RbVector<double> >( "er", new RbVector<double>(6, 1.0/6.0) );
        DeterministicNode<RateMatrix> *q = new DeterministicNode<RateMatrix>( "Q", new GtrRateMatrixFunction(er, pi) );
        std::cout << "Q:\t" << q->getValue() << std::endl;
#       if defined (USE_NUCLEOTIDE)
#           if defined(USE_TIME_TREE)
                PhyloCTMCSiteHomogeneousNucleotide<DnaState, TimeTree> *charModel = new PhyloCTMCSiteHomogeneousNucleotide<DnaState, TimeTree>(tau, false, numChar);
#           else
                PhyloCTMCSiteHomogeneousNucleotide<DnaState, BranchLengthTree> *charModel = new PhyloCTMCSiteHomogeneousNucleotide<DnaState, BranchLengthTree>(tau, false, numChar );
#           endif
#       else
#           if defined(USE_TIME_TREE)
                PhyloCTMCSiteHomogeneous<DnaState, TimeTree> *charModel = new PhyloCTMCSiteHomogeneous<DnaState, TimeTree>(tau, 4, false, numChar);
#           else
                PhyloCTMCSiteHomogeneous<DnaState, BranchLengthTree> *charModel = new PhyloCTMCSiteHomogeneous<DnaState, BranchLengthTree>(tau, 4, false, numChar );
#           endif
#       endif
#   else
        DeterministicNode<RateMatrix> *q = new DeterministicNode<RateMatrix>( "Q", new JcRateMatrixFunction(numStates));
#       if defined (USE_NUCLEOTIDE)
#          if defined(USE_TIME_TREE)
                PhyloCTMCSiteHomogeneousNucleotide<StandardState, TimeTree> *charModel = new PhyloCTMCSiteHomogeneousNucleotide<StandardState, TimeTree>(tau, false, numChar);
#           else
                PhyloCTMCSiteHomogeneousNucleotide<StandardState, BranchLengthTree> *charModel = new PhyloCTMCSiteHomogeneousNucleotide<StandardState, BranchLengthTree>(tau, false, numChar );
#           endif
#       else
#          if defined(USE_TIME_TREE)
                PhyloCTMCSiteHomogeneous<StandardState, TimeTree> *charModel = new PhyloCTMCSiteHomogeneous<StandardState, TimeTree>(tau, numStates, false, numChar);
#           else
                PhyloCTMCSiteHomogeneous<StandardState, BranchLengthTree> *charModel = new PhyloCTMCSiteHomogeneous<StandardState, BranchLengthTree>(tau, numStates, false, numChar );
#           endif
#       endif
#   endif
#   if defined(USE_RATE_HET)
        charModel->setSiteRates( site_rates_norm_2 );
#   endif
    charModel->setRateMatrix( q );
    StochasticNode< AbstractDiscreteCharacterData > *charactermodel = new StochasticNode< AbstractDiscreteCharacterData >("S", charModel);
    charactermodel->clamp( discrD );
    double lnp = charactermodel->getLnProbability();
    std::cerr << "    lnProb = " << lnp << std::endl;
#   if defined(USE_3_STATES)
#       if defined(USE_RATE_HET)
            const double paupLnL = lnp; // can't check this against paup....
#       else
            const double paupLnL = -813.23060;
#       endif
#   else
#       if defined(USE_RATE_HET)
            const double paupLnL = -900.9122;
#       else
            const double paupLnL = -892.5822;
#       endif
#   endif
    const double tol = 0.01;
    if (fabs(lnp - paupLnL) > tol) {
        std::cerr << "    deviates too much from the likelihood from PAUP* of " << paupLnL << std::endl;
        return false;
    }
    if (lnp >= 0.0) {
        std::cerr << "    lnProb is too high!" << std::endl;
        return false;
    }

    std::cout << "RevBayes LnL:\t\t" << charactermodel->getLnProbability() << std::endl;
    std::cout << "Finished GTR+Gamma model test." << std::endl;
    return true;
}