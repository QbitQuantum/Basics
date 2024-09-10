 float g1(const Vector& v, const Vector& m) const {
   if(dot(v, m) * Bsdf::cos_theta(v) <= 0.f) {
     return 0.f;
   }
   float a = Bsdf::cos_theta(v) / (this->alpha_b * Bsdf::sin_theta(v));
   return 2.f / (1.f + erf(a) + exp(-square(a)) / (a * SQRT_PI));
 }