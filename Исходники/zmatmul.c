inline void zmatmul(float *ain, float *bin, float *cout) {
#ifdef __MIC__
  __m512 a,b,c;
  __m512 a0,a1,a2,a3;
  __m512 b0,b1,b2,b3;

  __m512i pa0={ 0, 0, 2, 2, 0, 0, 2, 2, 8, 8,10,10, 8, 8,10,10};
  __m512i pa1={ 1, 1, 3, 3, 1, 1, 3, 3, 9, 9,11,11, 9, 9,11,11};
  __m512i pa2={ 4, 4, 6, 6, 4, 4, 6, 6,12,12,14,14,12,12,14,14};
  __m512i pa3={ 5, 5, 7, 7, 5, 5, 7, 7,13,13,15,15,13,13,15,15};

  __m512i pb0={ 0, 1, 0, 1, 4, 5, 4, 5, 0, 1, 0, 1, 4, 5, 4, 5};
  __m512i pb1={ 2, 3, 2, 3, 6, 7, 6, 7, 2, 3, 2, 3, 6, 7, 6, 7};
  __m512i pb2={ 8, 9, 8, 9,12,13,12,13, 8, 9, 8, 9,12,13,12,13};
  __m512i pb3={10,11,10,11,14,15,14,15,10,11,10,11,14,15,14,15};

  a=_mm512_load_ps(ain);
  b=_mm512_load_ps(bin);
  c=_mm512_load_ps(cout);

  a0=_mm512_castsi512_ps(_mm512_permutevar_epi32(pa0,_mm512_castps_si512(a)));
  a1=_mm512_castsi512_ps(_mm512_permutevar_epi32(pa1,_mm512_castps_si512(a)));
  a2=_mm512_castsi512_ps(_mm512_permutevar_epi32(pa2,_mm512_castps_si512(a)));
  a3=_mm512_castsi512_ps(_mm512_permutevar_epi32(pa3,_mm512_castps_si512(a)));

  b0=_mm512_castsi512_ps(_mm512_permutevar_epi32(pb0,_mm512_castps_si512(b)));
  b1=_mm512_castsi512_ps(_mm512_permutevar_epi32(pb1,_mm512_castps_si512(b)));
  b2=_mm512_castsi512_ps(_mm512_permutevar_epi32(pb2,_mm512_castps_si512(b)));
  b3=_mm512_castsi512_ps(_mm512_permutevar_epi32(pb3,_mm512_castps_si512(b)));

  c=_mm512_fmadd_ps(a0,b0,c);
  c=_mm512_fmadd_ps(a1,b1,c);
  c=_mm512_fmadd_ps(a2,b2,c);
  c=_mm512_fmadd_ps(a3,b3,c);

  _mm512_store_ps(cout,c);
#else
  cout[0] +=ain[0] *bin[0]+ain[1] *bin[2]+ain[4] *bin[8] +ain[5] *bin[10];
  cout[1] +=ain[0] *bin[1]+ain[1] *bin[3]+ain[4] *bin[9] +ain[5] *bin[11];
  cout[2] +=ain[2] *bin[0]+ain[3] *bin[2]+ain[6] *bin[8] +ain[7] *bin[10];
  cout[3] +=ain[2] *bin[1]+ain[3] *bin[3]+ain[6] *bin[9] +ain[7] *bin[11];
  cout[4] +=ain[0] *bin[4]+ain[1] *bin[6]+ain[4] *bin[12]+ain[5] *bin[14];
  cout[5] +=ain[0] *bin[5]+ain[1] *bin[7]+ain[4] *bin[13]+ain[5] *bin[15];
  cout[6] +=ain[2] *bin[4]+ain[3] *bin[6]+ain[6] *bin[12]+ain[7] *bin[14];
  cout[7] +=ain[2] *bin[5]+ain[3] *bin[7]+ain[6] *bin[13]+ain[7] *bin[15];
  cout[8] +=ain[8] *bin[0]+ain[9] *bin[2]+ain[12]*bin[8] +ain[13]*bin[10];
  cout[9] +=ain[8] *bin[1]+ain[9] *bin[3]+ain[12]*bin[9] +ain[13]*bin[11];
  cout[10]+=ain[10]*bin[0]+ain[11]*bin[2]+ain[14]*bin[8] +ain[15]*bin[10];
  cout[11]+=ain[10]*bin[1]+ain[11]*bin[3]+ain[14]*bin[9] +ain[15]*bin[11];
  cout[12]+=ain[8] *bin[4]+ain[9] *bin[6]+ain[12]*bin[12]+ain[13]*bin[14];
  cout[13]+=ain[8] *bin[5]+ain[9] *bin[7]+ain[12]*bin[13]+ain[13]*bin[15];
  cout[14]+=ain[10]*bin[4]+ain[11]*bin[6]+ain[14]*bin[12]+ain[15]*bin[14];
  cout[15]+=ain[10]*bin[5]+ain[11]*bin[7]+ain[14]*bin[13]+ain[15]*bin[15];
#endif

}