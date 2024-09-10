 bool ConvexPolygon::isInside(const Eigen::Vector3d& p)
 {
   Eigen::Vector3d A0 = vertices_[0];
   Eigen::Vector3d B0 = vertices_[0 + 1];
   Eigen::Vector3d direction0 = (B0 - A0).normalized();
   Eigen::Vector3d direction20 = (p - A0).normalized();
   bool direction_way = direction0.cross(direction20).dot(normal_) > 0;
   for (size_t i = 1; i < vertices_.size() - 1; i++) {
     Eigen::Vector3d A = vertices_[i];
     Eigen::Vector3d B = vertices_[i + 1];
     Eigen::Vector3d direction = (B - A).normalized();
     Eigen::Vector3d direction2 = (p - A).normalized();
     if (direction_way) {
       if (direction.cross(direction2).dot(normal_) >= 0) {
         continue;
       }
       else {
         return false;
       }
     }
     else {
       if (direction.cross(direction2).dot(normal_) <= 0) {
         continue;
       }
       else {
         return false;
       }
     }
   }
   return true;
 }