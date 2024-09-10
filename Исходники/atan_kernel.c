void KERNEL_NAME(VMLLONG n, VML_FLOAT * a, VML_FLOAT * b, VML_FLOAT * y, VML_FLOAT * z, VML_FLOAT * other_params) {
    VMLLONG i=0;
    for(i=0; i<n; i++) {
        y[i]=ATAN(a[i]);
    }
}