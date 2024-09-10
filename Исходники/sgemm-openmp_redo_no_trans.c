void sgemm( int m_a, int n_a, float *A, float *B, float *C ) {

  int mpad = m_a%STEPM ? (m_a/STEPM+1)*STEPM:m_a;
  int npad = n_a%STEPN ? (n_a/STEPN+1)*STEPN:n_a;
  int mbackup = m_a;

  float* Apad=malloc(mpad*npad*sizeof(float));
  transposeA(n_a, m_a, npad, mpad, Apad, A);
  A=Apad;
  float* Bpad=malloc(npad*mpad*sizeof(float));
  transposeB(n_a, m_a, npad, mpad, Bpad, B);
  B=Bpad;            
 
  float* Cpad = malloc(mpad*mpad*sizeof(float));
  float* backup = C;
  C = Cpad;

  m_a = mpad;
  n_a = npad;

#pragma omp parallel 
  {
    //    __m128 c0,a1, c1, a2, c2, a3, c3, a4, c4;
    __m128 a1, a2, a3, a4, c0;
    __m128 c11, c12, c13, c14;
    __m128 c21, c22, c23, c24;
    __m128 c31, c32, c33, c34;
    __m128 c41, c42, c43, c44;

    __m128 b1, b2, b3, b4;
    float temp0,temp1,temp2,temp3,temp4, temp5, temp6, temp7, temp8;
    int ii=0;
    int jj=0;
    int kk=0;

    int kkma=0;
    int jjna=0;
    int jjma=0; 
    int iina=0;

#pragma omp for
    for( int j = 0; j < m_a; j+=4 ) {
      jj=j;

      jjma=jj*m_a;
      jjna=jj*n_a;

      for( int i = 0; i < m_a; i+=4 ) {
	ii=i;

	iina=ii*n_a;

	c31=c32=c33=c34=c41=c42=c43=c44=c11=c12=c13=c14=c21=c22=c23=c24 = _mm_setzero_ps();
 
	for( int k = 0; k < n_a; k+=4 ) {
	  float* tempA=A+k+iina;
	  float* tempB=B+k+jjna;

	  b1 = _mm_loadu_ps(tempB);
	  b2 = _mm_loadu_ps(tempB+n_a);
	  b3 = _mm_loadu_ps(tempB+2*n_a);
	  b4 = _mm_loadu_ps(tempB+3*n_a);
	  /////////////////////////////////////////
	  a1 = _mm_loadu_ps(tempA);
	  a2 = _mm_loadu_ps(tempA+n_a);
	  a3 = _mm_loadu_ps(tempA+n_a*2);
	  a4 = _mm_loadu_ps(tempA+n_a*3);

	  c11=_mm_add_ps(c11,  _mm_mul_ps(a1, b1));
	  c21 = _mm_add_ps(c21, _mm_mul_ps(a2, b1));

	  c12 = _mm_add_ps(c12, _mm_mul_ps(a1, b2));
	  c22 = _mm_add_ps(c22, _mm_mul_ps(a2, b2));

	  c13= _mm_add_ps(c13,  _mm_mul_ps(a1, b3));
	  c23 = _mm_add_ps(c23, _mm_mul_ps(a2, b3));

	  c14 = _mm_add_ps(c14, _mm_mul_ps(a1, b4));
	  c24 = _mm_add_ps(c24, _mm_mul_ps(a2, b4));

	  c31=_mm_add_ps(c31,  _mm_mul_ps(a3, b1));
	  c41 = _mm_add_ps(c41, _mm_mul_ps(a4, b1));

	  c32 = _mm_add_ps(c32, _mm_mul_ps(a3, b2));
	  c42 = _mm_add_ps(c42, _mm_mul_ps(a4, b2));

	  c33= _mm_add_ps(c33,  _mm_mul_ps(a3, b3));
	  c43 = _mm_add_ps(c43, _mm_mul_ps(a4, b3));

	  c34 = _mm_add_ps(c34, _mm_mul_ps(a3, b4));
	  c44 = _mm_add_ps(c44, _mm_mul_ps(a4, b4));
	}

	c0=  _mm_hadd_ps(c11,c11);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c12,c12);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+m_a] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c13,c13);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+m_a*2] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c14,c14);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+m_a*3] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c21,c21);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+1] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c22,c22);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+1+m_a] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c23,c23);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+1+m_a*2] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c24,c24);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+1+m_a*3] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c31,c31);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+2] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c32,c32);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+2+m_a] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c33,c33);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+2+m_a*2] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c34,c34);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+2+m_a*3] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c41,c41);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+3] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c42,c42);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+3+m_a] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c43,c43);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+3+m_a*2] = _mm_cvtss_f32(c0);

	c0=  _mm_hadd_ps(c44,c44);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma+3+m_a*3] = _mm_cvtss_f32(c0);
	/*
	c0=  _mm_hadd_ps(c11,c11);
	c0=  _mm_hadd_ps(c0,c0); 
	C[ii+jjma] = _mm_cvtss_f32(c0);

	c11=  _mm_hadd_ps(c12,c12);
	c11=  _mm_hadd_ps(c11,c11);
	C[ii+jjma+m_a]= _mm_cvtss_f32(c11); 

	c12=  _mm_hadd_ps(c13,c13);
	c12=  _mm_hadd_ps(c12,c12);   
	C[ii+jjma+m_a*2]=_mm_cvtss_f32(c12);

	c13=  _mm_hadd_ps(c14,c14);
	c13=  _mm_hadd_ps(c13,c13);   
	C[ii+jjma+m_a*3]= _mm_cvtss_f32(c13);

	c14=  _mm_hadd_ps(c21,c21);
	c14=  _mm_hadd_ps(c14,c14); 
	C[ii+jjma+1] = _mm_cvtss_f32(c14);

	c21=  _mm_hadd_ps(c22,c22);
	c21=  _mm_hadd_ps(c21,c21);
	C[ii+jjma+m_a+1] = _mm_cvtss_f32(c21); 

	c22=  _mm_hadd_ps(c23,c23);
	c22=  _mm_hadd_ps(c22,c22);   
	C[ii+jjma+2*m_a+1]=_mm_cvtss_f32(c22);

	c23=  _mm_hadd_ps(c24,c24);
	c23=  _mm_hadd_ps(c23,c23);   
	C[ii+jjma+3*m_a+1]= _mm_cvtss_f32(c23);
	*/
      }
    } 
  }

  move(mbackup, mpad, C, backup);
  free(A);
  free(B);
  free(C);
}             