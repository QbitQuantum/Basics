int
main(int argc, const char **argv) {

  try {

    bool VERBOSE = false;
    double sig_cutoff = 0.05;

    /****************** COMMAND LINE OPTIONS ********************/
    OptionParser opt_parse(strip_path(argv[0]), "computes DMRs based on "
        "HMRs and probability of differences at "
        "individual CpGs",
        "<methdiffs_1_gt_2> <hmr_1> <hmr_2> "
        "<dmr_1_lt_2> <dmr_2_lt_1>");
    opt_parse.add_opt("cutoff", 'c', "Significance cutoff (default: 0.05)",
        false, sig_cutoff);
    opt_parse.add_opt("verbose", 'v', "print more run info", false, VERBOSE);
    vector<string> leftover_args;
    opt_parse.parse(argc, argv, leftover_args);
    if (argc == 1 || opt_parse.help_requested()) {
      cerr << opt_parse.help_message() << endl
      << opt_parse.about_message() << endl;
      return EXIT_SUCCESS;
    }
    if (opt_parse.about_requested()) {
      cerr << opt_parse.about_message() << endl;
      return EXIT_SUCCESS;
    }
    if (opt_parse.option_missing()) {
      cerr << opt_parse.option_missing_message() << endl;
      return EXIT_SUCCESS;
    }
    if (leftover_args.size() != 5) {
      cerr << opt_parse.help_message() << endl;
      return EXIT_SUCCESS;
    }
    const string diffs_file = leftover_args[0];
    const string hmr1_file = leftover_args[1];
    const string hmr2_file = leftover_args[2];
    const string outfile_a = leftover_args[3];
    const string outfile_b = leftover_args[4];
    /****************** END COMMAND LINE OPTIONS *****************/

    if (VERBOSE)
      cerr << "[LOADING HMRS] " << hmr1_file << endl;

    vector<GenomicRegion> regions_a;
    ReadBEDFile(hmr1_file, regions_a);
    assert(check_sorted(regions_a));
    if (!check_sorted(regions_a))
      throw SMITHLABException("regions not sorted in file: " + hmr1_file);
    if (!check_no_overlap(regions_a))
      throw SMITHLABException("regions overlap in file: " + hmr1_file);

    if (VERBOSE)
      cerr << "[LOADING HMRS] " << hmr2_file << endl;

    vector<GenomicRegion> regions_b;
    ReadBEDFile(hmr2_file, regions_b);
    assert(check_sorted(regions_b));
    if (!check_sorted(regions_b))
      throw SMITHLABException("regions not sorted in file: " + hmr2_file);
    if (!check_no_overlap(regions_b))
      throw SMITHLABException("regions overlap in file: " + hmr2_file);

    if (VERBOSE)
      cerr << "[COMPUTING SYMMETRIC DIFFERENCE]" << endl;


    size_t max_end = 0;
    for (size_t i = 0; i < regions_a.size(); ++i)
      max_end = max(max_end, regions_a[i].get_end());
    for (size_t i = 0; i < regions_b.size(); ++i)
      max_end = max(max_end, regions_b[i].get_end());

    vector<GenomicRegion> a_cmpl, b_cmpl;
    complement_regions(max_end, regions_a, a_cmpl);
    complement_regions(max_end, regions_b, b_cmpl);

    vector<GenomicRegion> dmrs_a, dmrs_b;
    genomic_region_intersection_by_base(regions_a, b_cmpl, dmrs_a);
    genomic_region_intersection_by_base(regions_b, a_cmpl, dmrs_b);

    // separate the regions by chrom and by desert
    if (VERBOSE)
      cerr << "[READING CPG METH DIFFS]" << endl;
    vector<GenomicRegion> cpgs;
	read_diffs_file(diffs_file, cpgs, VERBOSE);
    if (!check_sorted(cpgs))
      throw SMITHLABException("CpGs not sorted in: " + diffs_file);
    if (VERBOSE)
      cerr << "[TOTAL CPGS]: " << cpgs.size() << endl;

    vector<pair<size_t, size_t> > sep_sites;
    separate_sites(dmrs_a, cpgs, sep_sites);

    for (size_t i = 0; i < dmrs_a.size(); ++i) {
      size_t total_cpgs = 0, total_sig = 0;
      get_cpg_stats(true, sig_cutoff,
      cpgs, sep_sites[i].first, sep_sites[i].second,
      total_cpgs, total_sig);
      dmrs_a[i].set_name(dmrs_a[i].get_name() + ":" + toa(total_cpgs));
      dmrs_a[i].set_score(total_sig);
    }

    sep_sites.clear();
    separate_sites(dmrs_b, cpgs, sep_sites);

    for (size_t i = 0; i < dmrs_b.size(); ++i) {
      size_t total_cpgs = 0, total_sig = 0;
      get_cpg_stats(false, sig_cutoff,
        cpgs, sep_sites[i].first, sep_sites[i].second,
        total_cpgs, total_sig);
      dmrs_b[i].set_name(dmrs_b[i].get_name() + ":" + toa(total_cpgs));
      dmrs_b[i].set_score(total_sig);
    }

    std::ofstream out_a(outfile_a.c_str());
    copy(dmrs_a.begin(), dmrs_a.end(),
    std::ostream_iterator<GenomicRegion>(out_a, "\n"));

    std::ofstream out_b(outfile_b.c_str());
    copy(dmrs_b.begin(), dmrs_b.end(),
    std::ostream_iterator<GenomicRegion>(out_b, "\n"));

    if (VERBOSE)
      cerr << "[OUTPUT FORMAT] COL4=NAME:N_COVERED_CPGS COL5=N_SIG_CPGS" << endl;
  }
  catch (const SMITHLABException &e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }
  catch (std::bad_alloc &ba) {
    cerr << "ERROR: could not allocate memory" << endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}