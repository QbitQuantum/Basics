Pool FreesoundExtractor::computeAggregation(Pool& pool){

  // choose which descriptors stats to output
  const char* defaultStats[] = { "mean", "var", "min", "max", "dmean", "dmean2", "dvar", "dvar2" };
 
  map<string, vector<string> > exceptions;
  //TODO: review exceptions

  standard::Algorithm* aggregator = standard::AlgorithmFactory::create("PoolAggregator",
                                                                       "defaultStats", arrayToVector<string>(defaultStats),
                                                                       "exceptions", exceptions);
  Pool poolStats;
  aggregator->input("input").set(pool);
  aggregator->output("output").set(poolStats);

  aggregator->compute();

  // add descriptors that may be missing due to content
  const Real emptyVector[] = { 0, 0, 0, 0, 0, 0};
  
  int statsSize = int(sizeof(defaultStats)/sizeof(defaultStats[0]));

  if(!pool.contains<vector<Real> >("rhythm.beats_loudness")){
    for (uint i=0; i<statsSize; i++)
        poolStats.set(string("rhythm.beats_loudness.")+defaultStats[i],0); 
    }
  if(!pool.contains<vector<vector<Real> > >("rhythm.beats_loudness_band_ratio"))
    for (uint i=0; i<statsSize; i++) 
      poolStats.set(string("rhythm.beats_loudness_band_ratio.")+defaultStats[i],
        arrayToVector<Real>(emptyVector));
  else if (pool.value<vector<vector<Real> > >("rhythm.beats_loudness_band_ratio").size()<2){
      poolStats.remove(string("rhythm.beats_loudness_band_ratio"));
      for (uint i=0; i<statsSize; i++) {
        if(i==1 || i==6 || i==7)// var, dvar and dvar2 are 0
          poolStats.set(string("rhythm.beats_loudness_band_ratio.")+defaultStats[i],
              arrayToVector<Real>(emptyVector));
        else
          poolStats.set(string("rhythm.beats_loudness_band_ratio.")+defaultStats[i],
              pool.value<vector<vector<Real> > >("rhythm.beats_loudness_band_ratio")[0]);
      }
  }

    
    
  // variable descriptor length counts
    poolStats.set(string("rhythm.onset_count"), pool.value<vector<Real> >("rhythm.onset_times").size());
    poolStats.set(string("rhythm.beats_count"), pool.value<vector<Real> >("rhythm.beats_position").size());
    poolStats.set(string("tonal.chords_count"), pool.value<vector<string> >("tonal.chords_progression").size());
    
  delete aggregator;

  return poolStats;
}