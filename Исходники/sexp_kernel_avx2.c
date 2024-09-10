void KERNEL_NAME(VMLLONG n, VML_FLOAT * a, VML_FLOAT * b, VML_FLOAT * y, VML_FLOAT * z, VML_FLOAT * other_params) {
  VMLLONG i=0;
  VMLLONG loop_count=(n) >> 5;
  VMLLONG remain_count=(n) & 0x1f;

  while(loop_count>0){
    __m256 av0=_mm256_loadu_ps(a);
    __m256 av1=_mm256_loadu_ps(a+8);
    __m256 av2=_mm256_loadu_ps(a+16);
    __m256 av3=_mm256_loadu_ps(a+24);


    __m256 yv0=exp256_ps(av0);
    __m256 yv1=exp256_ps(av1);
    __m256 yv2=exp256_ps(av2);
    __m256 yv3=exp256_ps(av3);

    _mm256_storeu_ps(y, yv0);
    _mm256_storeu_ps(y+8, yv1);
    _mm256_storeu_ps(y+16, yv2);
    _mm256_storeu_ps(y+24, yv3);

    a+=32;
    b+=32;
    y+=32;
    loop_count--;
  }

  for(i=0; i<n; i++){
    y[i]=expf(a[i]);
  }
}