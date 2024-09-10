int main(int argc, char *argv[]) {
	set_new_handler(alloc_error);

	if(argc < 6) {
		print_usage(cout);
		exit(0);
	}
	
	string seqfile;                       // file with sequences
	string exprfile;                      // file with expression data
	string subsetfile;                    // file with subset of sequence names to search
	string scorefile;                     // file with scores

	if(! GetArg2(argc, argv, "-s", seqfile)) {
		cerr << "Please specify sequence file\n\n";
		print_usage(cout);
		exit(0);
	}
	if(! GetArg2(argc, argv, "-o", outfile)) {
		cerr << "Please specify output file\n\n";
		print_usage(cout);
		exit(0);
	}
	
	int search_type = UNDEFINED;
	if(GetArg2(argc, argv, "-ex", exprfile)) {
		search_type = EXPRESSION;
	}
	if(GetArg2(argc, argv, "-su", subsetfile)) {
		search_type = SUBSET;
	}
	if(GetArg2(argc, argv, "-sc", scorefile)) {
		search_type = SCORE;
	}
	if(search_type == UNDEFINED) {
		cerr << "Please specify either an expression data file, a file with a subset of sequence names, or a file with sequence scores.\n\n";
		print_usage(cout);
		exit(0);
	}

	// Decide mode of running
	archive = false;
	if(! GetArg2(argc, argv, "-worker", worker)) {
		worker = -1;
		archive = true;
	}
	
	// Read parameters
	vector<string> seqs;
	cerr << "Reading sequence data from '" << seqfile << "'... ";
	get_fasta_fast(seqfile.c_str(), seqs, seq_nameset);
	cerr << "done.\n";
	ngenes = seq_nameset.size();
	
	npoints = 0;
	if(search_type == EXPRESSION) {
		cerr << "Reading expression data from '" << exprfile << "'... ";
		get_expr(exprfile.c_str(), expr, data_nameset);
		cerr << "done.\n";
		npoints = expr[0].size();
		nsubset = 0;
	} else if(search_type == SUBSET) {
		cerr << "Reading subset of sequences to search from '" << subsetfile << "'... ";
		get_list(subsetfile.c_str(), subset);
		cerr << "done.\n";
		npoints = 0;
		for(int i = 0; i < ngenes; i++) {
			vector<float> row(0);
			expr.push_back(row);
		}
		nsubset = subset.size();
		sort(subset.begin(), subset.end());
	} else if(search_type == SCORE) {
		cerr << "Reading sequence scores from '" << scorefile << "'... ";
		get_scores(scorefile.c_str(), scores, data_nameset);
		cerr << "done.\n";
		npoints = 1;
		nsubset = 0;
	}

	vector<vector <float> > newexpr;
	vector<float> newscores;
	if(search_type == EXPRESSION) {
		order_data_expr(newexpr);
	}
	if(search_type == SCORE) {
		order_data_scores(newscores);
	}

	if(search_type == EXPRESSION) {
		cerr << "Successfully read input files -- dataset size is " << ngenes << " sequences X " << npoints << " timepoints\n";
	} else if(search_type == SUBSET) {
		cerr << "Successfully read input files -- dataset size is " << ngenes << " sequences, with " << nsubset << " to be searched\n";
	} else if(search_type == SCORE) {
		cerr << "Successfully read input files -- dataset size is " << ngenes << " scored sequences\n";
	}

	cerr << "Setting up MotifSearch... ";
	if(! GetArg2(argc, argv, "-numcols", ncol)) ncol = 10;
	if(! GetArg2(argc, argv, "-order", order)) order = 0;
	if(! GetArg2(argc, argv, "-simcut", simcut)) simcut = 0.8;
	if(! GetArg2(argc, argv, "-maxm", maxm)) maxm = 20;
	MotifSearch* ms;
	if(search_type == EXPRESSION) {
		ms = new MotifSearchExpr(seq_nameset, seqs, ncol, order, simcut, maxm, newexpr, npoints);
	} else if(search_type == SCORE) {
		ms = new MotifSearchScore(seq_nameset, seqs, ncol, order, simcut, maxm, newscores);
	} else {
		ms = new MotifSearchSubset(seq_nameset, seqs, ncol, order, simcut, maxm, subset);
	}
	ms->modify_params(argc, argv);
	ms->set_final_params();
	ms->ace_initialize();
	cerr << "done.\n";
	cerr << "Random seed: " << ms->get_params().seed << '\n';

	if(archive) {
		cerr << "Running in archive mode...\n";
		string archinstr(outfile);
		archinstr.append(".ms");
		ifstream archin(archinstr.c_str());
		if(archin) {
			cerr << "Refreshing from existing archive file " << archinstr << "... ";
			ms->get_archive().read(archin);
			cerr << "done.\n";
		}
		while(true) {
			int found = read_motifs(ms);
			if(found > 0) output(ms);
			if(found < 50) sleep(10);
		}
	} else {
		cerr << "Running as worker " << worker << "...\n";
		int nruns = ms->positions_in_search_space()/(ms->get_params().expect * ncol);
		nruns *= ms->get_params().oversample;
		nruns /= ms->get_params().undersample;
		cerr << "Restarts planned: " << nruns << '\n';
		string archinstr(outfile);
		archinstr.append(".ms");
		string lockstr(outfile);
		lockstr.append(".lock");
		for(int j = 1; j <= nruns; j++) {
			if(j == 1 || j % 50 == 0 || search_type == SUBSET) {
				struct flock fl;
				int fd;
				fl.l_type   = F_RDLCK;
				fl.l_whence = SEEK_SET;
				fl.l_start  = 0;
				fl.l_len    = 0;
				fl.l_pid    = getpid();
				fd = open(lockstr.c_str(), O_RDONLY);
				if(fd == -1) {
					if(errno != ENOENT)
						cerr << "\t\tUnable to read lock file, error was " << strerror(errno) << "\n";
				} else {
					while(fcntl(fd, F_SETLK, &fl) == -1) {
						cerr << "\t\tWaiting for lock release on archive file... \n";
						sleep(10);
					}
					ifstream archin(archinstr.c_str());
					if(archin) {
						cerr << "\t\tRefreshing archive from " << archinstr << "...";
						ms->get_archive().clear();
						ms->get_archive().read(archin);
						archin.close();
						cerr << "done.\n";
					}
					fl.l_type = F_UNLCK;
					fcntl(fd, F_SETLK, &fl);
					close(fd);
					cerr << "\t\tArchive now has " << ms->get_archive().nmots() << " motifs\n";
				}
			}
			cerr << "\t\tSearch restart #" << j << "/" << nruns << "\n";
			ms->search_for_motif(worker, j, outfile);
		}
	}
	delete ms;
	return 0;
}