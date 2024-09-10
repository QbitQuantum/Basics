bool TestBranchHeterogeneousHkyModel::run( void ) {
    
    /* First, we read in the data */
    // the matrix
    std::vector<AbstractCharacterData*> data = NclReader::getInstance().readMatrices(alignmentFilename);
    std::cout << "Read " << data.size() << " matrices." << std::endl;
    std::cout << data[0] << std::endl;
        
    
    /* set up the model graph */
    
    //////////////////////
    // first the priors //
    //////////////////////
    
    // birth-death process priors
    StochasticNode<double> *div = new StochasticNode<double>("diversification", new UniformDistribution(new ConstantNode<double>("div_lower", new double(0.0)), new ConstantNode<double>("div_upper", new double(100.0)) ));
    ConstantNode<double> *turn = new ConstantNode<double>("turnover", new double(0.0));
    ConstantNode<double> *rho = new ConstantNode<double>("rho", new double(1.0));
    
    // hky model priors
    ConstantNode<std::vector<double> > *bfPrior = new ConstantNode<std::vector<double> >( "bfPrior", new std::vector<double>(4,1.0) );
    ConstantNode< double > *tstvPrior = new ConstantNode< double >( "tstvPrior", new double(1.0) );
	
    // root frequencies
    StochasticNode<std::vector<double> > *rf = new StochasticNode<std::vector<double> >( "rf", new DirichletDistribution(bfPrior) );
	
	
	
//    // first the hyper-priors of the clock model
    ConstantNode<double> *a = new ConstantNode<double>("a", new double(0.5) );
    ConstantNode<double> *b = new ConstantNode<double>("b", new double(0.25) );
//	
//    
    // then the parameters
    ContinuousStochasticNode *expectLN = new ContinuousStochasticNode( "UCLN.expectation", new ExponentialDistribution(a) ); // the expectation of the LN dist so mu = log(expectLN) - (sigLN^2)/2
    ContinuousStochasticNode *sigLN = new ContinuousStochasticNode("UCLN.variance", new ExponentialDistribution(b) );	
    DeterministicNode<double> *logExpLN = new DeterministicNode<double>("logUCLN.exp", new LnFunction(expectLN) );
   DeterministicNode<double> *squareSigLN = new DeterministicNode<double>("squareSigLN", new BinaryMultiplication<double, double, double>(sigLN, sigLN) );
   DeterministicNode<double> *divSqSigLN = new DeterministicNode<double>("divSqSigLN", new BinaryDivision<double, double, double>(squareSigLN, new ConstantNode<double>( "2", new double (2.0))) );
   DeterministicNode<double> *muValLN = new DeterministicNode<double>("MuValLN", new BinarySubtraction<double, double, double>(logExpLN, divSqSigLN) );
	
   
    //Declaring a vector of HKY matrices
	size_t numBranches = 2*data[0]->getNumberOfTaxa() - 2;
    std::vector<StochasticNode < std::vector<double> >* > pis;
    std::vector< const TypedDagNode< RateMatrix >* > qs;
	StochasticNode < double >* tstv = new ContinuousStochasticNode("tstv", new ExponentialDistribution( tstvPrior ) );
//
//	
    // declaring a vector of clock rates
	std::vector<const TypedDagNode<double> *> branchRates;
	std::vector< ContinuousStochasticNode *> branchRates_nonConst;
    	
	
	
	
    for (unsigned int i = 0 ; i < numBranches ; i++ ) {
        // construct the per branch rate matrix
        std::ostringstream pi_name;
        pi_name << "pi(" << i << ")";
        pis.push_back(new StochasticNode<std::vector<double> >( pi_name.str(), new DirichletDistribution(bfPrior) ) );
        std::ostringstream q_name;
        q_name << "q(" << i << ")";
        qs.push_back(new DeterministicNode<RateMatrix>( q_name.str(), new HkyRateMatrixFunction( tstv, pis[i]) ));
        std::cout << "Q:\t" << qs[i]->getValue() << std::endl;        
        
       // construct the per branch clock rate
       std::ostringstream br_name;
        br_name << "br(" << i << ")";
		ContinuousStochasticNode* tmp_branch_rate = new ContinuousStochasticNode( br_name.str(), new LognormalDistribution(muValLN, sigLN, new ConstantNode<double>("offset", new double(0.0) )));
		branchRates.push_back( tmp_branch_rate );
		branchRates_nonConst.push_back( tmp_branch_rate );
	}
    // build the vector containing all rates/rate-matrices
    // instead of independent rates/rate-matrices we could have used anything that specifies a distribution on a set of values
    // e.g. a mixture, DPP or an autocorrelated model
    DeterministicNode< std::vector< double > >* br_vector = new DeterministicNode< std::vector< double > >( "br_vector", new VectorFunction< double >( branchRates ) );
    DeterministicNode< RbVector< RateMatrix > >* qs_node = new DeterministicNode< RbVector< RateMatrix > >( "q_vector", new RbVectorFunction<RateMatrix>(qs) );
    
    
    // create the variables for the rate variation across sites
    // we use the standard 4 categorical gamma rate variation
    // though, any other rates could be used too as long as they are normalized
    ConstantNode<double> *alpha_prior = new ConstantNode<double>("alpha_prior", new double(0.5) );
    ContinuousStochasticNode *alpha = new ContinuousStochasticNode("alpha", new ExponentialDistribution(alpha_prior) );
    
    ConstantNode<double> *q1 = new ConstantNode<double>("q1", new double(0.125) );
    DeterministicNode<double> *q1_value = new DeterministicNode<double>("q1_value", new QuantileFunction(q1, new GammaDistribution(alpha, alpha) ) );
    ConstantNode<double> *q2 = new ConstantNode<double>("q2", new double(0.375) );
    DeterministicNode<double> *q2_value = new DeterministicNode<double>("q2_value", new QuantileFunction(q2, new GammaDistribution(alpha, alpha) ) );
    ConstantNode<double> *q3 = new ConstantNode<double>("q3", new double(0.625) );
    DeterministicNode<double> *q3_value = new DeterministicNode<double>("q3_value", new QuantileFunction(q3, new GammaDistribution(alpha, alpha) ) );
    ConstantNode<double> *q4 = new ConstantNode<double>("q4", new double(0.875) );
    DeterministicNode<double> *q4_value = new DeterministicNode<double>("q4_value", new QuantileFunction(q4, new GammaDistribution(alpha, alpha) ) );
    std::vector<const TypedDagNode<double>* > gamma_rates = std::vector<const TypedDagNode<double>* >();
    gamma_rates.push_back(q1_value);
    gamma_rates.push_back(q2_value);
    gamma_rates.push_back(q3_value);
    gamma_rates.push_back(q4_value);
    
    DeterministicNode<std::vector<double> > *site_rates = new DeterministicNode<std::vector<double> >( "site_rates", new VectorFunction<double>(gamma_rates) );
    DeterministicNode<std::vector<double> > *site_rates_norm = new DeterministicNode<std::vector<double> >( "site_rates_norm", new NormalizeVectorFunction(site_rates) );
    // we actually do not use different probabilities per rate (yet!)
   // ConstantNode<std::vector<double> > *site_rate_probs = new ConstantNode<std::vector<double> >( "site_rate_probs", new std::vector<double>(4,1.0/4.0) );
    
    
	
    // create the stochastic node for the tree
    // we use a birth-death process prior and thus a time-tree
    // we could use as well an unrooted tree
    std::vector<std::string> names = data[0]->getTaxonNames();
    ConstantNode<double>* origin = new ConstantNode<double>( "origin", new double( 2.0 ) );
    std::vector<RevBayesCore::Taxon> taxa;
    for (size_t i = 0; i < names.size(); ++i)
    {
        taxa.push_back( Taxon( names[i] ) );
    }
    StochasticNode<TimeTree> *tau = new StochasticNode<TimeTree>( "tau", new ConstantRateBirthDeathProcess(origin, NULL, div, turn, rho, "uniform", "survival", taxa, std::vector<Clade>()) );
    
	
//	//rescale the tree so that its root age is 1
	TimeTree *t = tau->getValue().clone();
	const TopologyNode &root = t->getRoot();
	TreeUtilities::rescaleTree(t, &t->getRoot(), 1.0 / root.getAge());
//	
    tau->setValue( t );
    std::cout << "tau:\t" << tau->getValue() << std::endl;
    
    // and the character model
    //GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree> *charModel = new GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree>(tau, true, data[0]->getNumberOfCharacters() );
    GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree> *charModel = new GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree>(tau, 4, true, data[0]->getNumberOfCharacters() );
    // set the branch heterogeneous substitution matrices
    // if you set instead of a vector a single matrix, then you get a homogeneous model
    charModel->setRateMatrix( qs_node );
    charModel->setRootFrequencies( rf );
    // set the per branch clock rates
    // if you instead specify a single rate, you get a strict clock model
    charModel->setClockRate( br_vector );
    // specify the rate variation across sites
    // if you skip this then you get the model without rate variation across sites.
    charModel->setSiteRates( site_rates_norm );
	
    StochasticNode< AbstractCharacterData > *charactermodel = new StochasticNode< AbstractCharacterData >("S", charModel );
    charactermodel->clamp( data[0] );
    
    
    /* add the moves */
    RbVector<Move> moves;
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(div, 1.0), 2, true ) );
    moves.push_back( new NearestNeighborInterchange( tau, 5.0 ) );
    moves.push_back( new NarrowExchange( tau, 10.0 ) );
    moves.push_back( new FixedNodeheightPruneRegraft( tau, 2.0 ) );
    moves.push_back( new SubtreeScale( tau, 5.0 ) );
