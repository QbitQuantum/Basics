Hit ComplexObject::intersectMesh(Vec3Df origin, Vec3Df dest) {
  // hit is is where we keep track of hits with backfaces
  // For the moment we use noHit as a symbol
  Hit hit = noHit;

   //Material that is displayed if no material is found in Mesh
   Material errorMat = Material();
   errorMat.set_Kd(1,1,0);
   errorMat.set_Ka(1,1,0);
   errorMat.set_Ks(1,1,0);
   errorMat.set_Ns(96.7f);
   errorMat.set_illum(2);
   Material actualMat = errorMat;
    

  for (int i = 0; i < mesh.triangles.size(); i++) {
    Triangle T = mesh.triangles[i];

    //now return the actual material which is defined in the mesh
    int materialIndex = 999;
    if(mesh.triangleMaterials.size()>0){
  	materialIndex = mesh.triangleMaterials[i]; 
    }
    if(0 <= materialIndex && materialIndex < mesh.materials.size()){
   	actualMat = mesh.materials[materialIndex];
    }

    // Our implementation is based on the proposed algorithm of Dan Sunday at: http://geomalgorithms.com/a06-_intersect-2.html
    Vertex v0 = mesh.vertices[T.v[0]];
    Vertex v1 = mesh.vertices[T.v[1]];
    Vertex v2 = mesh.vertices[T.v[2]];

    // Edge vectors
    Vec3Df u = v1.p-v0.p;
    Vec3Df v = v2.p-v0.p;
    Vec3Df n = Vec3Df::crossProduct(u, v);  // Normal of the triangle

    Vec3Df w0 = origin - v0.p;
    float a = -Vec3Df::dotProduct(n, w0);
    float b = Vec3Df::dotProduct(n, dest);

    // Use this as a threshold to avoid division overflow
    if (fabs(b) < 0.0000001) {
      // ray is parallel to triangle plane (either precisely on or disjoint from plane)
      continue;
    }
    
    // Get intersection point of ray with triangle plane
    float r = a / b;
    if (r < 0.01)  // ray goes away from triangle
    {
	continue;
    }

    // intersect point of ray and plane
    Vec3Df I = origin + (r * dest);

    // Next up; triangle text; is I inside T?
    float uu, uv, vv, wu, wv, D;
    uu = Vec3Df::dotProduct(u, u);
    uv = Vec3Df::dotProduct(u, v);
    vv = Vec3Df::dotProduct(v, v);
    Vec3Df w = I - v0.p;
    wu = Vec3Df::dotProduct(w, u);
    wv = Vec3Df::dotProduct(w, v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
       continue;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
       continue;

    n.normalize();  // We can now truncate the normal to length of 1

    // If we get here I (the ray hitpoint) is in T (the triangle):
    // We check if we already found a hit before
    if (hit.isHit == 0) {
      // In that case we can just assign the current hit as the first one
      hit = Hit(1, I, n, actualMat);
    } else {
      // If so, we check whether this one is closer to the origin
      float previousDistance = (hit.hitPoint - origin).getLength();
      float currentDistance  = (I - origin).getLength();

      // Now check if it's closer
      if (currentDistance < previousDistance) {
        // If it is then we save the current hit
         hit = Hit(1, I, n, actualMat);
      } else {
        // If not we discard this hit and continue looking for one which is
        continue;
      }
    }
  }
  return hit;
}