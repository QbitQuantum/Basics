 unsigned __stdcall getvectors_multi_threaded(float **Args){
#else
 void getvectors_multi_threaded(float **Args){
#endif

    /* Input image, output vectors */
    float *I, *V;
    float *K;
    /* Size of input image */
    int Isize[3];
    /* Size of input vectors */
    int Vsize[2];
    /* Size of vector volume */
    int image3D;
    /* Constants used */
    int kernelratio;
    int block[6];

    int ThreadID;
    int Nthreads;

    I=Args[0];
    Isize[0]=(int)Args[1][0];
    Isize[1]=(int)Args[1][1];
    Isize[2]=(int)Args[1][2];
    V=Args[2];
    Vsize[0]=(int)Args[3][0];
    Vsize[1]=(int)Args[3][1];
    Vsize[2]=(int)Args[3][2];
    kernelratio=(int)Args[4][0];
    image3D=(int)Args[4][1];
    block[0]=(int)Args[5][0];
    block[1]=(int)Args[5][1];
    block[2]=(int)Args[5][2];
    block[3]=(int)Args[5][3];
    block[4]=(int)Args[5][4];
    block[5]=(int)Args[5][5];
    K=Args[6];
    ThreadID=(int)Args[7][0];
    Nthreads=(int)Args[8][0];

    if(image3D==0) {
        get2Dvectors(I, Isize, V, Vsize, kernelratio, block, K, ThreadID, Nthreads);
    }
    else {
        get3Dvectors(I, Isize, V, Vsize, kernelratio, block, K, ThreadID, Nthreads);
    }

    /*  explicit end thread, helps to ensure proper recovery of resources allocated for the thread */
    #ifdef _WIN32
            _endthreadex( 0 );
    return 0;
    #else
            pthread_exit(NULL);
    #endif
}