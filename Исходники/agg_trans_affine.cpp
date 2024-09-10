//------------------------------------------------------------------------
const trans_affine& trans_affine::parl_to_parl(const double* src,
                                               const double* dst) {
  sx = src[2] - src[0];
  shy = src[3] - src[1];
  shx = src[4] - src[0];
  sy = src[5] - src[1];
  tx = src[0];
  ty = src[1];
  invert();
  multiply(trans_affine(dst[2] - dst[0], dst[3] - dst[1], dst[4] - dst[0],
                        dst[5] - dst[1], dst[0], dst[1]));
  return *this;
}