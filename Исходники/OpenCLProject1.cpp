float actual_main(int argc, TCHAR* argv[], int DIMENSION){
    cl_int err;
    ocl_args_d_t ocl;
    cl_device_type deviceType = CL_DEVICE_TYPE_GPU;

    LARGE_INTEGER perfFrequency;
    LARGE_INTEGER performanceCountNDRangeStart;
    LARGE_INTEGER performanceCountNDRangeStop;

	
    cl_uint arrayWidth  = DIMENSION;
    cl_uint arrayHeight = DIMENSION;

    //initialize Open CL objects (context, queue, etc.)
    if (CL_SUCCESS != SetupOpenCL(&ocl, deviceType))
    {
        return -1;
    }

    // allocate working buffers. 
    // the buffer should be aligned with 4K page and size should fit 64-byte cached line
    cl_uint optimizedSize = ((sizeof(cl_int) * arrayWidth * arrayHeight - 1)/64 + 1) * 64;
    cl_int* inputA  = (cl_int*)_aligned_malloc(optimizedSize, 4096);
    cl_int* inputB  = (cl_int*)_aligned_malloc(optimizedSize, 4096);
    cl_int* outputC = (cl_int*)_aligned_malloc(optimizedSize, 4096);
    if (NULL == inputA || NULL == inputB || NULL == outputC)
    {
        LogError("Error: _aligned_malloc failed to allocate buffers.\n");
        return -1;
    }

    //random input
    generateInput(inputA, arrayWidth, arrayHeight);
    generateInput(inputB, arrayWidth, arrayHeight);

    // Create OpenCL buffers from host memory
    // These buffers will be used later by the OpenCL kernel
    if (CL_SUCCESS != CreateBufferArguments(&ocl, inputA, inputB, outputC, arrayWidth, arrayHeight))
    {
        return -1;
    }

     // Create and build the OpenCL program
    if (CL_SUCCESS != CreateAndBuildProgram(&ocl))
    {
        return -1;
    }

    // Program consists of kernels.
    // Each kernel can be called (enqueued) from the host part of OpenCL application.
    // To call the kernel, you need to create it from existing program.
    ocl.kernel = clCreateKernel(ocl.program, "Mul", &err);
    if (CL_SUCCESS != err)
    {
        LogError("Error: clCreateKernel returned %s\n", TranslateOpenCLError(err));
        return -1;
    }

    // Passing arguments into OpenCL kernel.
    if (CL_SUCCESS != SetKernelArguments(&ocl))
    {
        return -1;
    }

    // Regularly you wish to use OpenCL in your application to achieve greater performance results
    // that are hard to achieve in other ways.
    // To understand those performance benefits you may want to measure time your application spent in OpenCL kernel execution.
    // The recommended way to obtain this time is to measure interval between two moments:
    //   - just before clEnqueueNDRangeKernel is called, and
    //   - just after clFinish is called
    // clFinish is necessary to measure entire time spending in the kernel, measuring just clEnqueueNDRangeKernel is not enough,
    // because this call doesn't guarantees that kernel is finished.
    // clEnqueueNDRangeKernel is just enqueue new command in OpenCL command queue and doesn't wait until it ends.
    // clFinish waits until all commands in command queue are finished, that suits your need to measure time.
    bool queueProfilingEnable = true;
    if (queueProfilingEnable)
        QueryPerformanceCounter(&performanceCountNDRangeStart);
    // Execute (enqueue) the kernel
    if (CL_SUCCESS != ExecuteAddKernel(&ocl, arrayWidth, arrayHeight))
    {
        return -1;
    }
    if (queueProfilingEnable)
        QueryPerformanceCounter(&performanceCountNDRangeStop);

    // The last part of this function: getting processed results back.
    // use map-unmap sequence to update original memory area with output buffer.
    ReadAndVerify(&ocl, arrayWidth, arrayHeight, inputA, inputB);

    // retrieve performance counter frequency
    if (queueProfilingEnable)
    {
        QueryPerformanceFrequency(&perfFrequency);
        //LogInfo("NDRange performance counter time %f ms.\n",
          //  1000.0f*(float)(performanceCountNDRangeStop.QuadPart - performanceCountNDRangeStart.QuadPart) / (float)perfFrequency.QuadPart);
    }

    _aligned_free(inputA);
    _aligned_free(inputB);
    _aligned_free(outputC);

	return 1e6*(float)(performanceCountNDRangeStop.QuadPart - performanceCountNDRangeStart.QuadPart) / (float)perfFrequency.QuadPart;
}