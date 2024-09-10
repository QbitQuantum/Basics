float inverted_index_storage::calc_l2norm(const sfv_t& sfv) {
  float ret = 0.f;
  for (size_t i = 0; i < sfv.size(); ++i) {
    ret += sfv[i].second * sfv[i].second;
  }
  return sqrt(ret);
}