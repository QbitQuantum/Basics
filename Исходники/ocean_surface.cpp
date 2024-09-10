 void operator()(Particle* p, const vec2& position, float& t1, float& t2){
   const vec2 r = position - p->position;
   const float norm2 = dot(r,r);
   if (norm2 < kernelRadius2) {
     const float tmp = cst * pow(kernelRadius2-norm2,3); // POLY 6
     // const float tmp = cst * pow(kernelRadius-sqrt(norm2),3);
     t1 += p->massDensity * tmp;
     t2 += tmp;
   }
 }