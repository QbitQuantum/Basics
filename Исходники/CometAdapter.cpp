  void createParamFile_(ostream& os)
  {
    os << "# comet_version " << getStringOption_("comet_version") << "\n";               //required as first line in the param file
    os << "# Comet MS/MS search engine parameters file.\n";
    os << "# Everything following the '#' symbol is treated as a comment.\n";
    os << "database_name = " << getStringOption_("database") << "\n";
    os << "decoy_search = " << 0 << "\n"; // 0=no (default), 1=concatenated search, 2=separate search
    os << "num_threads = " << getIntOption_("threads") << "\n";  // 0=poll CPU to set num threads; else specify num threads directly (max 64)

    // masses
    map<String,int> precursor_error_units;
    precursor_error_units["amu"] = 0;
    precursor_error_units["mmu"] = 1;
    precursor_error_units["ppm"] = 2;

    map<string,int> isotope_error;
    isotope_error["off"] = 0;
    isotope_error["-1/0/1/2/3"] = 1;
    isotope_error["-8/-4/0/4/8"] = 2;

    os << "peptide_mass_tolerance = " << getDoubleOption_("precursor_mass_tolerance") << "\n";
    os << "peptide_mass_units = " << precursor_error_units[getStringOption_("precursor_error_units")] << "\n";                  // 0=amu, 1=mmu, 2=ppm
    os << "mass_type_parent = " << 1 << "\n";                    // 0=average masses, 1=monoisotopic masses
    os << "mass_type_fragment = " << 1 << "\n";                  // 0=average masses, 1=monoisotopic masses
    os << "precursor_tolerance_type = " << 0 << "\n";            // 0=MH+ (default), 1=precursor m/z; only valid for amu/mmu tolerances
    os << "isotope_error = " << isotope_error[getStringOption_("isotope_error")] << "\n";                      // 0=off, 1=on -1/0/1/2/3 (standard C13 error), 2= -8/-4/0/4/8 (for +4/+8 labeling)

    // search enzyme

    String enzyme_name = getStringOption_("enzyme");
    String enzyme_number = String(ProteaseDB::getInstance()->getEnzyme(enzyme_name)->getCometID());

    map<string,int> num_enzyme_termini;
    num_enzyme_termini["semi"] = 1;
    num_enzyme_termini["fully"] = 2;
    num_enzyme_termini["C-term unspecific"] = 8;
    num_enzyme_termini["N-term unspecific"] = 9;

    os << "search_enzyme_number = " << enzyme_number << "\n";                // choose from list at end of this params file
    os << "num_enzyme_termini = " << num_enzyme_termini[getStringOption_("num_enzyme_termini")] << "\n";                  // 1 (semi-digested), 2 (fully digested, default), 8 C-term unspecific , 9 N-term unspecific
    os << "allowed_missed_cleavage = " << getIntOption_("allowed_missed_cleavages") << "\n";             // maximum value is 5; for enzyme search

    // Up to 9 variable modifications are supported
    // format:  <mass> <residues> <0=variable/else binary> <max_mods_per_peptide> <term_distance> <n/c-term> <required>
    //     e.g. 79.966331 STY 0 3 -1 0 0
    vector<String> variable_modifications_names = getStringList_("variable_modifications");
    vector<ResidueModification> variable_modifications = getModifications_(variable_modifications_names);
    if (variable_modifications.size() > 9)
    {
      throw OpenMS::Exception::IllegalArgument(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, "Error: Comet only supports 9 variable modifications. " + String(variable_modifications.size()) + " provided.");
    }

    int max_variable_mods_in_peptide = getIntOption_("max_variable_mods_in_peptide");
    Size var_mod_index = 0;

    // write out user specified modifications
    for (; var_mod_index < variable_modifications.size(); ++var_mod_index)
    {
      const ResidueModification mod = variable_modifications[var_mod_index];
      double mass = mod.getDiffMonoMass();
      String residues = mod.getOrigin();
      //TODO support binary groups, e.g. for SILAC
      int binary_group = 0;
      //TODO support mod-specific limit (default for now is the overall max per peptide)
      int max_current_mod_per_peptide = max_variable_mods_in_peptide;
      //TODO support term-distances?
      int term_distance = -1;
      int nc_term = 0;

      //TODO support agglomeration of Modifications to same AA. Watch out for nc_term value then.
      if (mod.getTermSpecificity() == ResidueModification::C_TERM)
      {
        residues = "c";
        term_distance = 0;
        // Since users need to specify mods that apply to multiple residues/terms separately
        // 3 and -1 should be equal for now.
        nc_term = 3;
      }
      else if (mod.getTermSpecificity() == ResidueModification::N_TERM)
      {
        residues = "n";
        term_distance = 0;
        // Since users need to specify mods that apply to multiple residues/terms separately
        // 2 and -1 should be equal for now.
        nc_term = 2;
      }
      else if (mod.getTermSpecificity() == ResidueModification::PROTEIN_N_TERM) // not yet available
      {
        term_distance = 0;
        nc_term = 0;
      }
      else if (mod.getTermSpecificity() == ResidueModification::PROTEIN_C_TERM) // not yet available
      {
        term_distance = 0;
        nc_term = 1;
      }

      //TODO support required variable mods
      bool required = false;

      os << "variable_mod0" << var_mod_index+1 << " = " << mass << " " << residues << " " << binary_group << " " << max_current_mod_per_peptide << " " << term_distance << " " << nc_term << " " << required << "\n";
    }

    // fill remaining modification slots (if any) in Comet with "no modification"
    for (; var_mod_index < 9; ++var_mod_index)
    {
      os << "variable_mod0" << var_mod_index+1 << " = " << "0.0 X 0 3 -1 0 0" << "\n";
    }

    os << "max_variable_mods_in_peptide = " << getIntOption_("max_variable_mods_in_peptide") << "\n";
    os << "require_variable_mod = " << (int) (getStringOption_("require_variable_mod") == "true") << "\n";

    // fragment ion defaults
    // ion trap ms/ms:  1.0005 tolerance, 0.4 offset (mono masses), theoretical_fragment_ions = 1
    // high res ms/ms:    0.02 tolerance, 0.0 offset (mono masses), theoretical_fragment_ions = 0

    String instrument = getStringOption_("instrument");
    double bin_tol = getDoubleOption_("fragment_bin_tolerance");
    double bin_offset = getDoubleOption_("fragment_bin_offset");
    if (instrument == "low_res" && (bin_tol < 0.9 || bin_offset <= 0.2))
    {
      LOG_WARN << "Fragment bin size or tolerance is quite low for low res instruments." << "\n";
    }
    else if (instrument == "high_res" && (bin_tol > 0.2 || bin_offset > 0.1))
    {
      LOG_WARN << "Fragment bin size or tolerance is quite high for high res instruments." << "\n";
    };

    os << "fragment_bin_tol = " << bin_tol << "\n";               // binning to use on fragment ions
    os << "fragment_bin_offset = " << bin_offset  << "\n";              // offset position to start the binning (0.0 to 1.0)
    os << "theoretical_fragment_ions = " << (int)(instrument == "low_res") << "\n";           // 0=use flanking bin, 1=use M bin only
    os << "use_A_ions = " << (int)(getStringOption_("use_A_ions")=="true") << "\n";
    os << "use_B_ions = " << (int)(getStringOption_("use_B_ions")=="true") << "\n";
    os << "use_C_ions = " << (int)(getStringOption_("use_C_ions")=="true") << "\n";
    os << "use_X_ions = " << (int)(getStringOption_("use_X_ions")=="true") << "\n";
    os << "use_Y_ions = " << (int)(getStringOption_("use_Y_ions")=="true") << "\n";
    os << "use_Z_ions = " << (int)(getStringOption_("use_Z_ions")=="true") << "\n";
    os << "use_NL_ions = " << (int)(getStringOption_("use_NL_ions")=="true") << "\n";                         // 0=no, 1=yes to consider NH3/H2O neutral loss peaks

    // output
    os << "output_sqtstream = " << 0 << "\n";                    // 0=no, 1=yes  write sqt to standard output
    os << "output_sqtfile = " << 0 << "\n";                      // 0=no, 1=yes  write sqt file
    os << "output_txtfile = " << 0 << "\n";                     // 0=no, 1=yes  write tab-delimited txt file
    os << "output_pepxmlfile = " << 1 << "\n";                   // 0=no, 1=yes  write pep.xml file

    os << "output_percolatorfile = " << !getStringOption_("pin_out").empty() << "\n";              // 0=no, 1=yes  write Percolator tab-delimited input file
    os << "output_outfiles = " <<  0 << "\n";                    // 0=no, 1=yes  write .out files
    os << "print_expect_score = " << 1 << "\n";                  // 0=no, 1=yes to replace Sp with expect in out & sqt
    os << "num_output_lines = " << getIntOption_("num_hits") << "\n";                    // num peptide results to show
    os << "show_fragment_ions = " << 0 << "\n";                  // 0=no, 1=yes for out files only
    os << "sample_enzyme_number = " << enzyme_number << "\n";                // Sample enzyme which is possibly different than the one applied to the search.

    // mzXML parameters
    map<string,int> override_charge;
    override_charge["keep any known"] = 0;
    override_charge["ignore known"] = 1;
    override_charge["ignore outside range"] = 2;
    override_charge["keep known search unknown"] = 3;

    int precursor_charge_min(0), precursor_charge_max(0);
    if (!parseRange_(getStringOption_("precursor_charge"), precursor_charge_min, precursor_charge_max))
    {
      LOG_INFO << "precursor_charge range not set. Defaulting to 0:0 (disable charge filtering)." << endl;
    }

    os << "scan_range = " << "0 0" << "\n";                        // start and scan scan range to search; 0 as 1st entry ignores parameter
    os << "precursor_charge = " << precursor_charge_min << " " << precursor_charge_max << "\n";                  // precursor charge range to analyze; does not override any existing charge; 0 as 1st entry ignores parameter
    os << "override_charge = " << override_charge[getStringOption_("override_charge")] << "\n";                     // 0=no, 1=override precursor charge states, 2=ignore precursor charges outside precursor_charge range, 3=see online
    os << "ms_level = " << getIntOption_("ms_level") << "\n";                            // MS level to analyze, valid are levels 2 (default) or 3
    os << "activation_method = " << getStringOption_("activation_method") << "\n";                 // activation method; used if activation method set; allowed ALL, CID, ECD, ETD, PQD, HCD, IRMPD

    // misc parameters
    double digest_mass_range_min(600.0), digest_mass_range_max(5000.0);
    if (!parseRange_(getStringOption_("digest_mass_range"), digest_mass_range_min, digest_mass_range_max))
    {
      LOG_INFO << "digest_mass_range not set. Defaulting to 600.0 5000.0." << endl;
    }

    os << "digest_mass_range = " << digest_mass_range_min << " " << digest_mass_range_max << "\n";        // MH+ peptide mass range to analyze
    os << "num_results = " << 100 << "\n";                       // number of search hits to store internally
    os << "skip_researching = " << 1 << "\n";                    // for '.out' file output only, 0=search everything again (default), 1=don't search if .out exists
    os << "max_fragment_charge = " << getIntOption_("max_fragment_charge") << "\n";                 // set maximum fragment charge state to analyze (allowed max 5)
    os << "max_precursor_charge = " << getIntOption_("max_precursor_charge") << "\n";                // set maximum precursor charge state to analyze (allowed max 9)
    os << "nucleotide_reading_frame = " << 0 << "\n";            // 0=proteinDB, 1-6, 7=forward three, 8=reverse three, 9=all six
    os << "clip_nterm_methionine = " << (int)(getStringOption_("clip_nterm_methionine")=="true") << "\n";              // 0=leave sequences as-is; 1=also consider sequence w/o N-term methionine
    os << "spectrum_batch_size = " << getIntOption_("spectrum_batch_size") << "\n";                 // max. // of spectra to search at a time; 0 to search the entire scan range in one loop
    os << "decoy_prefix = " << "--decoysearch-not-used--" << "\n";                 // decoy entries are denoted by this string which is pre-pended to each protein accession
    os << "output_suffix = " << "" << "\n";                      // add a suffix to output base names i.e. suffix "-C" generates base-C.pep.xml from base.mzXML input
    os << "mass_offsets = " << ListUtils::concatenate(getDoubleList_("mass_offsets"), " ") << "\n"; // one or more mass offsets to search (values subtracted from deconvoluted precursor mass)

    // spectral processing
    map<string,int> remove_precursor_peak;
    remove_precursor_peak["no"] = 0;
    remove_precursor_peak["yes"] = 1;
    remove_precursor_peak["charge_reduced"] = 2;
    remove_precursor_peak["phosphate_loss"] = 3;

    double clear_mz_range_min(0.0), clear_mz_range_max(0.0);
    if (!parseRange_(getStringOption_("clear_mz_range"), clear_mz_range_min, clear_mz_range_max))
    {
      LOG_INFO << "clear_mz_range not set. Defaulting to 0:0 (disable m/z filter)." << endl;
    }

    os << "minimum_peaks = " << getIntOption_("minimum_peaks") << "\n";                      // required minimum number of peaks in spectrum to search (default 10)
    os << "minimum_intensity = " << getDoubleOption_("minimum_intensity") << "\n";                   // minimum intensity value to read in
    os << "remove_precursor_peak = " << remove_precursor_peak[getStringOption_("remove_precursor_peak")] << "\n";               // 0=no, 1=yes, 2=all charge reduced precursor peaks (for ETD)
    os << "remove_precursor_tolerance = " << getDoubleOption_("remove_precursor_tolerance") << "\n";        // +- Da tolerance for precursor removal
    os << "clear_mz_range = " << clear_mz_range_min << " " << clear_mz_range_max << "\n";                // for iTRAQ/TMT type data; will clear out all peaks in the specified m/z range


    // write fixed modifications - if not specified residue parameter is zero
    // Aminoacid:
    //      add_AA.OneletterCode_AA.ThreeLetterCode = xxx
    // Terminus:
    //      add_N/Cterm_peptide = xxx       protein not available yet
    vector<String> fixed_modifications_names = getStringList_("fixed_modifications");
    vector<ResidueModification> fixed_modifications = getModifications_(fixed_modifications_names);
    // Comet sets Carbamidometyl (C) as modification as default even if not specified
    // Therefor there is the need to set it to 0 if not set as flag
    if (fixed_modifications.empty())
    {
      os << "add_C_cysteine = 0.0000" << endl;
    }
    else
    {
      for (vector<ResidueModification>::const_iterator it = fixed_modifications.begin(); it != fixed_modifications.end(); ++it)
      {
        String AA = it->getOrigin();
        if ((AA!="N-term") && (AA!="C-term"))
        {
          const Residue* r = ResidueDB::getInstance()->getResidue(AA);
          String name = r->getName();
          os << "add_" << r->getOneLetterCode() << "_" << name.toLower() << " = " << it->getDiffMonoMass() << endl;
        }
        else
        {
          os << "add_" << AA.erase(1,1) << "_peptide = " << it->getDiffMonoMass() << endl;
        }
      }
    }

    //TODO register cut_before and cut_after in Enzymes.xml plus datastructures to add all our Enzymes with our names instead.
    // COMET_ENZYME_INFO _must_ be at the end of this parameters file
    os << "[COMET_ENZYME_INFO]" << "\n";
    os << "0.  No_enzyme              0      -           -" << "\n";
    os << "1.  Trypsin                1      KR          P" << "\n";
    os << "2.  Trypsin/P              1      KR          -" << "\n";
    os << "3.  Lys_C                  1      K           P" << "\n";
    os << "4.  Lys_N                  0      K           -" << "\n";
    os << "5.  Arg_C                  1      R           P" << "\n";
    os << "6.  Asp_N                  0      D           -" << "\n";
    os << "7.  CNBr                   1      M           -" << "\n";
    os << "8.  Glu_C                  1      DE          P" << "\n";
    os << "9.  PepsinA                1      FL          P" << "\n";
    os << "10. Chymotrypsin           1      FWYL        P" << "\n";
  }