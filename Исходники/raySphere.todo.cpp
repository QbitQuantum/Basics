////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  
  // ray from position to sphere center  
  Point3D L = center - ray.position;
  float LdL = sqrt(L.dot(L));

  float t_ca = L.dot(ray.direction); 

  float dSq = pow(LdL, 2) - pow(t_ca, 2);
  float rSq = pow(radius, 2);

  if (dSq > rSq){
    return -1;
  }
  else{
    float t_hc = sqrt(rSq - dSq);    
    float dist = t_ca - t_hc;
    if(mx < 0 || dist < mx){

      Point3D coord = ray(dist);

      iInfo.material = material;
      iInfo.normal = (coord - center).unit();        
      iInfo.iCoordinate = coord;
    }
    return dist;
  }
}