void LevelAverage(Pool& pool, const string& nspace) {

  // namespace:
  string llspace = "lowlevel.";
  if (!nspace.empty()) llspace = nspace + ".lowlevel.";

  vector<Real> levelArray = pool.value<vector<Real> >(llspace + "loudness");
  pool.remove(llspace + "loudness");

  // Maximum dynamic
  Real EPSILON = 10e-5;
  Real maxValue = levelArray[argmax(levelArray)];
  if (maxValue <= EPSILON) {
    maxValue = EPSILON;
  }

  // Normalization to the maximum
  Real THRESHOLD = 0.0001; // this corresponds to -80dB
  for (uint i=0; i<levelArray.size(); i++) {
    levelArray[i] /= maxValue;
    if (levelArray[i] <= THRESHOLD) {
      levelArray[i] = THRESHOLD;
    }
  }

  // Average Level
  Real levelAverage = 10*log10(mean(levelArray));

  // Re-scaling and range-control
  // This yields in numbers between
  // 0 for signals with  large dynamic variace and thus low dynamic average
  // 1 for signal with little dynamic range and thus
  // a dynamic average close to the maximum
  Real x1 = -5.0;
  Real x2 = -2.0;
  Real levelAverageSqueezed = squeezeRange(levelAverage, x1, x2);
  pool.set(llspace + "average_loudness", levelAverageSqueezed);
}