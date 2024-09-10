ld cal(ld x){
  ld res = x * W * L;
  for(int i = 0; i < (n); ++i){
    ld v = calcu(r[i], x);
    ld vball = 4 * (ld)(1.0) / 3 * (2 * acosl((ld)0)) * r[i] * r[i] * r[i];
    if(v >= vball * w[i])
      res -= vball * w[i];
    else
      res -= v;
  }
  return res;
}