int main(int argc, char** argv)
{
	/* variable declaration */
	DB(DB_LVL, "declaration");
	DT * memA_t0, *memA_t1, *memA_t2, *memA_t3;
	DT * memB_t0, *memB_t1, *memB_t2, *memB_t3;
	DT * memO_t0, *memO_t1, *memO_t2, *memO_t3;  
	int reps, size;
	int samples;
	int tid;
	int i, p, r, bytes, elems;	
	int bytes_min, bytes_max;	
	int elems_min, elems_max;
	double func_overhead;
	double t_start, t_end;	
	double t_min, c_min;	
	double alpha = 0.5;
	DB(DB_LVL, SEPERATOR);
	
	/* initialization */
	DB(DB_LVL, "intialization");
	samples = 3;	
	bytes_min = 1024, bytes_max = 1024*32; /* [1KB, 32KB] */
	elems_min = bytes_min/sizeof(DT), elems_max = bytes_max/sizeof(DT); /* the number of elements */
	reps = 	40000;

	DB(DB_LVL, SEPERATOR);
	
	/* omp environment */
  const int nthreads = argc > 1 ? atoi(argv[1]) : 4;
  fprintf(stderr , "nthreads= %d\n", nthreads);

	omp_set_num_threads(nthreads);

	/* iteration */
	DB(DB_LVL, "measurement");	
	for(elems=elems_min, bytes=bytes_min; elems<=elems_max; elems=elems+elems_min, bytes=bytes+bytes_min)
	{
		memA_t0 = (DT *)_mm_malloc(bytes_max, 64);
		memA_t1 = (DT *)_mm_malloc(bytes_max, 64);
		memA_t2 = (DT *)_mm_malloc(bytes_max, 64);
		memA_t3 = (DT *)_mm_malloc(bytes_max, 64);
		memB_t0 = (DT *)_mm_malloc(bytes_max, 64);
		memB_t1 = (DT *)_mm_malloc(bytes_max, 64);
		memB_t2 = (DT *)_mm_malloc(bytes_max, 64);
		memB_t3 = (DT *)_mm_malloc(bytes_max, 64);
		memO_t0 = (DT *)_mm_malloc(bytes_max, 64);
		memO_t1 = (DT *)_mm_malloc(bytes_max, 64);
		memO_t2 = (DT *)_mm_malloc(bytes_max, 64);
		memO_t3 = (DT *)_mm_malloc(bytes_max, 64);

		/* initialization a local space */
		fill(memA_t0, elems, 1.0);
		fill(memA_t1, elems, 2.0);
		fill(memA_t2, elems, 3.0);
		fill(memA_t3, elems, 4.0);
		fill(memB_t0, elems, 1.0);
		fill(memB_t1, elems, 2.0);
		fill(memB_t2, elems, 3.0);
		fill(memB_t3, elems, 4.0);
		fill(memO_t0, elems, 1.0);
		fill(memO_t1, elems, 2.0);
		fill(memO_t2, elems, 3.0);
		fill(memO_t3, elems, 4.0);
		
		/* measurement */
		t_min = 0.0f;
		c_min = 0.0f;
		DT ret_t0 = 0.0;		
		DT ret_t1 = 0.0;
		DT ret_t2 = 0.0;
		DT ret_t3 = 0.0;

#ifdef SAXPY2
#define Z _z
#else
#define Z _z
#endif

		for(p=0; p<samples; p++)
		{			
      __m512d *_x, *_y, *_z;
			#pragma omp parallel	private(_x,_y,_z) default(shared)
			{
        int tid;
				tid = omp_get_thread_num();
        switch(tid)
        {
          case 0:
            _x = (__m512d*)memA_t0;
            _y = (__m512d*)memB_t0;
            _z = (__m512d*)memO_t0;
            break;
          case 1:
            _x = (__m512d*)memA_t1;
            _y = (__m512d*)memB_t1;
            _z = (__m512d*)memO_t1;
            break;
          case 2:
            _x = (__m512d*)memA_t2;
            _y = (__m512d*)memB_t2;
            _z = (__m512d*)memO_t2;
            break;
          case 3:
            _x = (__m512d*)memA_t3;
            _y = (__m512d*)memB_t3;
            _z = (__m512d*)memO_t3;
            break;
          default:
            assert(0);
        }
#pragma omp barrier
        if(p==(samples-1))
          t_start = timer();	

        int r;
        for(r=0; r<reps; r++)
        {
          asm("#t0-beg");
#if 0  
          double *memO_t0 = (double*)Z;
          const double *memA_t0 = (double*)_x;
          const double *memB_t0 = (double*)_y;
#pragma vector aligned
          for(i=0; i<elems; i=i+1)
          {
            //ret_t0 += mem_t0[i];
            memO_t0[i] = alpha * memA_t0[i] + memB_t0[i];
          }				
          memO_t0[0] = memO_t0[0] * 0.1; // to avoid overflow and optimizations
#else
          const int cnts = elems >> 3;
          const __m512d  _a = _mm512_set1_pd(alpha);                           
          int ib;
          for (ib = 0; ib < cnts; ib += 8*8)
          { 
            Z[ib+0] = _mm512_add_pd(_y[ib+0], _mm512_mul_pd(_a,_x[ib+0]));
            Z[ib+1] = _mm512_add_pd(_y[ib+1], _mm512_mul_pd(_a,_x[ib+1]));
            Z[ib+2] = _mm512_add_pd(_y[ib+2], _mm512_mul_pd(_a,_x[ib+2]));
            Z[ib+3] = _mm512_add_pd(_y[ib+3], _mm512_mul_pd(_a,_x[ib+3]));
            Z[ib+4] = _mm512_add_pd(_y[ib+4], _mm512_mul_pd(_a,_x[ib+4]));
            Z[ib+5] = _mm512_add_pd(_y[ib+5], _mm512_mul_pd(_a,_x[ib+5]));
            Z[ib+6] = _mm512_add_pd(_y[ib+6], _mm512_mul_pd(_a,_x[ib+6]));
            Z[ib+7] = _mm512_add_pd(_y[ib+7], _mm512_mul_pd(_a,_x[ib+7]));

            Z[ib+8+0] = _mm512_add_pd(_y[ib+8+0], _mm512_mul_pd(_a,_x[ib+8+0]));
            Z[ib+8+1] = _mm512_add_pd(_y[ib+8+1], _mm512_mul_pd(_a,_x[ib+8+1]));
            Z[ib+8+2] = _mm512_add_pd(_y[ib+8+2], _mm512_mul_pd(_a,_x[ib+8+2]));
            Z[ib+8+3] = _mm512_add_pd(_y[ib+8+3], _mm512_mul_pd(_a,_x[ib+8+3]));
            Z[ib+8+4] = _mm512_add_pd(_y[ib+8+4], _mm512_mul_pd(_a,_x[ib+8+4]));
            Z[ib+8+5] = _mm512_add_pd(_y[ib+8+5], _mm512_mul_pd(_a,_x[ib+8+5]));
            Z[ib+8+6] = _mm512_add_pd(_y[ib+8+6], _mm512_mul_pd(_a,_x[ib+8+6]));
            Z[ib+8+7] = _mm512_add_pd(_y[ib+8+7], _mm512_mul_pd(_a,_x[ib+8+7]));

            Z[ib+16+0] = _mm512_add_pd(_y[ib+16+0], _mm512_mul_pd(_a,_x[ib+16+0]));
            Z[ib+16+1] = _mm512_add_pd(_y[ib+16+1], _mm512_mul_pd(_a,_x[ib+16+1]));
            Z[ib+16+2] = _mm512_add_pd(_y[ib+16+2], _mm512_mul_pd(_a,_x[ib+16+2]));
            Z[ib+16+3] = _mm512_add_pd(_y[ib+16+3], _mm512_mul_pd(_a,_x[ib+16+3]));
            Z[ib+16+4] = _mm512_add_pd(_y[ib+16+4], _mm512_mul_pd(_a,_x[ib+16+4]));
            Z[ib+16+5] = _mm512_add_pd(_y[ib+16+5], _mm512_mul_pd(_a,_x[ib+16+5]));
            Z[ib+16+6] = _mm512_add_pd(_y[ib+16+6], _mm512_mul_pd(_a,_x[ib+16+6]));
            Z[ib+16+7] = _mm512_add_pd(_y[ib+16+7], _mm512_mul_pd(_a,_x[ib+16+7]));

            Z[ib+24+0] = _mm512_add_pd(_y[ib+24+0], _mm512_mul_pd(_a,_x[ib+24+0]));
            Z[ib+24+1] = _mm512_add_pd(_y[ib+24+1], _mm512_mul_pd(_a,_x[ib+24+1]));
            Z[ib+24+2] = _mm512_add_pd(_y[ib+24+2], _mm512_mul_pd(_a,_x[ib+24+2]));
            Z[ib+24+3] = _mm512_add_pd(_y[ib+24+3], _mm512_mul_pd(_a,_x[ib+24+3]));
            Z[ib+24+4] = _mm512_add_pd(_y[ib+24+4], _mm512_mul_pd(_a,_x[ib+24+4]));
            Z[ib+24+5] = _mm512_add_pd(_y[ib+24+5], _mm512_mul_pd(_a,_x[ib+24+5]));
            Z[ib+24+6] = _mm512_add_pd(_y[ib+24+6], _mm512_mul_pd(_a,_x[ib+24+6]));
            Z[ib+24+7] = _mm512_add_pd(_y[ib+24+7], _mm512_mul_pd(_a,_x[ib+24+7]));

            Z[ib+32+0] = _mm512_add_pd(_y[ib+32+0], _mm512_mul_pd(_a,_x[ib+32+0]));
            Z[ib+32+1] = _mm512_add_pd(_y[ib+32+1], _mm512_mul_pd(_a,_x[ib+32+1]));
            Z[ib+32+2] = _mm512_add_pd(_y[ib+32+2], _mm512_mul_pd(_a,_x[ib+32+2]));
            Z[ib+32+3] = _mm512_add_pd(_y[ib+32+3], _mm512_mul_pd(_a,_x[ib+32+3]));
            Z[ib+32+4] = _mm512_add_pd(_y[ib+32+4], _mm512_mul_pd(_a,_x[ib+32+4]));
            Z[ib+32+5] = _mm512_add_pd(_y[ib+32+5], _mm512_mul_pd(_a,_x[ib+32+5]));
            Z[ib+32+6] = _mm512_add_pd(_y[ib+32+6], _mm512_mul_pd(_a,_x[ib+32+6]));
            Z[ib+32+7] = _mm512_add_pd(_y[ib+32+7], _mm512_mul_pd(_a,_x[ib+32+7]));

            Z[ib+40+0] = _mm512_add_pd(_y[ib+40+0], _mm512_mul_pd(_a,_x[ib+40+0]));
            Z[ib+40+1] = _mm512_add_pd(_y[ib+40+1], _mm512_mul_pd(_a,_x[ib+40+1]));
            Z[ib+40+2] = _mm512_add_pd(_y[ib+40+2], _mm512_mul_pd(_a,_x[ib+40+2]));
            Z[ib+40+3] = _mm512_add_pd(_y[ib+40+3], _mm512_mul_pd(_a,_x[ib+40+3]));
            Z[ib+40+4] = _mm512_add_pd(_y[ib+40+4], _mm512_mul_pd(_a,_x[ib+40+4]));
            Z[ib+40+5] = _mm512_add_pd(_y[ib+40+5], _mm512_mul_pd(_a,_x[ib+40+5]));
            Z[ib+40+6] = _mm512_add_pd(_y[ib+40+6], _mm512_mul_pd(_a,_x[ib+40+6]));
            Z[ib+40+7] = _mm512_add_pd(_y[ib+40+7], _mm512_mul_pd(_a,_x[ib+40+7]));

            Z[ib+48+0] = _mm512_add_pd(_y[ib+48+0], _mm512_mul_pd(_a,_x[ib+48+0]));
            Z[ib+48+1] = _mm512_add_pd(_y[ib+48+1], _mm512_mul_pd(_a,_x[ib+48+1]));
            Z[ib+48+2] = _mm512_add_pd(_y[ib+48+2], _mm512_mul_pd(_a,_x[ib+48+2]));
            Z[ib+48+3] = _mm512_add_pd(_y[ib+48+3], _mm512_mul_pd(_a,_x[ib+48+3]));
            Z[ib+48+4] = _mm512_add_pd(_y[ib+48+4], _mm512_mul_pd(_a,_x[ib+48+4]));
            Z[ib+48+5] = _mm512_add_pd(_y[ib+48+5], _mm512_mul_pd(_a,_x[ib+48+5]));
            Z[ib+48+6] = _mm512_add_pd(_y[ib+48+6], _mm512_mul_pd(_a,_x[ib+48+6]));
            Z[ib+48+7] = _mm512_add_pd(_y[ib+48+7], _mm512_mul_pd(_a,_x[ib+48+7]));

            Z[ib+56+0] = _mm512_add_pd(_y[ib+56+0], _mm512_mul_pd(_a,_x[ib+56+0]));
            Z[ib+56+1] = _mm512_add_pd(_y[ib+56+1], _mm512_mul_pd(_a,_x[ib+56+1]));
            Z[ib+56+2] = _mm512_add_pd(_y[ib+56+2], _mm512_mul_pd(_a,_x[ib+56+2]));
            Z[ib+56+3] = _mm512_add_pd(_y[ib+56+3], _mm512_mul_pd(_a,_x[ib+56+3]));
            Z[ib+56+4] = _mm512_add_pd(_y[ib+56+4], _mm512_mul_pd(_a,_x[ib+56+4]));
            Z[ib+56+5] = _mm512_add_pd(_y[ib+56+5], _mm512_mul_pd(_a,_x[ib+56+5]));
            Z[ib+56+6] = _mm512_add_pd(_y[ib+56+6], _mm512_mul_pd(_a,_x[ib+56+6]));
            Z[ib+56+7] = _mm512_add_pd(_y[ib+56+7], _mm512_mul_pd(_a,_x[ib+56+7]));

          } 
#endif
          asm("#t0-end");
        }								
			}
			if(p==(samples-1))
				t_end = timer();			
		}	
		t_min = (t_end - t_start)/reps;		
		printf("%lf,%lf,%lf,%lf\n", ret_t0, ret_t1, ret_t2, ret_t3);
		SAVE_DATA("%lf\t", 3*nthreads*bytes/t_min);
    printf("cbw: %lf\t elems= %d mem_tot= %d\n", 3*nthreads*bytes/t_min, elems/8, 3*elems*sizeof(DT)*nthreads);
		if(memA_t0!=NULL) _mm_free(memA_t0);
		if(memA_t1!=NULL) _mm_free(memA_t1);
		if(memA_t2!=NULL) _mm_free(memA_t2);
		if(memA_t3!=NULL) _mm_free(memA_t3);
		if(memB_t0!=NULL) _mm_free(memB_t0);
		if(memB_t1!=NULL) _mm_free(memB_t1);
		if(memB_t2!=NULL) _mm_free(memB_t2);
		if(memB_t3!=NULL) _mm_free(memB_t3);
		if(memO_t0!=NULL) _mm_free(memO_t0);
		if(memO_t1!=NULL) _mm_free(memO_t1);
		if(memO_t2!=NULL) _mm_free(memO_t2);
		if(memO_t3!=NULL) _mm_free(memO_t3);
	}		
	DB(DB_LVL, SEPERATOR);			
	
	/* post-process */
	DB(DB_LVL, "post-process");

	DB(DB_LVL, SEPERATOR);
}