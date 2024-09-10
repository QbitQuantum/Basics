bool PeakBackground::isBackground(Mantid::API::IMDIterator *iterator) const {
  if (!HardThresholdBackground::isBackground(iterator)) {
    const VMD &center = iterator->getCenter();
    V3D temp(center[0], center[1], center[2]); // This assumes dims 1, 2, and 3
                                               // in the workspace correspond to
                                               // positions.

    for (int i = 0; i < m_peaksWS->getNumberPeaks(); ++i) {
      const IPeak &peak = m_peaksWS->getPeak(i);
      V3D coords = m_coordFunction(&peak);
      if (coords.distance(temp) < m_radiusEstimate) {
        return false;
      }
    }
  }
  return true;
}