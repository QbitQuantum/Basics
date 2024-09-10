bool TestGtrGammaModel::run( void ) {
    
    /* First, we read in the data */
    // the matrix
    NclReader& reader = NclReader::getInstance();
    std::vector<AbstractCharacterData*> data = reader.readMatrices(alignmentFilename);
    std::cout << "Read " << data.size() << " matrices." << std::endl;
    
    std::vector<TimeTree*> trees = NclReader::getInstance().readTimeTrees( treeFilename );
    std::cout << "Read " << trees.size() << " trees." << std::endl;
    std::cout << trees[0]->getNewickRepresentation() << std::endl;
    
    /* set up the model graph */
    
    //////////////////////
    // first the priors //
    //////////////////////
    
    // birth-death process priors
    StochasticNode<double> *div = new StochasticNode<double>("diversification", new UniformDistribution(new ConstantNode<double>("", new double(0.0)), new ConstantNode<double>("", new double(100.0)) ));
    ConstantNode<double> *turn = new ConstantNode<double>("turnover", new double(0.0));
    ConstantNode<double> *rho = new ConstantNode<double>("rho", new double(1.0));
    // gtr model priors
    ConstantNode<std::vector<double> > *bf = new ConstantNode<std::vector<double> >( "bf", new std::vector<double>(4,1.0) );
    ConstantNode<std::vector<double> > *e = new ConstantNode<std::vector<double> >( "e", new std::vector<double>(6,1.0) );
    
    std::cout << "bf:\t" << bf->getValue() << std::endl;
    std::cout << "e:\t" << e->getValue() << std::endl;
    
    // then the parameters
    StochasticNode<std::vector<double> > *pi = new StochasticNode<std::vector<double> >( "pi", new DirichletDistribution(bf) );
    StochasticNode<std::vector<double> > *er = new StochasticNode<std::vector<double> >( "er", new DirichletDistribution(e) );
    
    //Rate heterogeneity
    ConstantNode<double> *alpha_prior = new ConstantNode<double>("alpha_prior", new double(0.5) );
    ContinuousStochasticNode *alpha = new ContinuousStochasticNode("alpha", new ExponentialDistribution(alpha_prior) );
    
    alpha->setValue( new double(0.5) );
    std::cout << "alpha:\t" << alpha->getValue() << std::endl;
    
    ConstantNode<double> *q1 = new ConstantNode<double>("q1", new double(0.125) );
    DeterministicNode<double> *q1_value = new DeterministicNode<double>("q1_value", new QuantileFunction(q1, new GammaDistribution(alpha, alpha) ) );
//    StochasticNode<double> *q1_value = new StochasticNode<double>("q1_value", new GammaDistribution(alpha, alpha) );
    ConstantNode<double> *q2 = new ConstantNode<double>("q2", new double(0.375) );
    DeterministicNode<double> *q2_value = new DeterministicNode<double>("q2_value", new QuantileFunction(q2, new GammaDistribution(alpha, alpha) ) );
//    StochasticNode<double> *q2_value = new StochasticNode<double>("q2_value", new GammaDistribution(alpha, alpha) );
    ConstantNode<double> *q3 = new ConstantNode<double>("q3", new double(0.625) );
    DeterministicNode<double> *q3_value = new DeterministicNode<double>("q3_value", new QuantileFunction(q3, new GammaDistribution(alpha, alpha) ) );
//    StochasticNode<double> *q3_value = new StochasticNode<double>("q3_value", new GammaDistribution(alpha, alpha) );
    ConstantNode<double> *q4 = new ConstantNode<double>("q4", new double(0.875) );
    DeterministicNode<double> *q4_value = new DeterministicNode<double>("q4_value", new QuantileFunction(q4, new GammaDistribution(alpha, alpha) ) );
//    StochasticNode<double> *q4_value = new StochasticNode<double>("q4_value", new GammaDistribution(alpha, alpha) );
    std::vector<const TypedDagNode<double>* > gamma_rates = std::vector<const TypedDagNode<double>* >();
    gamma_rates.push_back(q1_value);
    gamma_rates.push_back(q2_value);
    gamma_rates.push_back(q3_value);
    gamma_rates.push_back(q4_value);
    
    DeterministicNode<std::vector<double> > *site_rates = new DeterministicNode<std::vector<double> >( "site_rates", new VectorFunction<double>(gamma_rates) );
    // currently unused
    // ConstantNode<std::vector<double> > *site_rate_probs = new ConstantNode<std::vector<double> >( "site_rate_probs", new std::vector<double>(4,1.0/4.0) );

    DeterministicNode<std::vector<double> > *site_rates_norm = new DeterministicNode<std::vector<double> >( "site_rates_norm", new NormalizeVectorFunction(site_rates) );
    
    pi->setValue( new std::vector<double>(4,1.0/4.0) );
    er->setValue( new std::vector<double>(6,1.0/6.0) );
    
    std::cout << "pi:\t" << pi->getValue() << std::endl;
    std::cout << "er:\t" << er->getValue() << std::endl;
    std::cout << "rates:\t" << site_rates->getValue() << std::endl;
    std::cout << "rates:\t" << site_rates_norm->getValue() << std::endl;

    DeterministicNode<RateMatrix> *q = new DeterministicNode<RateMatrix>( "Q", new GtrRateMatrixFunction(er, pi) );
    
    std::cout << "Q:\t" << q->getValue() << std::endl;
    
    std::vector<std::string> names = data[0]->getTaxonNames();
    ConstantNode<double>* origin = new ConstantNode<double>( "origin", new double( trees[0]->getRoot().getAge()*2.0 ) );
    std::vector<RevBayesCore::Taxon> taxa;
    for (size_t i = 0; i < names.size(); ++i)
    {
        taxa.push_back( Taxon( names[i] ) );
    }
    StochasticNode<TimeTree> *tau = new StochasticNode<TimeTree>( "tau", new ConstantRateBirthDeathProcess(origin, NULL, div, turn, rho, "uniform", "survival", taxa, std::vector<Clade>()) );
    
    tau->setValue( trees[0] );
    std::cout << "tau:\t" << tau->getValue() << std::endl;
    
    // and the character model
// (unused)    size_t numChar = data[0]->getNumberOfCharacters();
    GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree> *phyloCTMC = new GeneralBranchHeterogeneousCharEvoModel<DnaState, TimeTree>(tau, 4, true, data[0]->getNumberOfCharacters());
    phyloCTMC->setSiteRates( site_rates_norm );
    phyloCTMC->setRateMatrix( q );
    StochasticNode< AbstractCharacterData > *charactermodel = new StochasticNode< AbstractCharacterData >("S", phyloCTMC );
    charactermodel->clamp( static_cast<DiscreteCharacterData<DnaState> *>( data[0] ) );
    
    std::cout << "LnL:\t\t" << charactermodel->getLnProbability() << std::endl;
    
    /* add the moves */
    RbVector<Move> moves;
//    moves.push_back( new ScaleMove(div, 1.0, true, 2.0) );
//    moves.push_back( new NearestNeighborInterchange( tau, 5.0 ) );
//    moves.push_back( new NarrowExchange( tau, 10.0 ) );
//    moves.push_back( new FixedNodeheightPruneRegraft( tau, 2.0 ) );
//    moves.push_back( new SubtreeScale( tau, 5.0 ) );
//    moves.push_back( new TreeScale( tau, 1.0, true, 2.0 ) );
//    moves.push_back( new NodeTimeSlideUniform( tau, 30.0 ) );
//    moves.push_back( new RootTimeSlide( tau, 1.0, true, 2.0 ) );
//    moves.push_back( new SimplexMove( er, 10.0, 1, 0, true, 2.0 ) );
//    moves.push_back( new SimplexMove( pi, 10.0, 1, 0, true, 2.0 ) );
//    moves.push_back( new SimplexMove( er, 100.0, 6, 0, true, 2.0 ) );
//    moves.push_back( new SimplexMove( pi, 100.0, 4, 0, true, 2.0 ) );
    
    moves.push_back( new MetropolisHastingsMove( new ScaleProposal(alpha, 1.0), 1, true) );
//    moves.push_back( new ScaleMove(q1_value, 1.0, true, 2.0) );
//    moves.push_back( new ScaleMove(q2_value, 1.0, true, 2.0) );
//    moves.push_back( new ScaleMove(q3_value, 1.0, true, 2.0) );
//    moves.push_back( new ScaleMove(q4_value, 1.0, true, 2.0) );
    
    // add some tree stats to monitor
    DeterministicNode<double> *treeHeight = new DeterministicNode<double>("TreeHeight", new TreeHeightStatistic(tau) );
    
    /* add the monitors */
    RbVector<Monitor> monitors;
    std::set<DagNode*> monitoredNodes;
//    monitoredNodes.insert( er );
//    monitoredNodes.insert( pi );
//    monitoredNodes.insert( q );
//    monitoredNodes.insert( q1_value );
//    monitoredNodes.insert( q2_value );
//    monitoredNodes.insert( q3_value );
//    monitoredNodes.insert( q4_value );
    monitoredNodes.insert( site_rates_norm );
    monitoredNodes.insert( alpha );
    monitoredNodes.insert( treeHeight );
    monitors.push_back( new FileMonitor( monitoredNodes, 1000, "TestGtrGammaModelSubstRates.log", "\t" ) );
    monitors.push_back( new ScreenMonitor( monitoredNodes, 1000, "\t" ) );
    std::set<DagNode*> monitoredNodes2;
    monitoredNodes2.insert( tau );
    monitors.push_back( new FileMonitor( monitoredNodes2, 1000, "TestGtrGammaModel.tree", "\t", false, false, false ) );
    
    /* instantiate the model */
    Model myModel = Model(q);
    
    /* instiate and run the MCMC */
    Mcmc myMcmc = Mcmc( myModel, moves, monitors );
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
    
    std::cout << "Finished GTR+Gamma model test." << std::endl;
    
    return true;
}