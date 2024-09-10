v4f step_t::operator () (float t) const
{
  // Evaluate the polynomial f by Estrin's method. Return
  //   (0 0 0 0)  if t < t0,
  //   (f f f f)  if t0 <= t < t1,
  //   (1 1 1 1)  if t > t1.
  v4f c4 = load4f (c);
  v4f one = { 1.0f, 1.0f, 1.0f, 1.0f };
  v4f tttt = _mm_set1_ps (t);           // t t t t
  v4f tt = _mm_unpacklo_ps (one, tttt); // 1 t 1 t
  v4f f0 = c4 * tt;                     // c0 c1*t c2 c3*t
  v4f ha = _mm_hadd_ps (f0, f0) * tt * tt;
  v4f f = _mm_hadd_ps (ha, ha);         // f f f f
  v4f f1 = _mm_unpacklo_ps (f, one);    // f 1 f 1
  v4f tx = load4f (T);                  // t0  t1 t1 inf
  v4f lo = _mm_movelh_ps (tx, tx);      // t0  t1 t0  t1
  v4f hi = _mm_movehl_ps (tx, tx);      // t1 inf t1 inf
  v4f sel = _mm_and_ps (_mm_cmpge_ps (tttt, lo), _mm_cmplt_ps (tttt, hi));
  v4f val = _mm_and_ps (sel, f1);       // f? 1? f? 1?
  return _mm_hadd_ps (val, val);
}