//Fixintg the root age at 1:
	//  moves.push_back( new TreeScale( tau, 1.0, true, 2.0 ) );
	//    moves.push_back( new RootTimeSlide( tau, 1.0, true, 2.0 ) );
//test: only 20 instead of 30
    moves.push_back( new NodeTimeSlideUniform( tau, 20.0 ) );
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(tstv, 1.0), 2, true ) );
    moves.push_back( new SimplexSingleElementScale( rf, 10.0, true, 2.0 ) );
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(alpha, 1.0), 2, true ) );
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(expectLN, 1.0), 2, true ) );
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(sigLN, 1.0), 2, true ) );
	std::vector<StochasticNode<double> * > rates;
	for (unsigned int i = 0 ; i < numBranches ; i ++ ) {
		rates.push_back( branchRates_nonConst[i] );
	}
	moves.push_back( new RateAgeBetaShift( tau, rates, 1.0, true, 10.0) );                                                         //!<  constructor

	
	
    for (unsigned int i = 0 ; i < numBranches ; i ++ ) {
        moves.push_back( new SimplexSingleElementScale( pis[i], 10.0, true, 2.0 ) );
        moves.push_back( new MetropolisHastingsMove( new ScaleProposal(branchRates_nonConst[i], 1.0), 1, true ) );
    }
    
    // add some tree stats to monitor
    DeterministicNode<double> *treeHeight = new DeterministicNode<double>("TreeHeight", new TreeHeightStatistic(tau) );
    
    /* add the monitors */
    RbVector<Monitor> monitors;
    std::set<DagNode*> monitoredNodes;
    monitoredNodes.insert( tstv );
    monitoredNodes.insert( treeHeight );
    monitors.push_back( new ScreenMonitor( monitoredNodes, 1, "\t" ) );
    std::set<DagNode*> monitoredNodes2;
    monitoredNodes2.insert( tau );
    monitors.push_back( new FileMonitor( monitoredNodes2, 10, "TestBranchHeterogeneousHkyModel.tree", "\t", false, false, false ) );
    
    /* instantiate the model */
    Model myModel = Model(qs[0]);
	
    monitors.push_back( new ModelMonitor( 10, "TestBranchHeterogeneousHkyModel.log", "\t" ) );
	
    /* instiate and run the MCMC */
    Mcmc myMcmc = Mcmc( myModel, moves, monitors );
//	myMcmc.burnin(1000, 100);
    myMcmc.run(mcmcGenerations);
    
    myMcmc.printOperatorSummary();
    
    /* clean up */
    //    for (size_t i = 0; i < 10; ++i) {
    //        delete x[i];
    //    }
    //    delete [] x;
    delete div;
    //    delete sigma;
    //    delete a;
    //    delete b;
    //    delete c;
    
    std::cout << "Finished GTR model test." << std::endl;
    
    return true;
}