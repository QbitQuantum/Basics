//! This function is documented in the header file
void init_gpu(const gmx_device_info_t *deviceInfo)
{
    assert(deviceInfo);

    // If the device is NVIDIA, for safety reasons we disable the JIT
    // caching as this is known to be broken at least until driver 364.19;
    // the cache does not always get regenerated when the source code changes,
    // e.g. if the path to the kernel sources remains the same

    if (deviceInfo->vendor_e == OCL_VENDOR_NVIDIA)
    {
        // Ignore return values, failing to set the variable does not mean
        // that something will go wrong later.
#ifdef _MSC_VER
        _putenv("CUDA_CACHE_DISABLE=1");
#else
        // Don't override, maybe a dev is testing.
        setenv("CUDA_CACHE_DISABLE", "1", 0);
#endif
    }
}