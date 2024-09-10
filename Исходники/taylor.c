void*drawman(void*x){
	int c=col++;
	unsigned _m=mx,mxx=16777216/_m;
	double _x=xx,_y=yy,_w=wh;
	do{
		__m128d cr=_mm_set1_pd(_x+_w*c);
		for(int j=0;j<512;j+=2){
			__m128d zr=cr,
				zi=_mm_set_pd(_y+_w*j,_y+_w*(j+1)),ci=zi,
				zr2=_mm_mul_pd(zr,zr),zi2=_mm_mul_pd(zi,zi);
			unsigned mk=mx-1;
			uint64_t kk[2]__attribute__((aligned(16)))={mk,mk};
			__m128i k=_mm_load_si128((__m128i*)kk);
			do{
				zi=_mm_mul_pd(zi,zr);
				zi=_mm_add_pd(_mm_add_pd(zi,zi),ci);
				zr=_mm_add_pd(_mm_sub_pd(zr2,zi2),cr);
				zr2=_mm_mul_pd(zr,zr);
				zi2=_mm_mul_pd(zi,zi);
				__m128d n=_mm_cmplt_pd(_mm_add_pd(zr2,zi2),_mm_set1_pd(4));
				if(!_mm_movemask_pd(n))break;
				k=_mm_add_epi64(k,_mm_castpd_si128(n));
			}while(--mk);
			_mm_store_si128((__m128i*)kk,k);
			manor[c][j]=kk[1]*mxx>>16;
			manor[c][j+1]=kk[0]*mxx>>16;
		}
		done[c>>6]|=1ULL<<(c&63);
		c=col++;
	}while(c<512&&!pull);
}