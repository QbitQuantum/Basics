int	main( int argc, char* argv[] )
{
	ParseCommandLine(argc, argv);

	ifstream	file(geometry_filepath.c_str(), ios::in);

	if (!file.is_open())
	{
		throw "Couldn't open geometry file!";
	}

	Geometry	geom(file);
	TFile		input_file(input_filepath.c_str());

	TTree	*info = (TTree*)input_file.FindObjectAny("info");
	TTree	*events = (TTree*)input_file.FindObjectAny("events");
	TTree	*cycle_efficiency = (TTree*)input_file.FindObjectAny("cycle_efficiency");

	// Now check that all branches in all tress have the same count of entries
	Long_t prev_entries;
	bool first = true;
	bool result = true;
	result &= is_same_size_tree(events, &prev_entries, &first);
	result &= is_same_size_tree(cycle_efficiency, &prev_entries, &first);
	if (!result)
	{
		throw "Unbalanced input tree";
	}

	if (!info)
	{
		throw "Missing info tree!";
	}

	info->Scan("key:value", "", "colsize=30");

	map<string, string>	info_hash = get_info_hash(info);
	string file_commit_id = info_hash["GIT_COMMIT_ID"];
	if (file_commit_id != GIT_COMMIT_ID)
	{
		cerr << endl
		     << "Warning: Commit id mismatch"
		     << endl
		     << "File created by: "
		     << file_commit_id
		     << endl
		     << "Current software is: "
		     << GIT_COMMIT_ID
		     << endl;
	}
	string original_filename =
	    gSystem->BaseName(info_hash["INPUT_FILE"].c_str());
	cerr << "original_filename\t" << original_filename << endl;

	try
	{
		TFile	output_file(output_filepath.c_str(), "RECREATE");
		TTree	*events_new;
		TTree	*efficiency_tree;
		TTree	*info_new = info->CloneTree();
		add_info_value(info_new, "PROCESS_GIT_COMMIT_ID", GIT_COMMIT_ID);
		intersection_set_t	s;

		events_new = Process(events, cycle_efficiency, geom, central_momentum, &s);

		efficiency_tree = Process2ndPass(events_new);

		// Now check that all branches in all tress have the same count of entries
		Long_t prev_entries;
		bool first = true;
		bool result = true;
		result &= is_same_size_tree(events_new, &prev_entries, &first);
		result &= is_same_size_tree(efficiency_tree, &prev_entries, &first);
		if (!result)
		{
			throw "Unbalanced output tree";
		}

		output_file.Write();
	}
	catch(const char *e)
	{
		cerr << "Exception: " << e << endl;
		cerr << "Removing output file \"" << output_filepath << "\"." << endl;
		gSystem->Unlink(output_filepath.c_str());
		return EXIT_FAILURE;
	}

	return 0;
}