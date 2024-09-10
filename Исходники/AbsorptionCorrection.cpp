/// Calculate the distances traversed by the neutrons within the sample
/// @param detector :: The detector we are working on
/// @param L2s :: A vector of the sample-detector distance for  each segment of
/// the sample
void AbsorptionCorrection::calculateDistances(const IDetector &detector,
                                              std::vector<double> &L2s) const {
  V3D detectorPos(detector.getPos());
  if (detector.nDets() > 1) {
    // We need to make sure this is right for grouped detectors - should use
    // average theta & phi
    detectorPos.spherical(detectorPos.norm(),
                          detector.getTwoTheta(V3D(), V3D(0, 0, 1)) * 180.0 /
                              M_PI,
                          detector.getPhi() * 180.0 / M_PI);
  }

  for (size_t i = 0; i < m_numVolumeElements; ++i) {
    // Create track for distance in cylinder between scattering point and
    // detector
    V3D direction = detectorPos - m_elementPositions[i];
    direction.normalize();
    Track outgoing(m_elementPositions[i], direction);
    int temp = m_sampleObject->interceptSurface(outgoing);

    /* Most of the time, the number of hits is 1. Sometime, we have more than
     * one intersection due to
     * arithmetic imprecision. If it is the case, then selecting the first
     * intersection is valid.
     * In principle, one could check the consistency of all distances if hits is
     * larger than one by doing:
     * Mantid::Geometry::Track::LType::const_iterator it=outgoing.begin();
     * and looping until outgoing.end() checking the distances with it->Dist
     */
    // Not hitting the cylinder from inside, usually means detector is badly
    // defined,
    // i.e, position is (0,0,0).
    if (temp < 1) {
      // FOR NOW AT LEAST, JUST IGNORE THIS ERROR AND USE A ZERO PATH LENGTH,
      // WHICH I RECKON WILL MAKE A
      // NEGLIGIBLE DIFFERENCE ANYWAY (ALWAYS SEEMS TO HAPPEN WITH ELEMENT RIGHT
      // AT EDGE OF SAMPLE)
      L2s[i] = 0.0;

      // std::ostringstream message;
      // message << "Problem with detector at " << detectorPos << " ID:" <<
      // detector->getID() << '\n';
      // message << "This usually means that this detector is defined inside the
      // sample cylinder";
      // g_log.error(message.str());
      // throw std::runtime_error("Problem in
      // AbsorptionCorrection::calculateDistances");
    } else // The normal situation
    {
      L2s[i] = outgoing.cbegin()->distFromStart;
    }
  }
}