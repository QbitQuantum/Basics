static inline void   sacEvaluateModelSPRT(PROSAC_HEST* p){
	unsigned i;
	unsigned isInlier;
	double   lambda       = 1.0;
	double   lambdaReject = ((1.0 - p->delta) / (1.0 - p->epsilon));
	double   lambdaAccept = ((   p->delta   ) / (    p->epsilon  ));
	float    distSq = p->maxD*p->maxD;
	float*   src = (float*)p->src;
	float*   dst = (float*)p->dst;
	float*   H   = p->H;
	
	
	p->inl      = 0;
	p->N_tested = 0;
	p->good     = 1;
	
	
	/* VECTOR */
	const __m128 distSqV=_mm_set1_ps(distSq);
	
	const __m128 H00=_mm_set1_ps(H[0]);
	const __m128 H01=_mm_set1_ps(H[1]);
	const __m128 H02=_mm_set1_ps(H[2]);
	const __m128 H10=_mm_set1_ps(H[4]);
	const __m128 H11=_mm_set1_ps(H[5]);
	const __m128 H12=_mm_set1_ps(H[6]);
	const __m128 H20=_mm_set1_ps(H[8]);
	const __m128 H21=_mm_set1_ps(H[9]);
	const __m128 H22=_mm_set1_ps(H[10]);
	
	for(i=0;i<(p->N-3) && p->good;i+=4){
		/* Backproject */
		__m128 x, y, X, Y, inter0, inter1, inter2, inter3;
		x=_mm_load_ps(src+2*i);
		y=_mm_load_ps(src+2*i+4);
		X=_mm_load_ps(dst+2*i);
		Y=_mm_load_ps(dst+2*i+4);
		
		inter0=_mm_unpacklo_ps(x,y);// y1 y0 x1 x0
		inter1=_mm_unpackhi_ps(x,y);// y3 y2 x3 x2
		inter2=_mm_unpacklo_ps(X,Y);// Y1 Y0 X1 X0
		inter3=_mm_unpackhi_ps(X,Y);// Y3 Y2 X3 X2
		
		x=_mm_castpd_ps(_mm_unpacklo_pd(_mm_castps_pd(inter0), _mm_castps_pd(inter1)));
		y=_mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(inter0), _mm_castps_pd(inter1)));
		X=_mm_castpd_ps(_mm_unpacklo_pd(_mm_castps_pd(inter2), _mm_castps_pd(inter3)));
		Y=_mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(inter2), _mm_castps_pd(inter3)));
		
		__m128 reprojX = _mm_add_ps(_mm_add_ps(_mm_mul_ps(H00, x), _mm_mul_ps(H01, y)), H02);
		__m128 reprojY = _mm_add_ps(_mm_add_ps(_mm_mul_ps(H10, x), _mm_mul_ps(H11, y)), H12);
		__m128 reprojZ = _mm_add_ps(_mm_add_ps(_mm_mul_ps(H20, x), _mm_mul_ps(H21, y)), H22);
		
		__m128 recipZ = _mm_rcp_ps(reprojZ);
		reprojX = _mm_mul_ps(reprojX, recipZ);
		reprojY = _mm_mul_ps(reprojY, recipZ);
		//reprojX = _mm_div_ps(reprojX, reprojZ);
		//reprojY = _mm_div_ps(reprojY, reprojZ);
		
		reprojX = _mm_sub_ps(reprojX, X);
		reprojY = _mm_sub_ps(reprojY, Y);
		
		reprojX = _mm_mul_ps(reprojX, reprojX);
		reprojY = _mm_mul_ps(reprojY, reprojY);
		
		__m128 reprojDistV = _mm_add_ps(reprojX, reprojY);
		
		__m128 cmp = _mm_cmple_ps(reprojDistV, distSqV);
		int msk = _mm_movemask_ps(cmp);
		
		/* ... */
		/*                   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15*/
		unsigned bitCnt[] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
		p->inl     += bitCnt[msk];
		
		
		/* SPRT */
		lambda *= p->lambdaTBL[msk];
		p->good = lambda <= p->A;
		/* If !p->good, the threshold A was exceeded, so we're rejecting */
	}
	
	/* SCALAR */
	for(;i<p->N && p->good;i++){
		/* Backproject */
		float x=src[i*2],y=src[i*2+1];
		float X=dst[i*2],Y=dst[i*2+1];
		
		float reprojX=H[0]*x+H[1]*y+H[2]; //  ( X_1 )     ( H_11 H_12    H_13  ) (x_1)
		float reprojY=H[4]*x+H[5]*y+H[6]; //  ( X_2 )  =  ( H_21 H_22    H_23  ) (x_2)
		float reprojZ=H[8]*x+H[9]*y+H[10];//  ( X_3 )     ( H_31 H_32 H_33=1.0 ) (x_3 = 1.0)
		
		//reproj is in homogeneous coordinates. To bring back to "regular" coordinates, divide by Z.
		reprojX/=reprojZ;
		reprojY/=reprojZ;
		
		//Compute distance
		reprojX-=X;
		reprojY-=Y;
		reprojX*=reprojX;
		reprojY*=reprojY;
		float reprojDist = reprojX+reprojY;
		
		/* ... */
		isInlier    = reprojDist <= distSq;
		p->inl     += isInlier;
		
		
		/* SPRT */
		lambda *= isInlier ? lambdaAccept : lambdaReject;
		p->good = lambda <= p->A;
		/* If !p->good, the threshold A was exceeded, so we're rejecting */
	}
	
	
	p->N_tested = i;
}