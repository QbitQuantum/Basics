int main(int argc, char* argv[]) {

  // input correct?
  if (argc != 3) {
    cout << "Error: incorrect number of arguments." << endl;
    cout << "Usage: " << argv[0] << " audio_input yaml_output" << endl;
    creditLibAV();
    exit(1);
  }

  // yes!
  string audioFilename = argv[1];
  string outputFilename = argv[2];

  // register the algorithms in the factory
  essentia::init();

  // parameters
  int sampleRate   = 22050;
  int frameSize    = 8192;
  int hopSize      = 1024;
  int rmsFrameSize = 256;
  int rmsHopSize   = 32;

  // instantiate algorithms
  AlgorithmFactory& factory = AlgorithmFactory::instance();

  Algorithm* audio    = factory.create("MonoLoader",
                                       "filename", audioFilename,
                                       "sampleRate", sampleRate);

  Algorithm* fc       = factory.create("FrameCutter",
                                       "frameSize", frameSize,
                                       "hopSize", hopSize);

  Algorithm* w        = factory.create("Windowing",
                                       "type", "blackmanharris62");

  Algorithm* spec     = factory.create("Spectrum");

  Algorithm* melBands = factory.create("MelBands",
                                       "sampleRate", sampleRate,
		                               "numberBands", 40,
		                               "lowFrequencyBound", 0,
		                               "highFrequencyBound", sampleRate/2);


  Algorithm* rd       = factory.create("RhythmTransform",
				                       "frameSize", rmsFrameSize,
				                       "hopSize", rmsHopSize);

  // connect algorithms:

  // set audio loader:
  vector<Real> audioBuffer;
  audio->output("audio").set(audioBuffer);

  // set frameCutter:
  vector<Real> frame;
  fc->input("signal").set(audioBuffer);
  fc->output("frame").set(frame);

  // set windowing:
  vector<Real> windowedFrame;
  w->input("frame").set(frame);
  w->output("frame").set(windowedFrame);

  // set spectrum:
  vector<Real> spectrum;
  spec->input("frame").set(windowedFrame);
  spec->output("spectrum").set(spectrum);

  // set melbands:
  vector<Real> bands;
  melBands->input("spectrum").set(spectrum);
  melBands->output("bands").set(bands);

  // storage:
  Pool pool;

  // load audio:
  audio->compute();

  // process frames:
  while (true) {

    // compute a frame
    fc->compute();

    // if it was the last one (ie: it was empty), then we're done.
    if (!frame.size()) {
      break;
    }

    // if the frame is silent, just drop it and go on processing
    //if (isSilent(frame)) continue;

    w->compute();
    spec->compute();
    melBands->compute();

    pool.add("spectral.mel_bands_energy", bands);
  }

  // compute rhythm transform:

  vector<vector<Real> > rhythm;
  rd->input("melBands").set(pool.value<vector<vector<Real> > >("spectral.mel_bands_energy"));
  rd->output("rhythm").set(rhythm);
  rd->compute();

  pool.remove("spectral.mel_bands_energy");

  // output to file:
  Algorithm* yamlOutput = AlgorithmFactory::create("YamlOutput",
                                                   "filename", outputFilename);

  yamlOutput->input("pool").set(pool);

  // run algorithms
  for(int i=0; i<(int)rhythm.size(); i++)
    pool.add("rhythdomain.frames", rhythm[i]);
  yamlOutput->compute();

  // clean up
  delete audio;
  delete fc;
  delete w;
  delete spec;
  delete melBands;
  delete rd;
  delete yamlOutput;

  essentia::shutdown();

  return 0;
}