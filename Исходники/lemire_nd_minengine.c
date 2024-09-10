/* Gateway of LEMIRE_ND_MINENGINE */
void mexFunction(int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[]) {
    
    mxClassID ClassID;
    
    /* pointer to the index array */
    double *idx, *minidx;
    /* Data pointers, which one are used depends on the class of A */
    double *adouble, *valdouble;
    float *asingle, *valsingle;
    int64 *aint64, *valint64;
    int32 *aint32, *valint32;
    int16 *aint16, *valint16;
    int08 *aint08, *valint08;
    uint64 *auint64, *valuint64;
    uint32 *auint32, *valuint32;
    uint16 *auint16, *valuint16;
    uint08 *auint08, *valuint08;

    mwSize i, pleft, n, window;
    mwSize imax, margin, linidx;
    int left, lstart, size;
    mwSize *Wedge; /* wedge */
    int nWedge; /* wedge number of elements (0 is empty wedge) */
    int Wedgefirst, Wedgelast; /* Indices of two ends of the wedge */
    int shape;
    
    mwSize p, q, j, k;
    mwIndex stepA, stepMinMax;
    const mwSize* dimA;
    mwSize dimOut[3];
    
    void *adata, *valdata;
    double *idxdata, *minidxdata;
    
    /* Check number of arguments */
    if (nrhs!=4)
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: four arguments are required.");
    
     /* Get the shape */
    shape = (int)mxGetScalar(SHAPE);
    
    /* Get class of input matrix A */
    ClassID = mxGetClassID(A);
    
    if (mxGetClassID(IDX) != mxDOUBLE_CLASS)
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: idx must be double.");
    
    /* Do not support on sparse */
    if (mxIsSparse(A))
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: First input A must be full.");       
    
    /* Get the number of elements of A */
    /* Get the size, MUST BE two or three, no check */
    dimA = mxGetDimensions(A);
    p = dimA[0];
    n = dimA[1];
    if (mxGetNumberOfDimensions(A)<3)
        q = 1; /* third dimension is singleton */
    else
        q = dimA[2];
   
    /* Window input must be double */
    if (mxGetClassID(WINDOW)!=mxDOUBLE_CLASS)
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: Second input WINDOW must be double.");
    
    /* Get the window size, cast it in mwSize */
    window = (mwSize)(*mxGetPr(WINDOW));
    margin = window-1;
    
    if (window<1) /* Check if it's valid */
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: windows must be 1 or greater.");   
    if (window>n || window>MAXINT)
        mexErrMsgTxt("LEMIRE_ND_MINENGINE: windows larger than data length.");
    
    /* Allocate wedges buffers for L and U, each is size (window+1) */
    size = (int)(window+1);
    Wedge = mxMalloc(size*sizeof(mwSize));
    if (Wedge==NULL) mexErrMsgTxt("LEMIRE_ND_MINENGINE: out of memory.");
    
    /* This parameters configure for three cases:
     * - full scan (minimum 1-element intersecting with window), or
     * - same scan (output has the same size as input)
     * - valid scan (full overlapping with window) */ 
    if (shape==FULL_SHAPE) {
        dimOut[1] = n+margin;
        lstart = -(int)(margin);
    } else if (shape==SAME_SHAPE) {
        dimOut[1] = n;
        lstart = -(int)(margin/2);
    } else { /* if (shape==VALID_SHAPE) */
        dimOut[1] = n-margin;
        lstart = 0;
    }
    
    /* The last index to be scanned */
    imax = (dimOut[1] + margin) + lstart;
    
    /* Create output arrays */
    dimOut[0] = p;
    dimOut[2] = q;

    MINVAL = mxCreateNumericArray(3, dimOut, ClassID, mxREAL);
    MINIDX = mxCreateNumericArray(3, dimOut, mxDOUBLE_CLASS, mxREAL); 
    /* Check if allocation is succeeded */
    if ((MINVAL==NULL) || (MINIDX==NULL))
         mexErrMsgTxt("LEMIRE_ND_MINENGINE: out of memory.");    
      
    /* Jump step of the third dimension */
    stepA = p*n; /* for A */
    stepMinMax = p*dimOut[1]; /* step for output */
    
    /* Get data pointers */
    adata = mxGetData(A);
    idxdata = mxGetPr(IDX); 
    valdata = mxGetData(MINVAL);
    minidxdata = mxGetPr(MINIDX);
        
    /* Call the engine depending on ClassID */
    switch (ClassID) {
        case mxDOUBLE_CLASS:
            SCAN(adouble, valdouble, double);
            break;
        case mxSINGLE_CLASS:
            SCAN(asingle, valsingle, float);
            break;
        case mxINT64_CLASS:
            SCAN(aint64, valint64, int64);
            break;
        case mxUINT64_CLASS:
            SCAN(auint64, valuint64, uint64);
            break;
        case mxINT32_CLASS:
            SCAN(aint32, valint32, int32);
            break;
        case mxUINT32_CLASS:
            SCAN(auint32, valuint32, uint32);
            break;
        case mxCHAR_CLASS:
            SCAN(auint16, valuint16, uint16);
            break;
        case mxINT16_CLASS:
            SCAN(aint16, valint16, int16);
            break;
        case mxUINT16_CLASS:
            SCAN(auint16, valuint16, uint16);
            break;
        case mxLOGICAL_CLASS:
            SCAN(auint08, valuint08, uint08);
            break;
        case mxINT8_CLASS:
            SCAN(aint08, valint08, int08);
            break;
        case mxUINT8_CLASS:
            SCAN(auint08, valuint08, uint08);
            break;
        default:
            mexErrMsgTxt("LEMIRE_ND_MINENGINE: Class not supported.");
    } /* switch */
    
    /* Free the buffer */
    mxFree(Wedge);
    
    return;
    
} /* Gateway LEMIRE_ND_MINENGINE */