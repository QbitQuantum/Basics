 // http://tavianator.com/2011/05/fast-branchless-raybounding-box-intersections/
 bool rayAabbIntersection(const Ray& ray, const AABB& aabb)
 {
     Real3 n_inv = Real3(1.0) / ray.direction();
     
     double tx1 = (aabb.min().x - ray.origin().x)*n_inv.x;
     double tx2 = (aabb.max().x - ray.origin().x)*n_inv.x;
     
     double tmin = glm::min(tx1, tx2);
     double tmax = glm::max(tx1, tx2);
     
     double ty1 = (aabb.min().y - ray.origin().y)*n_inv.y;
     double ty2 = (aabb.max().y - ray.origin().y)*n_inv.y;
     
     tmin = glm::max(tmin, glm::min(ty1, ty2));
     tmax = glm::min(tmax, glm::max(ty1, ty2));
     
     double tz1 = (aabb.min().z - ray.origin().z)*n_inv.z;
     double tz2 = (aabb.max().z - ray.origin().z)*n_inv.z;
     
     tmin = glm::max(tmin, glm::min(tz1, tz2));
     tmax = glm::min(tmax, glm::max(tz1, tz2));
     
     return tmax >= glm::max(tmin, 0.0);
 }