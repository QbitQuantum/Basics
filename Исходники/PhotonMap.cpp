void PhotonMapProperty::operator()(Photon const &photon) {
  ++nPhotons_;

  tgir::Real const rPower = photon.pow();

  rPowerAvg_ += rPower;
  rPowerVar_ += hi::square_of(rPower);

  if (rPowerMin_ > rPower) {
    rPowerMin_ = rPower;
  }

  if (rPowerMax_ < rPower) {
    rPowerMax_ = rPower;
  }
}