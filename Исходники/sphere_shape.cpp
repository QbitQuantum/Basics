 float SphereShape::point_eye_pdf(const Point& eye, const Vector& w) const {
   float dist_squared = length_squared(eye.v);
   if(dist_squared - this->radius * this->radius < 1e-3) {
     return Shape::point_eye_pdf(eye, w);
   }
   float dist = sqrt(dist_squared);
   float inv_dist = 1.f / dist;
   float cos_theta_max = sqrt(dist_squared - this->radius * this->radius) * inv_dist;
   return uniform_cone_pdf(cos_theta_max);
 }