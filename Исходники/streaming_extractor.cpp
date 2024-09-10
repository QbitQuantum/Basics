void computeReplayGain(const string& audioFilename, Real startTime, Real endTime, Pool& pool) {

  streaming::AlgorithmFactory& factory = streaming::AlgorithmFactory::instance();

  Real analysisSampleRate = 44100;


  /*************************************************************************
   *    1st pass: get metadata and replay gain                             *
   *************************************************************************/

  readMetadata(audioFilename, pool);

  string downmix = "mix";
  Real replayGain = 0.0;
  bool tryReallyHard = true;
  int length = 0;

  while (tryReallyHard) {
    Algorithm* audio_1 = factory.create("EqloudLoader",
                                        "filename", audioFilename,
                                        "sampleRate", analysisSampleRate,
                                        "startTime", startTime,
                                        "endTime", endTime,
                                        "downmix", downmix);

    Algorithm* rgain = factory.create("ReplayGain",
                                      "applyEqloud", false);

    pool.set("metadata.audio_properties.analysis_sample_rate", audio_1->parameter("sampleRate").toReal());
    pool.set("metadata.audio_properties.downmix", downmix);

    connect(audio_1->output("audio"), rgain->input("signal"));
    connect(rgain->output("replayGain"), pool, "metadata.audio_properties.replay_gain");

    cout << "Process step 1: Replay Gain" << endl;
    try {
      runGenerator(audio_1);
      length = audio_1->output("audio").totalProduced();
      deleteNetwork(audio_1);
      tryReallyHard = false;
    }

    catch (const EssentiaException&) {
      if (downmix == "mix") {
        downmix = "left";
        try {
          pool.remove("metadata.audio_properties.downmix");
          pool.remove("metadata.audio_properties.replay_gain");
        }
        catch (EssentiaException&) {}

        continue;
      }
      else {
        cerr << "ERROR: File looks like a completely silent file... Aborting..." << endl;
        exit(4);
      }
    }

    replayGain = pool.value<Real>("metadata.audio_properties.replay_gain");

    // very high value for replayGain, we are probably analyzing a silence even
    // though it is not a pure digital silence
    if (replayGain > 20.0) {
      // NB: except if it was some electro music where someone thought it was smart
      //     to have opposite left and right channels... Try with only the left
      //     channel, then.
      if (downmix == "mix") {
        downmix = "left";
        tryReallyHard = true;
        pool.remove("metadata.audio_properties.downmix");
        pool.remove("metadata.audio_properties.replay_gain");
      }
      else {
        cerr << "ERROR: File looks like a completely silent file... Aborting..." << endl;
        exit(5);
      }
    }
  }
  // set length (actually duration) of the file:
  pool.set("metadata.audio_properties.length", length/analysisSampleRate);

  cout.precision(10);
}