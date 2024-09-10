 Quaternion(Vector3D v1, Vector3D v2) {
     const double k = v2.norm() / v1.norm();
     const Vector3D d1 = v1.direction();
     const Vector3D d2 = v2.direction();
     if ( (d1 + d2).norm() < PRECISION ) {
         Vector3D n;
         srand( (unsigned int) time(0));
         do {
             double x = (double) rand() / RAND_MAX;
             double y = (double) rand() / RAND_MAX;
             double z = (double) rand() / RAND_MAX;
             Vector3D v = Vector3D(x, y, z);
             n = v - v1.direction()*(v*v1)/v1.norm();
         } while (n.norm() < PRECISION );
         init( 0.0, n.direction() );
     } else if ( (d1 - d2).norm() < PRECISION ) {
         init( 1.0, Vector3D(0.0, 0.0, 0.0) );
     } else {
         double phi = acos( v1.direction()*v2.direction() );
         Vector3D a = v1.cross(v2).direction();
         assert(a.norm() > PRECISION);
         double w = cos(phi/2) * sqrt(k);
         Vector3D u = a * sin(phi/2) * sqrt(k);
         init(w, u);
     }
 }