void buildOpenCLKernels_tea_leaf_zeqxty_kernel(int xdim0, int xdim1,
                                               int xdim2) {

  // int ocl_fma = OCL_FMA;
  if (!isbuilt_tea_leaf_zeqxty_kernel) {
    buildOpenCLKernels();
    // clSafeCall( clUnloadCompiler() );
    cl_int ret;
    char *source_filename[1] = {(char *)"./OpenCL/tea_leaf_zeqxty_kernel.cl"};

    // Load the kernel source code into the array source_str
    FILE *fid;
    char *source_str[1];
    size_t source_size[1];

    for (int i = 0; i < 1; i++) {
      fid = fopen(source_filename[i], "r");
      if (!fid) {
        fprintf(stderr, "Can't open the kernel source file!\n");
        exit(1);
      }

      source_str[i] = (char *)malloc(4 * 0x1000000);
      source_size[i] = fread(source_str[i], 1, 4 * 0x1000000, fid);
      if (source_size[i] != 4 * 0x1000000) {
        if (ferror(fid)) {
          printf("Error while reading kernel source file %s\n",
                 source_filename[i]);
          exit(-1);
        }
        if (feof(fid))
          printf("Kernel source file %s succesfuly read.\n",
                 source_filename[i]);
        // printf("%s\n",source_str[i]);
      }
      fclose(fid);
    }

    printf("Compiling tea_leaf_zeqxty_kernel %d source -- start \n", OCL_FMA);

    // Create a program from the source
    OPS_opencl_core.program = clCreateProgramWithSource(
        OPS_opencl_core.context, 1, (const char **)&source_str,
        (const size_t *)&source_size, &ret);
    clSafeCall(ret);

    // Build the program
    char buildOpts[255 * 3];
    char *pPath = NULL;
    pPath = getenv("OPS_INSTALL_PATH");
    if (pPath != NULL)
      if (OCL_FMA)
        sprintf(buildOpts, "-cl-mad-enable -DOCL_FMA -I%s/c/include "
                           "-DOPS_WARPSIZE=%d  "
                           "-Dxdim0_tea_leaf_zeqxty_kernel=%d  "
                           "-Dxdim1_tea_leaf_zeqxty_kernel=%d  "
                           "-Dxdim2_tea_leaf_zeqxty_kernel=%d ",
                pPath, 32, xdim0, xdim1, xdim2);
      else
        sprintf(buildOpts, "-cl-mad-enable -I%s/c/include -DOPS_WARPSIZE=%d  "
                           "-Dxdim0_tea_leaf_zeqxty_kernel=%d  "
                           "-Dxdim1_tea_leaf_zeqxty_kernel=%d  "
                           "-Dxdim2_tea_leaf_zeqxty_kernel=%d ",
                pPath, 32, xdim0, xdim1, xdim2);
    else {
      sprintf((char *)"Incorrect OPS_INSTALL_PATH %s\n", pPath);
      exit(EXIT_FAILURE);
    }

    ret = clBuildProgram(OPS_opencl_core.program, 1, &OPS_opencl_core.device_id,
                         buildOpts, NULL, NULL);

    if (ret != CL_SUCCESS) {
      char *build_log;
      size_t log_size;
      clSafeCall(clGetProgramBuildInfo(
          OPS_opencl_core.program, OPS_opencl_core.device_id,
          CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size));
      build_log = (char *)malloc(log_size + 1);
      clSafeCall(clGetProgramBuildInfo(
          OPS_opencl_core.program, OPS_opencl_core.device_id,
          CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL));
      build_log[log_size] = '\0';
      fprintf(
          stderr,
          "=============== OpenCL Program Build Info ================\n\n%s",
          build_log);
      fprintf(stderr,
              "\n========================================================= \n");
      free(build_log);
      exit(EXIT_FAILURE);
    }
    printf("compiling tea_leaf_zeqxty_kernel -- done\n");

    // Create the OpenCL kernel
    OPS_opencl_core.kernel[41] = clCreateKernel(
        OPS_opencl_core.program, "ops_tea_leaf_zeqxty_kernel", &ret);
    clSafeCall(ret);

    isbuilt_tea_leaf_zeqxty_kernel = true;
  }
}