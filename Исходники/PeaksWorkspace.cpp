/**
 * Returns selected information for a "peak" at QLabFrame.
 *
 * @param qFrame      An arbitrary position in Q-space.  This does not have to
 *be the
 *                    position of a peak.
 * @param labCoords  Set true if the position is in the lab coordinate system,
 *false if
 *                    it is in the sample coordinate system.
 * @return a vector whose elements contain different information about the
 *"peak" at that position.
 *         each element is a pair of description of information and the string
 *form for the corresponding
 *         value.
 */
int PeaksWorkspace::peakInfoNumber(Kernel::V3D qFrame, bool labCoords) const {
  std::vector<std::pair<std::string, std::string>> Result;
  std::ostringstream oss;
  oss << std::setw(12) << std::fixed << std::setprecision(3) << (qFrame.norm());
  std::pair<std::string, std::string> QMag("|Q|", oss.str());
  Result.push_back(QMag);

  oss.str("");
  oss.clear();
  oss << std::setw(12) << std::fixed << std::setprecision(3)
      << (2.0 * M_PI / qFrame.norm());

  std::pair<std::string, std::string> dspc("d-spacing", oss.str());
  oss.str("");
  oss.clear();
  Result.push_back(dspc);

  int seqNum = -1;
  double minDist = 10000000;

  for (int i = 0; i < getNumberPeaks(); i++) {
    Peak pk = getPeak(i);
    V3D Q = pk.getQLabFrame();
    if (!labCoords)
      Q = pk.getQSampleFrame();
    double D = qFrame.distance(Q);
    if (D < minDist) {
      minDist = D;
      seqNum = i + 1;
    }
  }
  return seqNum;
}