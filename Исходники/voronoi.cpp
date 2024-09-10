int main( int argc, char *argv[] ) {
	using std::auto_ptr;
	using std::exception;
	using std::ofstream;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::setprecision;
	using std::setiosflags;
	using std::ios;
	using std::min;
	using boost::timer;

	auto_ptr<Voronoi::StipplingParameters> parameters;
	
	try {
		parameters = parseArguments( argc, argv );
		if (parameters.get() == NULL) {
			return 0;
		}
	} catch ( exception e ) {
		return -1;
	}

	STIPPLER_HANDLE stippler;

	ofstream log;
	if ( parameters->createLogs ) {
		log.open( "log.txt" );
	}

	try {
		stippler = create_stippler( parameters.get() );
	} catch ( exception e ) {
		delete[] parameters.get()->inputFile;
		cerr << e.what() << endl;

		return -1;
	}

	write_configuration( cout, *(parameters.get()) );
	if ( parameters->createLogs ) {
		write_configuration( log, *(parameters.get()) );
	}

	int iteration = 0;
	float t = parameters->threshold + 1.0f;
	do {
		timer profiler;

		stippler_distribute(stippler);

		if ( parameters->createLogs ) {
			log << "Iteration " << (++iteration) << " completed in " << profiler.elapsed() << " seconds." << endl;
			cout << "Iteration " << iteration << " completed in " << profiler.elapsed() << " seconds." << endl;
		}

		t = stippler_getAverageDisplacement( stippler );

		if ( parameters->createLogs ) {
			log << "Current Displacement: " << t << endl;
			cout << "Current Displacement: " << t << endl;
		}

		cout << setiosflags(ios::fixed) << setprecision(2) << min((parameters->threshold / t * 100), 100.0f) << "% Complete" << endl; 
	} while ( t > parameters->threshold );

	// render final result to SVG
	try {
		render( stippler, *(parameters.get()) );
	} catch (exception e) {
		cerr << e.what();
	}

	delete[] parameters.get()->inputFile;

	if ( parameters->createLogs ) {
		log.close();
	}

	destroy_stippler( stippler );

	return 0;
}