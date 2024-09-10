void alignTicks(const string& audioFilename, Pool& pool, Real windowLength) {
  // As ticks are normally not so well aligned, this function tries to align
  // them with the nearest onset
  Real sampleRate = pool.value<Real>("sampleRate");
  standard::AlgorithmFactory& factory = standard::AlgorithmFactory::instance();
  standard::Algorithm* loader = factory.create("EasyLoader",
                                               "filename",   audioFilename,
                                               "downmix", "left",
                                               "startTime",  0,
                                               "endTime",    2000,
                                               "sampleRate", sampleRate);
  vector<Real> audio;
  loader->output("audio").set(audio);
  loader->compute();
  delete loader;
  Real audioLength = audio.size()/sampleRate;
  const vector<Real>& ticks = pool.value<vector<Real> >("ticks");
  int nticks = ticks.size();
  vector<Real> newTicks;
  newTicks.reserve(nticks);
  standard::Algorithm* trimmer = factory.create("Trimmer",
                                                "sampleRate", sampleRate);
  vector<Real> trimmedAudio;
  trimmer->input("signal").set(audio);
  trimmer->output("signal").set(trimmedAudio);
  int frameSize = 1024;
  int hopSize = frameSize/8;
  standard::Algorithm* fc = factory.create("FrameCutter",
                                           "startFromZero", true,
                                           "frameSize", frameSize,
                                           "hopSize", hopSize);
  standard::Algorithm* w = factory.create("Windowing");
  standard::Algorithm* spec = factory.create("Spectrum");
  standard::Algorithm* flux = factory.create("Flux");
  vector<Real> frame, windowedFrame, spectrum;
  Real fluxValue;
  fc->input("signal").set(trimmedAudio);
  fc->output("frame").set(frame);
  w->input("frame").set(frame);
  w->output("frame").set(windowedFrame);
  spec->input("frame").set(windowedFrame);
  spec->output("spectrum").set(spectrum);
  flux->input("spectrum").set(spectrum);
  flux->output("flux").set(fluxValue);
  for (int i=0; i<nticks; i++) {
    if (ticks[i] >= audioLength) break;
    Real startTime = max(ticks[i]-windowLength, Real(0));
    Real endTime = min(startTime+2*windowLength, audioLength);
    trimmer->configure("startTime", startTime, "endTime", endTime);
    trimmer->compute();
    vector<Real> fluxValues;
    fluxValues.reserve(trimmedAudio.size()/hopSize);
    while (true) {
      fc->compute();
      if (frame.empty()) break;
      w->compute();
      spec->compute();
      flux->compute();
      fluxValues.push_back(fluxValue);
    }
    fc->reset();
    int fluxSize = fluxValues.size();
    if (fluxSize<1) break;
    vector<Real> dfluxValues(fluxSize-1,0);
    for (int j=0; j<(int)fluxSize-1; j++) {
      Real delta = fluxValues[j+1]-fluxValues[j];
      if (delta>0) dfluxValues[j] = delta;
    }
    int maxIdx = argmax(dfluxValues);
    newTicks.push_back(startTime+Real(maxIdx*hopSize/sampleRate));
  }
  pool.remove("ticks");
  for (int i=0; i<(int)newTicks.size(); i++) pool.add("ticks", newTicks[i]);
  delete fc;
  delete w;
  delete spec;
  delete flux;
  delete trimmer;
}