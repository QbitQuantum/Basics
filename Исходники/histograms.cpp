void VectorHistogram::AddVector(float x, float y) {
  bins_[NormAngle(x, y) * num_bins_] += hypot(x, y);
  ++num_vectors_;
}