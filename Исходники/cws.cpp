int main()
{
	try {
		g_conf.readFile(CONFIG_FILE);
	} catch (const FileIOException &e) {
		cerr << "I/O error while reading " << CONFIG_FILE << endl;
		exit(EXIT_FAILURE);
	} catch(const ParseException &pex) {
		cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
		     << " - " << pex.getError() << std::endl;
		exit(EXIT_FAILURE);
	}

	try {
		initialize_simulator();
		create_job_tracker();
		create_pools();
	} catch (const SettingNotFoundException &e) {
		cerr << "Missing a setting in configuration file" << endl;
		exit(EXIT_FAILURE);
	}

	if (import_workload1(g_input.c_str(), &g_job_tracker->getpools())) {
		cerr << "Unable to load workload" << endl;
		exit(EXIT_FAILURE);
	}

	cerr << "Processing workload ..." << endl;
	g_job_tracker->process();

	cerr << "Calculating utilizations ..." << endl;
	calc_utils();

	export_schedule(g_output.c_str(), g_job_tracker->getpools());
	cerr << "Saved schedule to output " << g_output << endl;

	delete g_job_tracker;

	return 0;
}