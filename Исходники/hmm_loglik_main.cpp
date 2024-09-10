int main(int argc, char** argv)
{
  // Parse command line options.
  CLI::ParseCommandLine(argc, argv);

  // Load observations.
  const string inputFile = CLI::GetParam<string>("input_file");
  const string modelFile = CLI::GetParam<string>("model_file");

  mat dataSeq;
  data::Load(inputFile, dataSeq, true);

  // Load model, but first we have to determine its type.
  SaveRestoreUtility sr;
  sr.ReadFile(modelFile);
  string type;
  sr.LoadParameter(type, "hmm_type");

  double loglik = 0;
  if (type == "discrete")
  {
    HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1));

    LoadHMM(hmm, sr);

    // Verify only one row in observations.
    if (dataSeq.n_cols == 1)
      dataSeq = trans(dataSeq);

    if (dataSeq.n_rows > 1)
      Log::Fatal << "Only one-dimensional discrete observations allowed for "
          << "discrete HMMs!" << endl;

    loglik = hmm.LogLikelihood(dataSeq);
  }
  else if (type == "gaussian")
  {
    HMM<GaussianDistribution> hmm(1, GaussianDistribution(1));

    LoadHMM(hmm, sr);

    // Verify correct dimensionality.
    if (dataSeq.n_rows != hmm.Emission()[0].Mean().n_elem)
      Log::Fatal << "Observation dimensionality (" << dataSeq.n_rows << ") "
          << "does not match HMM Gaussian dimensionality ("
          << hmm.Emission()[0].Mean().n_elem << ")!" << endl;

    loglik = hmm.LogLikelihood(dataSeq);
  }
  else if (type == "gmm")
  {
    HMM<GMM<> > hmm(1, GMM<>(1, 1));

    LoadHMM(hmm, sr);

    // Verify correct dimensionality.
    if (dataSeq.n_rows != hmm.Emission()[0].Dimensionality())
      Log::Fatal << "Observation dimensionality (" << dataSeq.n_rows << ") "
          << "does not match HMM Gaussian dimensionality ("
          << hmm.Emission()[0].Dimensionality() << ")!" << endl;

    loglik = hmm.LogLikelihood(dataSeq);
  }
  else
  {
    Log::Fatal << "Unknown HMM type '" << type << "' in file '" << modelFile
        << "'!" << endl;
  }

  cout << loglik << endl;
}