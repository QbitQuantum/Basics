INLINE P YgooSmathYPfsinh(P x) {
  INTFLO iz, ix; ix.i = (PINT)x; 
  iz.f = (float)sinh((double)ix.f);
  return (P)iz.i;
}