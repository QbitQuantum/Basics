int main(int argc, char** argv)
{
  // Parse command line options.
  CLI::ParseCommandLine(argc, argv);

  // Set random seed.
  if (CLI::GetParam<int>("seed") != 0)
    RandomSeed((size_t) CLI::GetParam<int>("seed"));
  else
    RandomSeed((size_t) time(NULL));

  // Load observations.
  const string modelFile = CLI::GetParam<string>("model_file");
  const int length = CLI::GetParam<int>("length");
  const int startState = CLI::GetParam<int>("start_state");

  if (length <= 0)
  {
    Log::Fatal << "Invalid sequence length (" << length << "); must be greater "
        << "than or equal to 0!" << endl;
  }

  // Load model, but first we have to determine its type.
  SaveRestoreUtility sr;
  sr.ReadFile(modelFile);
  string emissionType;
  sr.LoadParameter(emissionType, "emission_type");

  mat observations;
  Col<size_t> sequence;
  if (emissionType == "DiscreteDistribution")
  {
    HMM<DiscreteDistribution> hmm(1, DiscreteDistribution(1));
    hmm.Load(sr);

    if (startState < 0 || startState >= (int) hmm.Transition().n_rows)
    {
      Log::Fatal << "Invalid start state (" << startState << "); must be "
          << "between 0 and number of states (" << hmm.Transition().n_rows
          << ")!" << endl;
    }

    hmm.Generate(size_t(length), observations, sequence, size_t(startState));
  }
  else if (emissionType == "GaussianDistribution")
  {
    HMM<GaussianDistribution> hmm(1, GaussianDistribution(1));
    hmm.Load(sr);

    if (startState < 0 || startState >= (int) hmm.Transition().n_rows)
    {
      Log::Fatal << "Invalid start state (" << startState << "); must be "
          << "between 0 and number of states (" << hmm.Transition().n_rows
          << ")!" << endl;
    }

    hmm.Generate(size_t(length), observations, sequence, size_t(startState));
  }
  else if (emissionType == "GMM")
  {
    HMM<GMM<> > hmm(1, GMM<>(1, 1));
    hmm.Load(sr);

    if (startState < 0 || startState >= (int) hmm.Transition().n_rows)
    {
      Log::Fatal << "Invalid start state (" << startState << "); must be "
          << "between 0 and number of states (" << hmm.Transition().n_rows
          << ")!" << endl;
    }

    hmm.Generate(size_t(length), observations, sequence, size_t(startState));
  }
  else
  {
    Log::Fatal << "Unknown HMM type '" << emissionType << "' in file '" << modelFile
        << "'!" << endl;
  }

  // Save observations.
  const string outputFile = CLI::GetParam<string>("output_file");
  data::Save(outputFile, observations, true);

  // Do we want to save the hidden sequence?
  const string sequenceFile = CLI::GetParam<string>("state_file");
  if (sequenceFile != "")
    data::Save(sequenceFile, sequence, true);
  
  return 0;
}