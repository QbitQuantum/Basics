int main(void)
{
   // std::cout<<std::endl<<" Compute inner product..."<<std::endl<<std::endl;

    // INIT VECTOR
    //double vec1    [_PBM_SIZE] __attribute__((aligned(_CBSIM_DBL_ALIGN_)));//__declspec(align(n))
    //double vec2    [_PBM_SIZE] __attribute__((aligned(_CBSIM_DBL_ALIGN_)));
     //__declspec(align(_CBSIM_DBL_ALIGN_)) double vec1    [_PBM_SIZE];
     //__declspec(align(_CBSIM_DBL_ALIGN_)) double vec2    [_PBM_SIZE];

    //double *vec1 = _aligned_malloc(_PBM_SIZE*sizeof *vec1,_CBSIM_DBL_ALIGN_);
    //double *vec2 = _aligned_malloc(_PBM_SIZE*sizeof *vec2,_CBSIM_DBL_ALIGN_);


	double *vec1 =(double *)_mm_malloc(sizeof(double)*_PBM_SIZE,32);
    double *vec2 =(double *)_mm_malloc(sizeof(double)*_PBM_SIZE,32);

    double result = 0.0;
//    tbb::tick_count t1, t2;
    int loopsToDo = 10000;
    for (int i=0 ; i < _PBM_SIZE ; i++)
    {
        vec1[i] = static_cast<double>(i)*0.01;
        vec2[i] = static_cast<double>(i)*0.01;
    }


// SERIAL ***********************************************************************************
//    t1 = tbb::tick_count::now();


    for (int z=0 ; z < loopsToDo ; z++)
    {
    //__m256d ymm0;
    //__m256d ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7;//, ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15, ymm16, ymm17, ymm18;
    //ymm0 = _mm256_setzero_pd(); // accumulator
    //double res0 = 0.0, res1 = 0.0, res2 = 0.0, res3 = 0.0;
    //__m256d acc = _mm256_setzero_pd();
    //double res[4] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0, 0.0, 0.0};
        result = 0.0;
    //double res[2] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0};
    for (int i=0 ; i < _PBM_SIZE; i+=8)
    {
/*        __m256d ymm1 = _mm256_load_pd(&vec1[i]);
        __m256d ymm2 = _mm256_load_pd(&vec2[i]);
        __m256d ymm3 = _mm256_mul_pd( ymm1, ymm2 );

        __m128d xmm1 = _mm256_extractf128_pd(ymm3,0);
        __m128d xmm2 = _mm256_extractf128_pd(ymm3,1);
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);

        _mm_store_pd(&res[0],xmm3);

        //_mm256_store_pd(&res[0],ymm12);
        result += (res[0] + res[1]);// + (res[2] + res[3]);
*/
        __assume_aligned(&vec1[0],32);
        __assume_aligned(&vec2[0],32);
       __m256d ymm1 = _mm256_load_pd(&vec1[i]);
        __m256d ymm2 = _mm256_load_pd(&vec2[i]);
        __m256d ymm3 = _mm256_mul_pd( ymm1, ymm2 );

        __m256d ymm4 = _mm256_load_pd(&vec1[i+4]);
        __m256d ymm5 = _mm256_load_pd(&vec2[i+4]);
        __m256d ymm6 = _mm256_mul_pd( ymm4, ymm5 );

        __m256d ymm7 = _mm256_add_pd( ymm3, ymm6);
        
        __m128d xmm1 = _mm256_extractf128_pd(ymm7,0);
        __m128d xmm2 = _mm256_extractf128_pd(ymm7,1);;
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);
double res[2] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0};
        _mm_store_pd(&res[0],xmm3);

        //_mm256_store_pd(&res[0],ymm12);
        result += (res[0] + res[1]);// + (res[2] + res[3]);

        //__m256d ymm0 = _mm256_add_pd( ymm0, ymm7);

/*        //__assume_aligned(&vec1[0],32);
        //__assume_aligned(&vec2[0],32);
        __m256d ymm1 = _mm256_load_pd(&vec1[i]);
        __m256d ymm2 = _mm256_load_pd(&vec2[i]);
        __m256d ymm3 = _mm256_mul_pd( ymm1, ymm2 );

        __m256d ymm4 = _mm256_load_pd(&vec1[i+4]);
        __m256d ymm5 = _mm256_load_pd(&vec2[i+4]);
        //__m256d ymm6 = _mm256_mul_pd( ymm4, ymm5 );

        //__m256d ymm7 = _mm256_add_pd( ymm3, ymm6);
        __m256d ymm6 = _mm256_fmadd_pd (ymm4,ymm5,ymm3);
        //ymm0 = _mm256_add_pd( ymm0, ymm7);


        __m128d xmm1 = _mm256_extractf128_pd(ymm6,0);
        __m128d xmm2 = _mm256_extractf128_pd(ymm6,1);;
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);

        _mm_store_pd(&res[0],xmm3);

        //_mm256_store_pd(&res[0],ymm12);
        result += (res[0] + res[1]);// + (res[2] + res[3]);

        //_mm256_store_pd(&res[0],ymm6);
        //result_SIMD_INTRINSICS += (res[0] + res[1]) + (res[2] + res[3]);
*/

//#define _VER_AVX
#ifdef _VER_AVX
        __m256d ymm1 = _mm256_load_pd(&vec1[i]);
        __m256d ymm2 = _mm256_load_pd(&vec2[i]);
        __m256d ymm3 = _mm256_mul_pd( ymm1, ymm2 );

        __m256d ymm4 = _mm256_load_pd(&vec1[i+4]);
        __m256d ymm5 = _mm256_load_pd(&vec2[i+4]);
        __m256d ymm6 = _mm256_mul_pd( ymm4, ymm5 );

        __m256d ymm7 = _mm256_load_pd(&vec1[i+8]);
        __m256d ymm8 = _mm256_load_pd(&vec2[i+8]);
        __m256d ymm9 = _mm256_mul_pd( ymm7, ymm8 );

        __m256d ymm10 = _mm256_load_pd(&vec1[i+12]);
        __m256d ymm11 = _mm256_load_pd(&vec2[i+12]);
        __m256d ymm12 = _mm256_mul_pd( ymm10, ymm11 );

        __m256d ymm13 = _mm256_add_pd( ymm3, ymm6);
        __m256d ymm14 = _mm256_add_pd( ymm9, ymm12);
        __m256d ymm15 = _mm256_add_pd( ymm13, ymm14);

        __m128d xmm1 = _mm256_extractf128_pd(ymm15,0);
        __m128d xmm2 = _mm256_extractf128_pd(ymm15,1);;
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);
        double res_SIMD_INTRINSICS[2] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0};
        _mm_store_pd(&res_SIMD_INTRINSICS[0],xmm3);

        result += (res_SIMD_INTRINSICS[0] + res_SIMD_INTRINSICS[1]);

        //ymm0 = _mm256_add_pd( ymm0, ymm13);
        //ymm0 = _mm256_add_pd( ymm0, ymm14);
