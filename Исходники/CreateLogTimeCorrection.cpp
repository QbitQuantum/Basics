/** Get instrument geometry setup including L2 for each detector and L1
  */
void CreateLogTimeCorrection::getInstrumentSetup() {
  // 1. Get sample position and source position
  IComponent_const_sptr sample = m_instrument->getSample();
  if (!sample) {
    throw runtime_error("No sample has been set.");
  }
  V3D samplepos = sample->getPos();

  IComponent_const_sptr source = m_instrument->getSource();
  if (!source) {
    throw runtime_error("No source has been set.");
  }
  V3D sourcepos = source->getPos();
  m_L1 = sourcepos.distance(samplepos);

  // 2. Get detector IDs
  std::vector<detid_t> detids = m_instrument->getDetectorIDs(true);
  for (auto &detid : detids) {
    IDetector_const_sptr detector = m_instrument->getDetector(detid);
    V3D detpos = detector->getPos();
    double l2 = detpos.distance(samplepos);
    m_l2map.emplace(detid, l2);
  }

  // 3. Output information
  g_log.information() << "Sample position = " << samplepos << "; "
                      << "Source position = " << sourcepos << ", L1 = " << m_L1
                      << "; "
                      << "Number of detector/pixels = " << detids.size()
                      << ".\n";
}