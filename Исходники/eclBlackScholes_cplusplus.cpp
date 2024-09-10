int main(int argc, char *argv[])
{
    cl_uint samples = 256 * 256 * 4;
    size_t blockSizeX = 1;
    size_t blockSizeY = 1;
    cl_float *randArray = NULL;
    cl_float *deviceCallPrice = NULL;
    cl_float *devicePutPrice = NULL;
    cl_float *hostCallPrice = NULL;
    cl_float *hostPutPrice = NULL;
	ecl::error ret;

    cl_uint height = 64;

    /* Calculate width and height from samples */
    samples = samples / 4;
    samples = (samples / GROUP_SIZE)? (samples / GROUP_SIZE) * GROUP_SIZE: GROUP_SIZE;

    cl_uint tempVar1 = (cl_uint)sqrt((double)samples);
    tempVar1 = (tempVar1 / GROUP_SIZE)? (tempVar1 / GROUP_SIZE) * GROUP_SIZE: GROUP_SIZE;
    samples = tempVar1 * tempVar1;

    width = tempVar1;
    height = width;
    ret = ecl::compileSource(code);
	assert(ret == eclSuccess);
    setParam<cl_uint>(&width, widthStr, widthDefault);

    // Alloc & init input data
    randArray = new (ecl::allocator) cl_float[width * height * sizeof(cl_float4)];
    deviceCallPrice = new (ecl::allocator) cl_float[width * height * sizeof(cl_float4)];
    devicePutPrice = new (ecl::allocator) cl_float[width * height * sizeof(cl_float4)];
    assert(randArray != NULL);
    assert(deviceCallPrice != NULL);
    assert(devicePutPrice != NULL);
    hostCallPrice = (cl_float*)malloc(width * height * sizeof(cl_float4));
    if(hostCallPrice == NULL)
        return 0;
    hostPutPrice = (cl_float*)malloc(width * height * sizeof(cl_float4));
    if(hostPutPrice == NULL) {
        free(hostCallPrice);
        return 0;
    }

    // random initialisation of input
    for(cl_uint i = 0; i < width * height * 4; i++)
        randArray[i] = (float)rand() / (float)RAND_MAX;

    eclMemset(deviceCallPrice, 0, width * height * sizeof(cl_float4));
    eclMemset(devicePutPrice, 0, width * height * sizeof(cl_float4));
    eclMemset(hostCallPrice, 0, width * height * sizeof(cl_float4));
    eclMemset(hostPutPrice, 0, width * height * sizeof(cl_float4));

    // Call the kernel
    ecl::config globalSize(width, height);
    ecl::config localSize(blockSizeX, blockSizeY);
	ecl::config globalWorkOffset(0); 
    ecl::kernel kernel("blackScholes", ret);
    assert(ret == eclSuccess);
#ifndef __GXX_EXPERIMENTAL_CXX0X__
    ret = kernel.setArg(0, randArray);
	assert(ret == eclSuccess);
    ret = kernel.setArg(1, width);
	assert(ret == eclSuccess);
    ret = kernel.setArg(2, deviceCallPrice);
	assert(ret == eclSuccess);
    ret = kernel.setArg(3, devicePutPrice);
	assert(ret == eclSuccess);
    ret = kernel.callNDRange(globalSize, localSize, globalWorkOffset);
	assert(ret == eclSuccess);
#else
    ret = kernel(globalSize, localSize)(randArray, width, deviceCallPrice, devicePutPrice);
	assert(ret == eclSuccess);
#endif

    printf("deviceCallPrice£º\n");
    for(cl_uint i = 0; i < width; i++) {
        printf("%f ", deviceCallPrice[i]);
    }
    printf("\ndevicePutPrice£º\n");
    for(cl_uint i = 0; i < width; i++) {
        printf("%f ", devicePutPrice[i]);
    }

    blackScholesCPU(randArray, width, height, hostCallPrice, hostPutPrice);
    printf("\nhostCallPrice£º\n");
    for(cl_uint i = 0; i < width; i++) {
        printf("%f ", hostCallPrice[i]);
    }
    printf("\nhostPutPrice£º\n");
    for(cl_uint i = 0; i < width; i++) {
        printf("%f ", hostPutPrice[i]);
    }

    float error = 0.0f;
    float ref = 0.0f;
    bool callPriceResult = true;
    bool putPriceResult = true;
    float normRef;

    for(cl_uint i = 1; i < width * height * 4; ++i) {
        float diff = hostCallPrice[i] - deviceCallPrice[i];
        error += diff * diff;
        ref += hostCallPrice[i] * deviceCallPrice[i];
    }

    normRef =::sqrtf((float) ref);
    if (::fabs((float) ref) < 1e-7f) {
        callPriceResult = false;
    }
    if(callPriceResult) {
        float normError = ::sqrtf((float) error);
        error = normError / normRef;
        callPriceResult = error < 1e-6f;
    }

    for(cl_uint i = 1; i < width * height * 4; ++i) {
        float diff = hostPutPrice[i] - devicePutPrice[i];
        error += diff * diff;
        ref += hostPutPrice[i] * devicePutPrice[i];
    }

    normRef =::sqrtf((float) ref);
    if (::fabs((float) ref) < 1e-7f) {
        putPriceResult = false;
    }
    if(putPriceResult) {
        float normError = ::sqrtf((float) error);
        error = normError / normRef;
        putPriceResult = error < 1e-4f;
    }

    if(!(callPriceResult ? (putPriceResult ? true : false) : false)) {
        printf("Failed!\n");
    } else {
        printf("Passed!\n");
    }

    free(hostPutPrice);
    hostPutPrice = NULL;
    free(hostCallPrice);
    hostCallPrice = NULL;

    ecl::free(devicePutPrice);
    ecl::free(deviceCallPrice);
    ecl::free(randArray);

    return 0;
}