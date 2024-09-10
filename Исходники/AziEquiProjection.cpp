 static Vect3 equator_map(const Vect3& ref, const Vect3& p) {
   Vect3 xmult = ref.Hat();
   Vect3 ymult = vect3_orthog_toy(ref).Hat();
   Vect3 zmult = ref.cross(vect3_orthog_toy(ref)).Hat();
   return Vect3(xmult.dot(p), ymult.dot(p), zmult.dot(p));
 }