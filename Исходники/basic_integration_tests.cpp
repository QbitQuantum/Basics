/** Run GNGAlgorithm on a cube (3-dimensional) with given parameters
 * @returns pair<double, double> : nodes, mean_error
 */
pair<double, double> test_convergence(GNGConfiguration * cnf = 0,
		int num_database = 1000, int ms_loop = 5000, string save_filename = "",
		double* extra_examples = 0, int extra_samples_size = 0,
		string load_filename = "") {
	GNGConfiguration config = GNGConfiguration::getDefaultConfiguration();
	config.uniformgrid_optimization = true;

	if (cnf)
		config = *cnf;
	config.datasetType = GNGConfiguration::DatasetSeq;

	GNGServer * s;

	if (load_filename != "") {
		cerr << "Loading everything from file!\n";
		s = new GNGServer(load_filename);
	} else {
		s = GNGServer::constructTestServer(config);
	}

	cerr << s->getGraph().reportPool() << endl;

	s->run();

	cerr << "Allocating " << (config.dim) * num_database << endl << flush;
	double * vect = new double[(config.dim) * num_database];
	for (int i = 0; i < num_database; ++i) {
		for (int j = 0; j <= config.dim; ++j)
			if (j == 0)
				vect[j + (i) * (config.dim)] = 0.0;
			else if (j < config.dim)
				vect[j + (i) * (config.dim)] = __double_rnd(0, 1);
	}

	cerr << "Allocated examples\n";

	if (extra_examples) {
		cerr << "Adding extra examples\n";
		s->insertExamples(extra_examples, 0, 0,
				extra_samples_size / (config.dim), config.dim);
	}

	cerr << "Adding main examples\n";
	s->insertExamples(vect, 0, 0, num_database, config.dim);

	cerr << "Dimensionality of example is " << s->getDatabase().getDataDim()
			<< endl;

	for (int i = 0; i < 10; ++i) {
		cerr << "Exemplary sample (testing memory correctness):\n";
		int ex = s->getDatabase().drawExample();
		write_array(s->getDatabase().getPosition(ex),
				s->getDatabase().getPosition(ex) + (config.dim + 1));
	}



	cerr << "testNewInterface::Collecting results\n";

	int iteration = 0;

	while (true) {
		++iteration;

		gmum::sleep(sleep_ms);
		if (iteration >= ms_loop / sleep_ms)
			break;
	}

	s->terminate();

	gmum::sleep(sleep_ms);

	pair<double, double> t = pair<double, double>(
			s->getGraph().get_number_nodes(), s->getMeanError());
	if (save_filename != "") {
		cerr << "GNGNumericTest::Saving to GraphML\n";
		writeToGraphML(s->getGraph(), save_filename);
	}

	delete s;
	return t;
}