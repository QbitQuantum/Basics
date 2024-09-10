__global__ void test_llround(hipLaunchParm lp, double *a, long long int *b){
    int tid = hipThreadIdx_x;
    b[tid] = llround(a[tid]);
}