#endif
//#define _VER_AVX2
#ifdef _VER_AVX2
        __m256d ymm1 = _mm256_load_pd(&vec1[i]);
        __m256d ymm2 = _mm256_load_pd(&vec1[i+4]);
        __m256d ymm3 = _mm256_load_pd(&vec1[i+8]);
        __m256d ymm4 = _mm256_load_pd(&vec1[i+12]);
        //__m256d ymm13 = _mm256_load_pd(&vec1[i+16]);
        //__m256d ymm14 = _mm256_load_pd(&vec1[i+20]);
        //__m256d ymm15 = _mm256_load_pd(&vec1[i+24]);
        //__m256d ymm16 = _mm256_load_pd(&vec1[i+28]);

        __m256d ymm5 = _mm256_load_pd(&vec2[i]);
        __m256d ymm6 = _mm256_load_pd(&vec2[i+4]);
        __m256d ymm7 = _mm256_load_pd(&vec2[i+8]);
        __m256d ymm8 = _mm256_load_pd(&vec2[i+12]);
        //__m256d ymm17 = _mm256_load_pd(&vec2[i+16]);
        //__m256d ymm18 = _mm256_load_pd(&vec2[i+20]);
        //__m256d ymm19 = _mm256_load_pd(&vec2[i+24]);
        //__m256d ymm20 = _mm256_load_pd(&vec2[i+28]);

        __m256d ymm9 = _mm256_mul_pd(ymm1,ymm5);
        __m256d ymm10 = _mm256_fmadd_pd(ymm2,ymm6,ymm9);
        //__m256d ymm11 = _mm256_mul_pd(ymm3,ymm7);
        __m256d ymm11 = _mm256_fmadd_pd(ymm3,ymm7,ymm10);
        __m256d ymm12 = _mm256_fmadd_pd(ymm4,ymm8,ymm11);
        //ymm12 = _mm256_hadd_pd(ymm10,ymm12);
        //__m256d ymm21 = _mm256_fmadd_pd(ymm13,ymm17,ymm12);
        //__m256d ymm22 = _mm256_fmadd_pd(ymm14,ymm18,ymm21);
        //__m256d ymm23 = _mm256_fmadd_pd(ymm15,ymm19,ymm22);
        //__m256d ymm24 = _mm256_fmadd_pd(ymm16,ymm20,ymm23);
        __m128d xmm1 = _mm256_extractf128_pd(ymm12,0);
        __m128d xmm2 = _mm256_extractf128_pd(ymm12,1);;
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);
        double res[2] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0};
        _mm_store_pd(&res[0],xmm3);

        //_mm256_store_pd(&res[0],ymm12);
        result += (res[0] + res[1]);// + (res[2] + res[3]);
