/**
 * Generate a random position within the final detector in the lab frame
 * @param nominalPos The poisiton of the centre point of the detector
 * @param energy The final energy of the neutron
 * @param scatterPt The position of the scatter event that lead to this
 * detector
 * @param direcBeforeSc Directional vector that lead to scatter point that hit
 * this detector
 * @param scang [Output] The value of the scattering angle for the generated
 * point
 * @param distToExit [Output] The distance covered within the object from
 * scatter to exit
 * @return A new position in the detector
 */
V3D VesuvioCalculateMS::generateDetectorPos(
    const V3D &nominalPos, const double energy, const V3D &scatterPt,
    const V3D &direcBeforeSc, double &scang, double &distToExit) const {
  // Inverse attenuation length (m-1) for vesuvio det.
  const double mu = 7430.0 / sqrt(energy);
  // Probability of detection in path thickness.
  const double ps = 1.0 - exp(-mu * m_detThick);
  V3D detPos;
  scang = 0.0;
  distToExit = 0.0;
  size_t ntries(0);
  do {
    // Beam direction by moving to front of "box"define by detector dimensions
    // and then
    // computing expected distance travelled based on probability
    detPos[m_beamIdx] = (nominalPos[m_beamIdx] - 0.5 * m_detThick) -
                        (log(1.0 - m_randgen->flat() * ps) / mu);
    // perturb away from nominal position
    detPos[m_acrossIdx] =
        nominalPos[m_acrossIdx] + (m_randgen->flat() - 0.5) * m_detWidth;
    detPos[m_upIdx] =
        nominalPos[m_upIdx] + (m_randgen->flat() - 0.5) * m_detHeight;

    // Distance to exit the sample for this order
    V3D scToDet = detPos - scatterPt;
    scToDet.normalize();
    Geometry::Track scatterToDet(scatterPt, scToDet);
    if (m_sampleShape->interceptSurface(scatterToDet) > 0) {
      scang = direcBeforeSc.angle(scToDet);
      const auto &link = scatterToDet.cbegin();
      distToExit = link->distInsideObject;
      break;
    }
    // if point is very close surface then there may be no valid intercept so
    // try again
    ++ntries;
  } while (ntries < MAX_SCATTER_PT_TRIES);
  if (ntries == MAX_SCATTER_PT_TRIES) {
    // Assume it is very close to the surface so that the distance travelled
    // would
    // be a neglible contribution
    distToExit = 0.0;
  }
  return detPos;
}