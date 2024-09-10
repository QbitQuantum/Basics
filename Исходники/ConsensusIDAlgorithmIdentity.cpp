  void ConsensusIDAlgorithmIdentity::preprocess_(
    vector<PeptideIdentification>& ids)
  {
    // check score types and orientations:
    bool higher_better = ids[0].isHigherScoreBetter();
    set<String> score_types;

    for (vector<PeptideIdentification>::iterator pep_it = ids.begin();
         pep_it != ids.end(); ++pep_it)
    {
      if (pep_it->isHigherScoreBetter() != higher_better)
      {
        // scores with different orientations definitely aren't comparable:
        String hi_lo = higher_better ? "higher/lower" : "lower/higher";
        String msg = "Score types '" + ids[0].getScoreType() + "' and '" +
          pep_it->getScoreType() + "' have different orientations (" + hi_lo +
          " is better) and cannot be compared meaningfully.";
        throw Exception::InvalidValue(__FILE__, __LINE__, OPENMS_PRETTY_FUNCTION,
                                      msg, higher_better ? "false" : "true");
      }
      score_types.insert(pep_it->getScoreType());
    }

    if (score_types.size() > 1)
    {
      String types;
      types.concatenate(score_types.begin(), score_types.end(), "'/'");
      LOG_WARN << "Warning: Different score types for peptide hits found ('"
               << types << "'). If the scores are not comparable, "
               << "results will be meaningless." << endl;
    }
  }