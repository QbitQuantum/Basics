/* Update the normal vector in vertex b of triangle (a,b,c).
 * This corresponds to adding the normalized ab * bc vector product,
 * multiplied by the angle in b */
void vertex::update_norm(const vertex &a, const vertex &b, const vertex &c) {
  vertex v1, v2, p;
  float norm, surf, angle;
  v1 = b-a;
  v2 = c-b;
  p = v1*v2;
  surf = sqrtf((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)
      * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z));
  norm = sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
  if (norm > surf)
    angle = M_PI / 2;
  else
    angle = asinf(norm / surf);
  angle /= norm;
  x += p.x * angle;
  y += p.y * angle;
  z += p.z * angle;
}