#endif

/*        // Performing 4 dot product at one time
        ymm1  = _mm256_load_pd(&vec1[i]);    // x[0]
        ymm2  = _mm256_load_pd(&vec1[i+4]);  // x[1]
        ymm3  = _mm256_load_pd(&vec1[i+8]);  // x[2]
        ymm4  = _mm256_load_pd(&vec1[i+12]); // x[3]

        ymm5  = _mm256_load_pd(&vec2[i]);    // y[0]
        ymm6  = _mm256_load_pd(&vec2[i+4]);  // y[1]
        ymm7  = _mm256_load_pd(&vec2[i+8]);  // y[2]
        ymm8  = _mm256_load_pd(&vec2[i+12]); // y[3]

        ymm9  = _mm256_mul_pd( ymm1, ymm5 );   // xy0
        ymm10 = _mm256_mul_pd( ymm2, ymm6 );   // xy1
        ymm11 = _mm256_hadd_pd( ymm9, ymm10 ); // low to high: xy00+xy01 xy10+xy11 xy02+xy03 xy12+xy13

        ymm12 = _mm256_mul_pd( ymm3, ymm7 ); // xy2
        ymm13 = _mm256_mul_pd( ymm4, ymm8 ); // xy3
        ymm14 = _mm256_hadd_pd( ymm12, ymm13 );  // low to high: xy20+xy21 xy30+xy31 xy22+xy23 xy32+xy33

        ymm15 = _mm256_permute2f128_pd( ymm11, ymm14, 0x21 ); // low to high: xy02+xy03 xy12+xy13 xy20+xy21 xy30+xy31

        ymm1  = _mm256_blend_pd( ymm11, ymm14, 0b1100); // low to high: xy00+xy01 xy10+xy11 xy22+xy23 xy32+xy33

        ymm2 = _mm256_add_pd( ymm15, ymm1 );

        ymm0 = _mm256_add_pd( ymm0, ymm2 );
*/

