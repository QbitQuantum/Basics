////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
  v1 = v[1]->position - v[0]->position;
  v2 = v[2]->position - v[0]->position;
  
  plane.normal = v1.crossProduct(v2).unit();

  float d = plane.normal.dot(v1);// * -1.0f);
  float t = d / plane.normal.dot(plane.normal);

  Point3D PoP = plane.normal * t;
  plane.distance = sqrt(PoP.dot(PoP));
}