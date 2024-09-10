void SimCudaHelper::Initialize(int cudaDevice)
{
    cudaDevice = Init(cudaDevice);
    cudaError res;
    // From CUDA prog guide: cudaSetDevice()and cudaGLSetGLDevice() are mutually exclusive.
    res = cudaSetDevice(cudaDevice);
    if (res != cudaSuccess)
    {
        CheckError(res, "cudaGetDeviceCount failed");
    }
    else
    {
        cout << "CUDA: Successful cudaSetDevice, using device " << cudaDevice << "\n";
    }
}