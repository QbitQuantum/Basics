/** Calculate the hkl corresponding to a given Q-vector
 * @param Q :: Q-vector in $AA^-1 in the sample frame
 * @return a V3D with H,K,L
 */
V3D OrientedLattice::hklFromQ(const V3D &Q) const {
  DblMatrix UBinv = this->getUB();
  UBinv.Invert();
  V3D out = UBinv * Q / TWO_PI; // transform back to HKL
  return out;
}