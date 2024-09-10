void mad12(int num, DT* data, int repeat, DT vv1, DT vv2)
{
	int gid, j;
#ifndef MIC
    #pragma omp parallel for 
    for (gid = 0; gid<num; gid++)
    {
        register DT s = (DT)(0.999f);
	register DT v1 = vv1;
	register DT v2 = vv2;
        for (j=0; j<repeat; ++j) 
        {
		MADD1_MOP2
        }
        data[gid] = s;
    }
#else
	#pragma omp parallel for 
    for (gid = 0; gid<num; gid=gid+STEP)
    {       
	__m512d s = _mm512_set1_pd(0.999f);
	__m512d v1 = _mm512_set1_pd(vv1);
	__m512d v2 = _mm512_set1_pd(vv2);
        for (j=0; j<repeat; ++j) 
        {
            MADD1_MOP2
        }

	_mm512_store_pd(&(data[gid]), s);
    }
#endif
	
	return ;
}