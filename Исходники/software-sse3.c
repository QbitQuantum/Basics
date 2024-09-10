int main(){
  typedef union{
    __m128 m128;
    float flt[4];
  } m128f;
  __m128 x = {1.0,2.0,3.0,4.0};
  __m128 y = {10.0,20.0,30.0,40.0};
  m128f s,h;
  s.m128=haddps(x,y);
  h.m128=_mm_hadd_ps(x,y);
  printf("Software hadd: %f %f %f %f\n",s.flt[0],s.flt[1],s.flt[2],s.flt[3]);
  printf("Hardware hadd: %f %f %f %f\n",h.flt[0],h.flt[1],h.flt[2],h.flt[3]);
  return;
}