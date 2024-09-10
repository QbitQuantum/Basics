SMetric3 interpolation (const SMetric3 &m1,
                        const SMetric3 &m2,
                        const SMetric3 &m3,
                        const SMetric3 &m4,
                        const double u,
                        const double v,
                        const double w)
{
  SMetric3 im1 = m1.invert();
  SMetric3 im2 = m2.invert();
  SMetric3 im3 = m3.invert();
  SMetric3 im4 = m4.invert();
  im1 *= (1.-u-v-w);
  im2 *= u;
  im3 *= v;
  im4 *= w;
  im1 += im2;
  im1 += im3;
  im1 += im4;
  return im1.invert();
}