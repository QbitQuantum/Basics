/* A vectorized version of the Voigt function using X86 SSE instructions */
void my_voigt(const float *damping, const float *frequency_offset, float *voigt_value, int N)   
{                                                                   
    // coefficients of the rational approximation formula
    // to the complementary error function
    const __m128 A0 = _mm_set1_ps(122.607931777104326f);
    const __m128 A1 = _mm_set1_ps(214.382388694706425f);
    const __m128 A2 = _mm_set1_ps(181.928533092181549f);
    const __m128 A3 = _mm_set1_ps(93.155580458138441f);
    const __m128 A4 = _mm_set1_ps(30.180142196210589f);
    const __m128 A5 = _mm_set1_ps(5.912626209773153f);
    const __m128 A6 = _mm_set1_ps(0.564189583562615f);
    const __m128 B0 = _mm_set1_ps(122.60793177387535f);
    const __m128 B1 = _mm_set1_ps(352.730625110963558f);
    const __m128 B2 = _mm_set1_ps(457.334478783897737f);
    const __m128 B3 = _mm_set1_ps(348.703917719495792f);
    const __m128 B4 = _mm_set1_ps(170.354001821091472f);
    const __m128 B5 = _mm_set1_ps(53.992906912940207f);
    const __m128 B6 = _mm_set1_ps(10.479857114260399f);

    __m128 ivsigno;
    __m128 V;
    __m128 Z1_real;
    __m128 Z1_imag;
    __m128 Z2_real;
    __m128 Z2_imag;
    __m128 Z3_real;
    __m128 Z3_imag;
    __m128 Z4_real;
    __m128 Z4_imag;
    __m128 Z5_real;
    __m128 Z5_imag;
    __m128 Z6_real;
    __m128 Z6_imag;
    __m128 ZZ1_real;
    __m128 ZZ1_imag;
    __m128 ZZ2_real;
    __m128 ZZ2_imag;
    __m128 ZZ3_real;
    __m128 ZZ3_imag;
    __m128 ZZ4_real;
    __m128 ZZ4_imag;
    __m128 ZZ5_real;
    __m128 ZZ5_imag;
    __m128 ZZ6_real;
    __m128 ZZ6_imag;
    __m128 ZZ7_real;
    __m128 ZZ7_imag;
    __m128 division_factor;
    __m128 ZZZ_real;
    __m128 damp;
    __m128 offs;
    __m128 vval;
    __m128 one = _mm_set1_ps(1.0f); 
    __m128 zero = _mm_set1_ps(0.0f);
    __m128 mone = _mm_set1_ps(-1.0f);
    __m128 half = _mm_set1_ps(-0.5f);
    __m128 mask;

    float *stmp = (float *) _mm_malloc(4*sizeof(float), 16);

    int i;
    for(i=0; i<N; i+=VECLEN){
        _mm_prefetch((const char *)&damping[i+64], _MM_HINT_T0);
        _mm_prefetch((const char *)&frequency_offset[i+64], _MM_HINT_T0);
        damp = _mm_load_ps(&damping[i]);
        offs = _mm_load_ps(&frequency_offset[i]);
        mask = _mm_cmplt_ps(offs, zero);
        ivsigno = _mm_add_ps(_mm_and_ps(mask,mone),_mm_andnot_ps(mask,one));
        V = _mm_mul_ps(ivsigno, offs);       

        Z1_real = _mm_add_ps(_mm_mul_ps(A6, damp), A5);
        Z1_imag = _mm_mul_ps(A6, V);
        Z2_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(Z1_real, damp), _mm_mul_ps(Z1_imag, V)), A4);
        Z2_imag = _mm_add_ps(_mm_mul_ps(Z1_real, V), _mm_mul_ps(Z1_imag, damp));
        Z3_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(Z2_real, damp), _mm_mul_ps(Z2_imag, V)), A3);
        Z3_imag = _mm_add_ps(_mm_mul_ps(Z2_real, V), _mm_mul_ps(Z2_imag, damp));
        Z4_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(Z3_real, damp), _mm_mul_ps(Z3_imag, V)), A2);
        Z4_imag = _mm_add_ps(_mm_mul_ps(Z3_real, V), _mm_mul_ps(Z3_imag, damp));
        Z5_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(Z4_real, damp), _mm_mul_ps(Z4_imag, V)), A1);
        Z5_imag = _mm_add_ps(_mm_mul_ps(Z4_real, V), _mm_mul_ps(Z4_imag, damp));
        Z6_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(Z5_real, damp), _mm_mul_ps(Z5_imag, V)), A0);
        Z6_imag = _mm_add_ps(_mm_mul_ps(Z5_real, V), _mm_mul_ps(Z5_imag, damp));
        ZZ1_real = _mm_add_ps(damp, B6);          
        ZZ1_imag = V;                    
        ZZ2_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ1_real, damp), _mm_mul_ps(ZZ1_imag, V)), B5); 
        ZZ2_imag = _mm_add_ps(_mm_mul_ps(ZZ1_real, V), _mm_mul_ps(ZZ1_imag, damp)); 
        ZZ3_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ2_real, damp), _mm_mul_ps(ZZ2_imag, V)), B4); 
        ZZ3_imag = _mm_add_ps(_mm_mul_ps(ZZ2_real, V), _mm_mul_ps(ZZ2_imag, damp)); 
        ZZ4_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ3_real, damp), _mm_mul_ps(ZZ3_imag, V)), B3); 
        ZZ4_imag = _mm_add_ps(_mm_mul_ps(ZZ3_real, V), _mm_mul_ps(ZZ3_imag, damp)); 
        ZZ5_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ4_real, damp), _mm_mul_ps(ZZ4_imag, V)), B2); 
        ZZ5_imag = _mm_add_ps(_mm_mul_ps(ZZ4_real, V), _mm_mul_ps(ZZ4_imag, damp)); 
        ZZ6_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ5_real, damp), _mm_mul_ps(ZZ5_imag, V)), B1); 
        ZZ6_imag = _mm_add_ps(_mm_mul_ps(ZZ5_real, V), _mm_mul_ps(ZZ5_imag, damp)); 
        ZZ7_real = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(ZZ6_real, damp), _mm_mul_ps(ZZ6_imag, V)), B0); 
        ZZ7_imag = _mm_add_ps(_mm_mul_ps(ZZ6_real, V), _mm_mul_ps(ZZ6_imag, damp)); 
        division_factor = _mm_div_ps(one, _mm_add_ps(_mm_mul_ps(ZZ7_real, ZZ7_real), _mm_mul_ps(ZZ7_imag, ZZ7_imag)));
        ZZZ_real = _mm_mul_ps((_mm_add_ps(_mm_mul_ps(Z6_real, ZZ7_real), _mm_mul_ps(Z6_imag, ZZ7_imag))), division_factor); 

        _mm_stream_ps(&voigt_value[i], ZZZ_real);
    }
    _mm_free(stmp);
}