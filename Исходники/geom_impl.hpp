void centroid(iter_t begin, iter_t end, adapt_t adapt, vector<ndim>& c) {
  c.setZero();
  int n = 0;
  for (; begin != end; ++begin, ++n) {
    c += adapt(*begin);
  }
  c /= double(n);
}