int main(int argc, char* argv[]) {

  //if (argc < 3  || argc > 6) usage();
  string audioFilename;
  string outputFilename;
  bool computeSegmentation = false;
  Real startTime = 0, endTime = 2000;

  switch (argc) {
    case 3:
      audioFilename =  argv[1];
      outputFilename = argv[2];
      break;
    case 4:
    {
      audioFilename =  argv[1];
      outputFilename = argv[2];
      string s(argv[3]);
      string::size_type pos = s.find("segment=");
      if (pos == string::npos) {
        cout << "Unrecognize option \"" << argv[3] << "\"" << endl;
        exit(2);
      }
      string segmentation = s.substr(s.find("=")+1, string::npos);
      if (segmentation=="true") computeSegmentation = true;
      break;
    }
    case 5:
      audioFilename =  argv[1];
      outputFilename = argv[2];
      startTime = atof(argv[3]);
      endTime = atof(argv[4]);
      cout << "processing audio from " << startTime << "s. to " << endTime << "s." << endl;
      break;
    case 6:
      cout << "Segmentation only available on the entire audio file" << endl;
      break;
    default:
      usage();
  }

  // Register the algorithms in the factory(ies)
  essentia::init();

  // pool cotaining profile (configure) options; use default settings
  Pool options;
  setOptions(options, "");

  // pool for storing results
  Pool pool;
  // this pool contains only descriptors computed after applying equal loudness
  // filetering:
  pool.set("metadata.audio_properties.equal_loudness", true);

  if (computeSegmentation) {
    // pool for storing segments:
    computeReplayGain(audioFilename, startTime, endTime, pool, options);
    computeSegments(audioFilename, startTime, endTime, pool, options);
    vector<Real> segments = pool.value<vector<Real> >("segmentation.timestamps");
    for (int i=0; i<int(segments.size()-1); ++i) {
      startTime = segments[i];
      endTime = segments[i+1];
      cout << "\n**************************************************************************";
      cout << "\nSegment " << i << ": processing audio from " << startTime << "s. to " << endTime << "s.";
      cout << "\n**************************************************************************" << endl;
      ostringstream ns;
      ns << "segment_" << i ;
      computeLowLevel(audioFilename, startTime, endTime, pool, options, ns.str());
      computeMidLevel(audioFilename, startTime, endTime, pool, options, ns.str());
      //computePanning(audioFilename, startTime, endTime, pool, options, ns.str());
      computeHighlevel(pool, options, ns.str());
    }
    cout << "\n**************************************************************************" << endl;
    Pool stats = computeAggregation(pool, segments.size());
    outputToFile(stats, outputFilename);
  }
  else {
    try {
      compute(audioFilename, outputFilename, startTime, endTime, pool, options);
    }
    catch (EssentiaException& e) {
      cout << e.what() << endl;
    }
  }

  pool.remove("metadata.audio_properties.downmix");
  essentia::shutdown();

  return 0;
}