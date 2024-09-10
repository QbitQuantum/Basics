bool UVSphere::isIntersect(const Ray& r, float tmin, float tmax, float time)const{
  Vec temp = r.origin() - center;
  float a = r.direction().dot(r.direction());
  float b = 2 * r.direction().dot(temp);
  float c = temp.dot(temp) - radius * radius;

  float discriminant = b*b - 4*a*c;
  if(discriminant > 0){
    discriminant = sqrt(discriminant);
    float t = (-b -discriminant) /(2*a);
    if(t < tmin) t = (-b + discriminant) / (2*a);
    if(t < tmin || t > tmax) return false;
    
    return true;
  }
  return false;
}