void PhotonMapping::TracePhoton(const Vec3f &position, const Vec3f &direction, 
				const Vec3f &energy, int iter) {
  
  if(iter>args->num_bounces){
    return;
  }

  Hit h = Hit();
  Ray R = Ray(position, direction);
  bool intersect = raytracer->CastRay(R, h, false);
  if(!intersect){
    return;
  }
  Material *m = h.getMaterial();
  Vec3f normal = h.getNormal();
  Vec3f point = R.pointAtParameter(h.getT());
  Vec3f opDirec = direction;
  opDirec.Negate();
  opDirec.Normalize();
  Vec3f diffuse = m->getDiffuseColor(), reflec = m->getReflectiveColor();
  double diffuseAnswer = diffuse.x()+diffuse.y()+diffuse.z();
  double reflecAnswer = reflec.x()+reflec.y()+reflec.z();
  double total = reflecAnswer+diffuseAnswer;
  diffuseAnswer /= total;
  reflecAnswer /= total;
  double seed = GLOBAL_mtrand.rand();
  if(seed <= diffuseAnswer && seed >= 0){
    Vec3f newEnergy = energy * diffuse;
    Vec3f newPosition = point;
    Vec3f newDirection = Vec3f(GLOBAL_mtrand.rand(),GLOBAL_mtrand.rand(),GLOBAL_mtrand.rand());
    newDirection.Normalize();
    Photon answer = Photon(point,opDirec,newEnergy,iter+1);
    kdtree->AddPhoton(answer);
    TracePhoton(newPosition, newDirection, newEnergy, iter+1);
  }
  else if(seed>diffuseAnswer && seed <= 1){
    Vec3f newEnergy = energy * reflec;
    Vec3f newPosition = point;
    Vec3f newDirection = direction - 2 * direction.Dot3(normal) * normal;
    Photon answer = Photon(point,opDirec,newEnergy,iter+1);
    kdtree->AddPhoton(answer);
    TracePhoton(newPosition, newDirection, newEnergy, iter+1);
  }
  // ==============================================
  // ASSIGNMENT: IMPLEMENT RECURSIVE PHOTON TRACING
  // ==============================================

  // Trace the photon through the scene.  At each diffuse or
  // reflective bounce, store the photon in the kd tree.

  // One optimization is to *not* store the first bounce, since that
  // direct light can be efficiently computed using classic ray
  // tracing.



}