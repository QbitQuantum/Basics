int main()
{
 
  string year = "2014";
  string team = "ATL";
  string col = "1";
  // Load observations.
  const string inputFile =  "state_data/2014/2014ATL_state_col0.csv";
  const string modelFile = "simulation_data/" + year + "/" + year + team + "sim_col" + col + ".xml";

  mat dataSeq;
  data::Load(inputFile, dataSeq, true);

  // Load model, but first we have to determine its type.
  SaveRestoreUtility sr;
  sr.ReadFile(modelFile);
  string type;
  sr.LoadParameter(type, "hmm_type");

  arma::Col<size_t> sequence;
  if (type == "discrete")
  {
    HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1));

    LoadHMM(hmm, sr);

    // Verify only one row in observations.
    if (dataSeq.n_cols == 1)
      dataSeq = trans(dataSeq);

    if (dataSeq.n_rows > 1)
     std::cout<< "Only one-dimensional discrete observations allowed for "<< "discrete HMMs!" << endl;

    hmm.Predict(dataSeq, sequence);
  }
 
  // Save output.
  const string outputFile = "simulation_data/" + year + "/" + year + team + "sim_col" + col + "_data" + ".csv";
  data::Save(outputFile, sequence, true);
}