 Vector3d latticeVectorHelper( Vector3d difference_along_normal, Vector3d v_dir ){
   double length = difference_along_normal.length() / (difference_along_normal.normalize().dot(v_dir));
   return v_dir * length;
 }