/*        __m256d x[4], y[4];
        x[0] = _mm256_load_pd(&vec1[i]);
        x[1] = _mm256_load_pd(&vec1[i+4]);
        x[2] = _mm256_load_pd(&vec1[i+8]);
        x[3] = _mm256_load_pd(&vec1[i+12]);
        y[0] = _mm256_load_pd(&vec2[i]);
        y[1] = _mm256_load_pd(&vec2[i+4]);
        y[2] = _mm256_load_pd(&vec2[i+8]);
        y[3] = _mm256_load_pd(&vec2[i+12]);

        __m256d xy0 = _mm256_mul_pd( x[0], y[0] );
        __m256d xy1 = _mm256_mul_pd( x[1], y[1] );
        // low to high: xy00+xy01 xy10+xy11 xy02+xy03 xy12+xy13
        __m256d temp01 = _mm256_hadd_pd( xy0, xy1 );

        __m256d xy2 = _mm256_mul_pd( x[2], y[2] );
        __m256d xy3 = _mm256_mul_pd( x[3], y[3] );
        // low to high: xy20+xy21 xy30+xy31 xy22+xy23 xy32+xy33
        __m256d temp23 = _mm256_hadd_pd( xy2, xy3 );

        // low to high: xy02+xy03 xy12+xy13 xy20+xy21 xy30+xy31
        __m256d swapped = _mm256_permute2f128_pd( temp01, temp23, 0x21 );

        // low to high: xy00+xy01 xy10+xy11 xy22+xy23 xy32+xy33
        __m256d blended = _mm256_blend_pd(temp01, temp23, 0b1100);

        __m256d dotproduct = _mm256_add_pd( swapped, blended );
*/
        //ymm0 = _mm256_add_pd(ymm0,dotproduct);

/*        __m128d xmm1 = _mm256_extractf128_pd(dotproduct,0);
        __m128d xmm2 = _mm256_extractf128_pd(dotproduct,1);;
        __m128d xmm3 = _mm_hadd_pd(xmm1,xmm2);
        double res[2] __attribute__((aligned(_CBSIM_DBL_ALIGN_))) = {0.0, 0.0};
        _mm_store_pd(&res[0],xmm3);

        //_mm256_store_pd(&res[0],ymm12);
        result += (res[0] + res[1]);// + (res[2] + res[3]);
*/

//        _mm256_store_pd(&res[0],dotproduct);
//        result += (res[0] + res[1]) + (res[2] + res[3]);

        //result_SIMD_INTRINSICS += dotproduct[0] + dotproduct[1] + dotproduct[2] + dotproduct[3];

        //double res[4] __attribute__((aligned(_CBSIM_DBL_ALIGN_)));
        //_mm256_store_pd(&res[0],ymm0);
        //result_SIMD_INTRINSICS += res[0] + res[1] + res[2] + res[3];
        //double* res = (double*)&ymm0;
        //result_SIMD_INTRINSICS += res[0] + res[1] + res[2] + res[3];
    }
    //double* res = (double*)&ymm0;
    //result_SIMD_INTRINSICS += res[0] + res[1] + res[2] + res[3];
    //double res[4] __attribute__((aligned(_CBSIM_DBL_ALIGN_)));
    //_mm256_store_pd(&res[0],ymm0);
    //result_SIMD_INTRINSICS += res[0] + res[1] + res[2] + res[3];
}


//    t2 = tbb::tick_count::now();
//    double exec_time = 1000.0*(t2-t1).seconds();


    //std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(5);
    std::cout<<std::endl<<"RESULTS: " <<std::endl;
    std::cout<<"result_intrin ----------: "<< result << std::endl;
    //std::cout<<"result_intrin ----------: "<< result << ", time: " << 1000.0*(t2-t1).seconds() << " ms" << std::endl;

    std::cout<<std::endl<<"Program end. "<<std::endl<<std::endl;
    return 0;
}