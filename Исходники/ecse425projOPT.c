void matVecMult_opt(int N, const double *matA, const double *vecB, double *vecC) 
{
    int i;
    int j;
    double c;
    if((N%2)==0)
    {
        for(i=0; i<N; i++, matA+=N)
        {
            //__m128d vecB_value = _mm_load_sd(&vecB[i]);
            //vecB_value = _mm_unpacklo_pd(vecB_value, vecB_value);
            for(j=0; j<N; j+=2)
            {
                //__m128d matA_value = _mm_load_pd(&matA[j]);
                //__m128d vecC_value = _mm_load_sd(&vecC[i]);
                //__m128d vecB_value = _mm_load_pd(&vecB[j]);
                //__m128d mulResult = _mm_mul_pd(matA_value, vecB_value);
                //mulResult = _mm_hadd_pd(mulResult, _mm_set_pd(0,0));
                _mm_store_sd(&vecC[i], _mm_add_sd(_mm_hadd_pd(
                    _mm_mul_pd(_mm_load_pd(&matA[j]), _mm_load_pd(&vecB[j])),
                    _mm_set_pd(0,0)),
                     _mm_load_sd(&vecC[i])));
            }
        }
    }
    else
    {
        for(i = 0; i < N; i++, matA+=N)
        {
            c=0;
            for(j=0; j < N; j++)
            {
            //vecC[i] += matA[i*N+j]*vecB[j];
            //_mm_prefetch(&matA[j], _MM_HINT_NTA);
                c += matA[j]*vecB[j];
            //_mm_prefetch(&matA[j+1], _MM_HINT_T2);
            //_mm_store_pd(&vecC[i], _mm_load_pd(&vecB[i]));
            //_mm_store_pd(&vecC[i],_mm_add_pd(_mm_mul_pd(_mm_load_pd(&matA[j]),_mm_load_pd(&vecB[i])),_mm_load_pd(&vecC[i])));
            }
            vecC[i]=c;
        }
    }
}