void TestHSMM::test_marginal_cut(const char* filename, size_t ID){

	HSMMparam param(filename);

	FactorGraph *graph;
	JTree *jt;

	// Set some constants
	size_t maxiter = 10000;
	Real   tol = 1e-9;
	size_t verb = 0;

	//window size
    size_t W = 20;
    size_t start = 0;

	// Store the constants in a PropertySet object
	PropertySet opts;
	opts.set("maxiter",maxiter);  // Maximum number of iterations
	opts.set("tol",tol);          // Tolerance for convergence
	opts.set("verbose",verb);     // Verbosity (amount of output generated)

	Factor O_last;
	vector< vector<Real> > all_marginal;
	vector<Real> sequence_marginal;
	all_marginal.reserve(test_data.size());


	cout << "Now we do testing...\n";

	for(size_t i=0; i<test_data.size(); i++) {

		//allocate memory
		sequence_marginal.reserve(test_data[i].size());

		//initialize HSMM of ever increasing size up to test_data[i].size()
		graph = new FactorGraph();
		graph->createHSMMFactorGraph(param.init, param.dist, test_data[i].size());

		jt = new JTree(*graph, opts("updates",string("HUGIN"))("heuristic",string("MINWEIGHT")) );

		jt->init();
		jt->run();

		O_last = jt->calcMarginal(graph->var(4));
		sequence_marginal.push_back( log(O_last.p().get(test_data[i][0].second)) );

		delete jt;

		for(size_t k=1; k < test_data[i].size(); k++){

			jt = new JTree(*graph, opts("updates",string("HUGIN"))("heuristic",string("MINWEIGHT")) );

			//clamp a window of observable variables to their values, except last variable which is not clamped
			start = k-W;
			if(start < 0) start = 0;

			for(size_t j = start; j <= k-1; j++){
				jt->clamp(test_data[i][j].first, test_data[i][j].second);
			}

			jt->init();
			jt->run();

			//compute p(o_last=c | o_1...o_{last-1})
			//this will give us a distribution: {o_last=1, o_last=2, ... o_last=M}
			O_last = jt->calcMarginal(graph->var(3*k+4));

			//since we have a specific observation at last time step: o_last=c, get its probability:
			sequence_marginal.push_back( log(O_last.p().get(test_data[i][k].second)) );

			delete jt;
		}

		cout << "Tested point " << i << " out of " << test_data.size() <<"\n";

		all_marginal.push_back(sequence_marginal);
		sequence_marginal.clear();

		delete graph;
	}

	cout << "Testing done.\n";

	ofstream os;
	stringstream result;
	result << string("data/HSMMmarginal_test_") << ID << string(".txt");
	os.open(result.str().c_str(), ios::trunc);

	for(size_t i=0; i<all_marginal.size(); i++){
		for(size_t j=0; j<all_marginal[i].size(); j++){
			os << all_marginal[i][j]<<" ";
		}
		os << "\n";
	}
}