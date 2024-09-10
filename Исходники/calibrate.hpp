void calibrate_energy(float* _x, float* _y, float* _z, float* _e, const size_t& _size){

  const size_t lenght = _size;
#if GCC_VERSION > 40701
  float *x = (float*)__builtin_assume_aligned(_x, 16);
  float *y = (float*)__builtin_assume_aligned(_y, 16);
  float *z = (float*)__builtin_assume_aligned(_z, 16);
  float *e = (float*)__builtin_assume_aligned(_e, 16);
#else
  float *x = _x;
  float *y = _y;
  float *z = _z;
  float *e = _e;
#endif

  for(size_t i = 0;i<lenght;++i){
    float r = std::sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
    float scale = p0 + p1*r + p2*r*r + p3*r*r*r + p4*r*r*r*r + p5*r*r*r*r*r ;
    scale /= (2.f*1e7/3.f);
    e[i] = (1.f-scale)*e[i];
  }
  
}