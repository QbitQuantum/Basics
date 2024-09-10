  ExitCodes main_(int, const char**)
  {
    //-------------------------------------------------------------
    // parsing parameters
    //-------------------------------------------------------------

    String inputfile_name = getStringOption_("in");
    String outputfile_name = getStringOption_("out");
    Param fit_algorithm = getParam_().copy("fit_algorithm:", true);
    fit_algorithm.setValue("out_plot", getStringOption_("out_plot")); // re-assemble full param (was moved to top-level)
    bool split_charge = getFlag_("split_charge");
    bool top_hits_only = getFlag_("top_hits_only");
    double fdr_for_targets_smaller = getDoubleOption_("fdr_for_targets_smaller");
    bool target_decoy_available = false;
    bool ignore_bad_data = getFlag_("ignore_bad_data");
    bool prob_correct = getFlag_("prob_correct");

    // Set fixed e-value threshold
    smallest_e_value_ = numeric_limits<double>::denorm_min();

    //-------------------------------------------------------------
    // reading input
    //-------------------------------------------------------------
    IdXMLFile file;
    vector<ProteinIdentification> protein_ids;
    vector<PeptideIdentification> peptide_ids;
    file.load(inputfile_name, protein_ids, peptide_ids);
    vector<double> scores;
    vector<double> decoy;
    vector<double> target;
    set<Int> charges;
    PosteriorErrorProbabilityModel PEP_model;
    PEP_model.setParameters(fit_algorithm);
    StringList search_engines = ListUtils::create<String>("XTandem,OMSSA,MASCOT,SpectraST,MyriMatch,SimTandem,MSGFPlus,MS-GF+,Comet");
    //-------------------------------------------------------------
    // calculations
    //-------------------------------------------------------------
    if (split_charge)
    {
      for (vector<PeptideIdentification>::iterator pep_it = peptide_ids.begin(); pep_it != peptide_ids.end(); ++pep_it)
      {
        vector<PeptideHit>& hits = pep_it->getHits();
        for (std::vector<PeptideHit>::iterator hit_it = hits.begin(); hit_it != hits.end(); ++hit_it)
        {
          charges.insert(hit_it->getCharge());
        }
      }
      if (charges.empty())
      {
        throw Exception::ElementNotFound(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, "no charges found!");
      }
    }
    for (vector<PeptideIdentification>::iterator pep_it = peptide_ids.begin(); pep_it != peptide_ids.end(); ++pep_it)
    {
      if (!pep_it->getHits().empty())
      {
        target_decoy_available = ((pep_it->getScoreType() == "q-value") && pep_it->getHits()[0].metaValueExists("target_decoy"));
        break;
      }
    }

    set<Int>::iterator charge_it = charges.begin(); // charges can be empty, no problem if split_charge is not set
    if (split_charge && charges.empty())
    {
      throw Exception::Precondition(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION, "'split_charge' is set, but the list of charge states is empty");
    }
    map<String, vector<vector<double> > > all_scores;
    char splitter = ','; // to split the engine from the charge state later on
    do
    {
      for (StringList::iterator engine_it = search_engines.begin(); engine_it != search_engines.end(); ++engine_it)
      {
        for (vector<ProteinIdentification>::iterator prot_it = protein_ids.begin(); prot_it != protein_ids.end(); ++prot_it)
        {
          String searchengine = prot_it->getSearchEngine();
          if ((*engine_it == searchengine) || (*engine_it == searchengine.toUpper()))
          {
            for (vector<PeptideIdentification>::iterator pep_it = peptide_ids.begin(); pep_it != peptide_ids.end(); ++pep_it)
            {
              if (prot_it->getIdentifier() == pep_it->getIdentifier())
              {
                vector<PeptideHit>& hits = pep_it->getHits();
                if (top_hits_only)
                {
                  pep_it->sort();
                  if (!hits.empty() && (!split_charge || hits[0].getCharge() == *charge_it))
                  {
                    double score = getScore_(*engine_it, hits[0]);
                    if (!boost::math::isnan(score)) // issue #740: ignore scores with 0 values, otherwise you will get the error "unable to fit data"
                    {
                      scores.push_back(score);

                      if (target_decoy_available)
                      {
                        if (hits[0].getScore() < fdr_for_targets_smaller)
                        {
                          target.push_back(score);
                        }
                        else
                        {
                          decoy.push_back(score);
                        }
                      }
                    }
                  }
                }
                else
                {
                  for (std::vector<PeptideHit>::iterator hit_it = hits.begin(); hit_it != hits.end(); ++hit_it)
                  {
                    if (!split_charge || (hit_it->getCharge() == *charge_it))
                    {
                      double score = getScore_(*engine_it, *hit_it);
                      if (!boost::math::isnan(score)) // issue #740: ignore scores with 0 values, otherwise you will get the error "unable to fit data"
                      {
                        scores.push_back(score);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        if (scores.size() > 2)
        {
          vector<vector<double> > tmp;
          tmp.push_back(scores);
          tmp.push_back(target);
          tmp.push_back(decoy);
          if (split_charge)
          {
            String engine_with_charge_state = *engine_it + String(splitter) + String(*charge_it);
            all_scores.insert(make_pair(engine_with_charge_state, tmp));
          }
          else
          {
            all_scores.insert(make_pair(*engine_it, tmp));
          }
        }

        scores.clear();
        target.clear();
        decoy.clear();
      }

      if (split_charge) ++charge_it;
    }
    while (charge_it != charges.end());

    if (all_scores.empty())
    {
      writeLog_("No data collected. Check whether search engine is supported.");
      if (!ignore_bad_data) return INPUT_FILE_EMPTY;
    }

    String out_plot = fit_algorithm.getValue("out_plot").toString().trim();
    for (map<String, vector<vector<double> > >::iterator score_it = all_scores.begin(); score_it != all_scores.end(); ++score_it)
    {
      vector<String> engine_info;
      score_it->first.split(splitter, engine_info);
      String engine = engine_info[0];
      Int charge = -1;
      if (engine_info.size() == 2)
      {
        charge = engine_info[1].toInt();
      }
      if (split_charge)
      {
        // only adapt plot output if plot is requested (this badly violates the output rules and needs to change!)
        // one way to fix this: plot charges into a single file (no renaming of output file needed) - but this requires major code restructuring
        if (!out_plot.empty()) fit_algorithm.setValue("out_plot", out_plot + "_charge_" + String(charge));
        PEP_model.setParameters(fit_algorithm);
      }

      const bool return_value = PEP_model.fit(score_it->second[0]);
      if (!return_value) writeLog_("Unable to fit data. Algorithm did not run through for the following search engine: " + engine);
      if (!return_value && !ignore_bad_data) return UNEXPECTED_RESULT;

      if (return_value)
      {
        // plot target_decoy
        if (!out_plot.empty() && top_hits_only && target_decoy_available && (score_it->second[0].size() > 0))
        {
          PEP_model.plotTargetDecoyEstimation(score_it->second[1], score_it->second[2]); //target, decoy
        }

        bool unable_to_fit_data = true;
        bool data_might_not_be_well_fit = true;
        for (vector<ProteinIdentification>::iterator prot_it = protein_ids.begin(); prot_it != protein_ids.end(); ++prot_it)
        {
          String searchengine = prot_it->getSearchEngine();
          if ((engine == searchengine) || (engine == searchengine.toUpper()))
          {
            for (vector<PeptideIdentification>::iterator pep_it = peptide_ids.begin(); pep_it != peptide_ids.end(); ++pep_it)
            {
              if (prot_it->getIdentifier() == pep_it->getIdentifier())
              {
                String score_type = pep_it->getScoreType() + "_score";
                vector<PeptideHit> hits = pep_it->getHits();
                for (std::vector<PeptideHit>::iterator hit_it = hits.begin(); hit_it != hits.end(); ++hit_it)
                {
                  if (!split_charge || (hit_it->getCharge() == charge))
                  {
                    double score;
                    hit_it->setMetaValue(score_type, hit_it->getScore());

                    score = getScore_(engine, *hit_it);
                    if (boost::math::isnan(score)) // issue #740: ignore scores with 0 values, otherwise you will get the error "unable to fit data"
                    {
                      score = 1.0;
                    }
                    else 
                    { 
                      score = PEP_model.computeProbability(score);
                      if ((score > 0.0) && (score < 1.0)) unable_to_fit_data = false;  // only if all it->second[0] are 0 or 1 unable_to_fit_data stays true
                      if ((score > 0.2) && (score < 0.8)) data_might_not_be_well_fit = false;  //same as above
                    }
                    hit_it->setScore(score);
                    if (prob_correct)
                    {
                      hit_it->setScore(1.0 - score);
                    }
                    else
                    {
                      hit_it->setScore(score);
                    }
                  }
                }
                pep_it->setHits(hits);
              }
              if (prob_correct)
              {
                pep_it->setScoreType("Posterior Probability");
                pep_it->setHigherScoreBetter(true);
              }
              else
              {
                pep_it->setScoreType("Posterior Error Probability");
                pep_it->setHigherScoreBetter(false);
              }
            }
          }
        }
        if (unable_to_fit_data) writeLog_(String("Unable to fit data for search engine: ") + engine);
        if (unable_to_fit_data && !ignore_bad_data) return UNEXPECTED_RESULT;

        if (data_might_not_be_well_fit) writeLog_(String("Data might not be well fitted for search engine: ") + engine);
      }
    }
    //-------------------------------------------------------------
    // writing output
    //-------------------------------------------------------------
    file.store(outputfile_name, protein_ids, peptide_ids);
    return EXECUTION_OK;
  }