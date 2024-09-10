void init_sse_data()
{
#ifdef HAVE_SSE
  if (A_s == 0) {
    posix_memalign ((void**)&A_s, 16, (sizeof(__m128)*12));
    A_s[0]  = _mm_setr_ps ( 1.0/6.0, -3.0/6.0,  3.0/6.0, -1.0/6.0 );
    A_s[0]  = _mm_setr_ps ( 1.0/6.0, -3.0/6.0,  3.0/6.0, -1.0/6.0 );	  
    A_s[1]  = _mm_setr_ps ( 4.0/6.0,  0.0/6.0, -6.0/6.0,  3.0/6.0 );	  
    A_s[2]  = _mm_setr_ps ( 1.0/6.0,  3.0/6.0,  3.0/6.0, -3.0/6.0 );	  
    A_s[3]  = _mm_setr_ps ( 0.0/6.0,  0.0/6.0,  0.0/6.0,  1.0/6.0 );	  
    A_s[4]  = _mm_setr_ps ( -0.5,  1.0, -0.5, 0.0  );		  
    A_s[5]  = _mm_setr_ps (  0.0, -2.0,  1.5, 0.0  );		  
    A_s[6]  = _mm_setr_ps (  0.5,  1.0, -1.5, 0.0  );		  
    A_s[7]  = _mm_setr_ps (  0.0,  0.0,  0.5, 0.0  );		  
    A_s[8]  = _mm_setr_ps (  1.0, -1.0,  0.0, 0.0  );		  
    A_s[9]  = _mm_setr_ps ( -2.0,  3.0,  0.0, 0.0  );		  
    A_s[10] = _mm_setr_ps (  1.0, -3.0,  0.0, 0.0  );		  
    A_s[11] = _mm_setr_ps (  0.0,  1.0,  0.0, 0.0  );                  
  }
                 
#endif
#ifdef HAVE_SSE2
  if (A_d == 0) {
    posix_memalign ((void**)&A_d, 16, (sizeof(__m128d)*24));
    A_d[ 0] = _mm_setr_pd (  3.0/6.0, -1.0/6.0 );	   
    A_d[ 1] = _mm_setr_pd (  1.0/6.0, -3.0/6.0 );	   
    A_d[ 2] = _mm_setr_pd ( -6.0/6.0,  3.0/6.0 );	   
    A_d[ 3] = _mm_setr_pd (  4.0/6.0,  0.0/6.0 );	   
    A_d[ 4] = _mm_setr_pd (  3.0/6.0, -3.0/6.0 );	   
    A_d[ 5] = _mm_setr_pd (  1.0/6.0,  3.0/6.0 );	   
    A_d[ 6] = _mm_setr_pd (  0.0/6.0,  1.0/6.0 );	   
    A_d[ 7] = _mm_setr_pd (  0.0/6.0,  0.0/6.0 );	   
    A_d[ 8] = _mm_setr_pd ( -0.5,  0.0 );		   
    A_d[ 9] = _mm_setr_pd ( -0.5,  1.0 );		   
    A_d[10] = _mm_setr_pd (  1.5,  0.0 );		   
    A_d[11] = _mm_setr_pd (  0.0, -2.0 );		   
    A_d[12] = _mm_setr_pd ( -1.5,  0.0 );		   
    A_d[13] = _mm_setr_pd (  0.5,  1.0 );		   
    A_d[14] = _mm_setr_pd (  0.5,  0.0 );		   
    A_d[15] = _mm_setr_pd (  0.0,  0.0 );		   
    A_d[16] = _mm_setr_pd (  0.0,  0.0 );		   
    A_d[17] = _mm_setr_pd (  1.0, -1.0 );		   
    A_d[18] = _mm_setr_pd (  0.0,  0.0 );		   
    A_d[19] = _mm_setr_pd ( -2.0,  3.0 );		   
    A_d[20] = _mm_setr_pd (  0.0,  0.0 );		   
    A_d[21] = _mm_setr_pd (  1.0, -3.0 );		   
    A_d[22] = _mm_setr_pd (  0.0,  0.0 );		   
    A_d[23] = _mm_setr_pd (  0.0,  1.0 );   
  }                
#endif
}