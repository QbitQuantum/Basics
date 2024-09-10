vector<intn> Quantize(const vector<floatn>& points, const Resln& resln) {
  if (points.empty())
    return vector<intn>();

  BoundingBox<floatn> bb;
  for (const floatn& p : points) {
    bb(p);
  }
  const float dwidth = bb.max_size();
  if (dwidth == 0) {
    vector<intn> ret;
    ret.push_back(make_intn(0));
    return ret;
  }

  // Quantize points to integers
  vector<intn> qpoints(points.size());
  for (int i = 0; i < points.size(); ++i) {
    const floatn& p = points[i];
    intn q = make_intn(0);
    for (int k = 0; k < DIM; ++k) {
      const double d =
          (resln.width-1) * ((p.s[k] - bb.min().s[k]) / dwidth);
      const int v = static_cast<int>(d+0.5);
      if (v < 0) {
        cerr << "Coordinate in dimension " << k << " is less than zero.  d = "
             << d << " v = " << v << endl;
        cerr << "  p[k] = " << p.s[k]
             << " bb.min()[k] = " << bb.min().s[k] << endl;
        cerr << "  dwidth = " << dwidth << " kwidth = " << resln.width << endl;
        throw logic_error("bad coordinate");
      }
      q.s[k] = v;
    }
    qpoints[i] = q;
  }
  
  return qpoints;
}