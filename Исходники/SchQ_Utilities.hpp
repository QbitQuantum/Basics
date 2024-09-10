 // Returns the angle between two Vecs
 double angle_between(Vec3D<Type> v){
     return(atan(dot_product(v)/(magnitude() * v.magnitude())));
 }