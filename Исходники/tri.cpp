bool Tri::intersect(Ray& _ray, float* thit, Intersection* in) {
  Ray ray = _ray.transform(inverseTransform);
  if (!intersectP(ray)) { return false; }
  if (*thit < t) { return false; }

  p = ray.getPos() + ray.getDir() * t;
  w = p - a;
  vCrossW = glm::cross(v, w);
  uCrossW = glm::cross(u, w);

  if (glm::dot(vCrossW, vCrossU) < 0) { return false; }
  if (glm::dot(uCrossW, uCrossV) < 0) { return false; }

  beta = glm::length(vCrossW)/denom;
  gamma = glm::length(uCrossW)/denom;
  alpha = 1 - beta - gamma;

  if (!(beta <= 1 && gamma <= 1 && beta + gamma <= 1)) { return false; }

  *thit = t;
  in->localGeo.pos = mat4TimesVec3(getTransform(),
    (ray.getPos() + t * ray.getDir()), 1.0);
  in->localGeo.normal = getNormal();
  //shift position slightly towards normal (epsilon shift)
  in->localGeo.pos = in->localGeo.pos + in->localGeo.normal * epsilon;
  in->primitive = this;

  return true;
}