void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // ****************   PARSE THE INPUTS  ******************* //
    myAssert(nrhs==4,"fitStumpUINT8_c: bad nrhs");
    const mxArray* mxX = prhs[0];
    myAssert(mxIsUint8(mxX), "fitStumpUINT8_c: X must be uint8");
    unsigned char* X = (unsigned char*) mxGetPr(mxX);
    int N = mxGetM(mxX);    int p = mxGetN(mxX);
    
    const mxArray* mxWWY = prhs[1];
    myAssert(mxIsDouble(prhs[1]), "fitStumpUINT8_c: wwy must be double");
    double* wwy = (double*) mxGetPr(mxWWY);
    myAssert(mxGetM(mxWWY)==2, "fitStumpUINT8_c: wwy must be 2 x N");
    myAssert(mxGetN(mxWWY)==N, "fitStumpUINT8_c: wwy must be 2 x N");
    const mxArray* mxCandVars = prhs[2];
    myAssert(mxIsUint32(mxCandVars), "fitStumpUINT8_c: mxCandVars must be uint32");
    unsigned int* candVars = (unsigned int*) mxGetPr(mxCandVars);
    int nCand = mxGetNumberOfElements(mxCandVars);
    
    const mxArray* mxGoodInd = prhs[3];
    int nGd = mxGetNumberOfElements(mxGoodInd);
    myAssert(nGd==0 || mxIsUint32(mxGoodInd), "fitStumpUINT8_c: mxGoodInd must be uint32");
    unsigned int* goodInd = (unsigned int*) mxGetPr(mxGoodInd);
        
    // ******************  SET UP THE OUTPUTS  ******************* //
    plhs[0] = mxCreateNumericMatrix(1,nCand,mxINT32_CLASS,mxREAL);
    int* cutInd = (int*) mxGetPr(plhs[0]);
	plhs[1] = mxCreateNumericMatrix(1,nCand,mxDOUBLE_CLASS, mxREAL);
    double* ssxBest = (double*) mxGetPr(plhs[1]);
	plhs[2] = mxCreateNumericMatrix(1,nCand,mxDOUBLE_CLASS,mxREAL);
	double* muL = (double*) mxGetPr(plhs[2]);
	plhs[3] = mxCreateNumericMatrix(1,nCand,mxDOUBLE_CLASS,mxREAL);
    double* muR = (double*) mxGetPr(plhs[3]);
    // ************** MAIN LOOP OVER ALL CANDIDATE VARS *********** //
    for(int m=0; m<nCand; m++) {
        unsigned char* x = X + N*candVars[m];
        double* wwyBuck = (double *) mxMalloc(2*256*sizeof(double));
        // fill weights with small epsilon for numerical stability
        for(int i=0; i<256; i++) {
            wwyBuck[i*2] = 1.0E-10;
            wwyBuck[i*2+1] = 0;
        }
        // make weighted histogram of w and wy
        buckSums(wwyBuck, wwy, N, x, goodInd, nGd);
        // cumsum
        __m128d* wwyBuck128 = (__m128d*) wwyBuck;
        for(int i=1; i<256; i++)
            wwyBuck128[i] = _mm_add_pd(wwyBuck128[i], wwyBuck128[i-1]);
        // compute -ssx
        __m128d wCumEnd = _mm_set_pd(wwyBuck[256*2-2], wwyBuck[256*2-2]);
        __m128d wyCumEnd = _mm_set_pd(wwyBuck[256*2-1], wwyBuck[256*2-1]);

        __m128d* ssx128 = (__m128d*) mxMalloc(1*256*sizeof(__m128d));
        for(int i=0; i<128; i++) {
            __m128d wwyBuck1 = wwyBuck128[i*2];
            __m128d wwyBuck2 = wwyBuck128[i*2+1];
            __m128d wyBuck = _mm_unpackhi_pd(wwyBuck1,wwyBuck2);
            __m128d wBuck = _mm_unpacklo_pd(wwyBuck1,wwyBuck2);
            ssx128[i] = _mm_div_pd(_mm_mul_pd(wyBuck,wyBuck),wBuck);

            __m128d tmp1 = _mm_sub_pd(wyCumEnd,wyBuck);
            tmp1 = _mm_mul_pd(tmp1,tmp1);
            __m128d tmp2 = _mm_sub_pd(wCumEnd,wBuck);

            ssx128[i] = _mm_add_pd(ssx128[i],_mm_div_pd(tmp1,tmp2));
        }
        // find best split location for this candidate variable
        double* ssx = (double*) ssx128;
        double mx = ssx[0];     cutInd[m] = 0;
        
        for(int i=1;i<256;i++) {
            if(ssx[i] > mx) {
                mx = ssx[i];	cutInd[m] = i;
            }
        }
        ssxBest[m] = -mx;
        muL[m] = wwyBuck[cutInd[m]*2+1] / wwyBuck[cutInd[m]*2];
        muR[m] = (wwyBuck[256*2-1] - wwyBuck[cutInd[m]*2+1]) / (wwyBuck[256*2-2] - wwyBuck[cutInd[m]*2]);
    }
}