double WCV_TEP::horizontal_tvar(const Vect2& s, const Vect2& v) const {
  // Time variable is Modified Tau
  double TEP = -1;
  double sdotv = s.dot(v);
  if (sdotv < 0)
    return (Util::sq(table.getDTHR())-s.sqv())/sdotv;
  return TEP;
}