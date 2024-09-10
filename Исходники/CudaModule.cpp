void CudaModule::printDeviceInfo(CUdevice device)
{
    static const struct
    {
        CUdevice_attribute  attrib;
        const char*         name;
    } attribs[] =
    {
#define A21(ENUM, NAME) { CU_DEVICE_ATTRIBUTE_ ## ENUM, NAME },
#if (CUDA_VERSION >= 4000)
#   define A40(ENUM, NAME) A21(ENUM, NAME)
#else
#   define A40(ENUM, NAME) // TODO: Some of these may exist in earlier versions, too.
#endif

        A21(CLOCK_RATE,                         "Clock rate")
        A40(MEMORY_CLOCK_RATE,                  "Memory clock rate")
        A21(MULTIPROCESSOR_COUNT,               "Number of SMs")
//      A40(GLOBAL_MEMORY_BUS_WIDTH,            "DRAM bus width")
//      A40(L2_CACHE_SIZE,                      "L2 cache size")

        A21(MAX_THREADS_PER_BLOCK,              "Max threads per block")
        A40(MAX_THREADS_PER_MULTIPROCESSOR,     "Max threads per SM")
        A21(REGISTERS_PER_BLOCK,                "Registers per block")
//      A40(MAX_REGISTERS_PER_BLOCK,            "Max registers per block")
        A21(SHARED_MEMORY_PER_BLOCK,            "Shared mem per block")
//      A40(MAX_SHARED_MEMORY_PER_BLOCK,        "Max shared mem per block")
        A21(TOTAL_CONSTANT_MEMORY,              "Constant memory")
//      A21(WARP_SIZE,                          "Warp size")

        A21(MAX_BLOCK_DIM_X,                    "Max blockDim.x")
//      A21(MAX_BLOCK_DIM_Y,                    "Max blockDim.y")
//      A21(MAX_BLOCK_DIM_Z,                    "Max blockDim.z")
        A21(MAX_GRID_DIM_X,                     "Max gridDim.x")
//      A21(MAX_GRID_DIM_Y,                     "Max gridDim.y")
//      A21(MAX_GRID_DIM_Z,                     "Max gridDim.z")
//      A40(MAXIMUM_TEXTURE1D_WIDTH,            "Max tex1D.x")
//      A40(MAXIMUM_TEXTURE2D_WIDTH,            "Max tex2D.x")
//      A40(MAXIMUM_TEXTURE2D_HEIGHT,           "Max tex2D.y")
//      A40(MAXIMUM_TEXTURE3D_WIDTH,            "Max tex3D.x")
//      A40(MAXIMUM_TEXTURE3D_HEIGHT,           "Max tex3D.y")
//      A40(MAXIMUM_TEXTURE3D_DEPTH,            "Max tex3D.z")
//      A40(MAXIMUM_TEXTURE1D_LAYERED_WIDTH,    "Max layerTex1D.x")
//      A40(MAXIMUM_TEXTURE1D_LAYERED_LAYERS,   "Max layerTex1D.y")
//      A40(MAXIMUM_TEXTURE2D_LAYERED_WIDTH,    "Max layerTex2D.x")
//      A40(MAXIMUM_TEXTURE2D_LAYERED_HEIGHT,   "Max layerTex2D.y")
//      A40(MAXIMUM_TEXTURE2D_LAYERED_LAYERS,   "Max layerTex2D.z")
//      A40(MAXIMUM_TEXTURE2D_ARRAY_WIDTH,      "Max array.x")
//      A40(MAXIMUM_TEXTURE2D_ARRAY_HEIGHT,     "Max array.y")
//      A40(MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES,  "Max array.z")

//      A21(MAX_PITCH,                          "Max memcopy pitch")
//      A21(TEXTURE_ALIGNMENT,                  "Texture alignment")
//      A40(SURFACE_ALIGNMENT,                  "Surface alignment")

        A40(CONCURRENT_KERNELS,                 "Concurrent launches supported")
        A21(GPU_OVERLAP,                        "Concurrent memcopy supported")
        A40(ASYNC_ENGINE_COUNT,                 "Max concurrent memcopies")
//      A40(KERNEL_EXEC_TIMEOUT,                "Kernel launch time limited")
//      A40(INTEGRATED,                         "Integrated with host memory")
        A40(UNIFIED_ADDRESSING,                 "Unified addressing supported")
        A40(CAN_MAP_HOST_MEMORY,                "Can map host memory")
        A40(ECC_ENABLED,                        "ECC enabled")

//      A40(TCC_DRIVER,                         "Driver is TCC")
//      A40(COMPUTE_MODE,                       "Compute exclusivity mode")

//      A40(PCI_BUS_ID,                         "PCI bus ID")
//      A40(PCI_DEVICE_ID,                      "PCI device ID")
//      A40(PCI_DOMAIN_ID,                      "PCI domain ID")

#undef A21
#undef A40
    };

    char name[256];
    int major;
    int minor;
    size_t memory;

    checkError("cuDeviceGetName", cuDeviceGetName(name, FW_ARRAY_SIZE(name) - 1, device));
    checkError("cuDeviceComputeCapability", cuDeviceComputeCapability(&major, &minor, device));
    checkError("cuDeviceTotalMem", cuDeviceTotalMem(&memory, device));
    name[FW_ARRAY_SIZE(name) - 1] = '\0';

    printf("\n");
    char deviceIdStr[16];
    sprintf( deviceIdStr, "CUDA device %d", device);
    printf("%-32s%s\n",deviceIdStr, name);
        
    printf("%-32s%s\n", "---", "---");
    
    int version = getDriverVersion();
    printf("%-32s%d.%d\n", "CUDA driver API version", version/10, version%10);
    printf("%-32s%d.%d\n", "Compute capability", major, minor);
    printf("%-32s%.0f megs\n", "Total memory", (F32)memory * exp2(-20));

    for (int i = 0; i < (int)FW_ARRAY_SIZE(attribs); i++)
    {
        int value;
        if (cuDeviceGetAttribute(&value, attribs[i].attrib, device) == CUDA_SUCCESS)
            printf("%-32s%d\n", attribs[i].name, value);
    }
    printf("\n");
}