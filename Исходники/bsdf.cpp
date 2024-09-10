Spectrum MirrorBSDF::sample_f(const Vector3D& wo, Vector3D* wi, float* pdf) {

  // TODO Part 5:
  // Implement MirrorBSDF
  reflect(wo, wi);
  double cosine = abs_cos_theta(*wi);
  Spectrum result = reflectance/cosine;
  *pdf = 1;
  return result;
}