void maxcoinMiner_openCL_generateOrUpdateKernel()
{
	if( maxcoinOpenCLKernelInited )
		return;
	maxcoinOpenCLKernelInited = true;
	printf("Compiling OpenCL kernel...\n");

	char* kernel_src = (char*)malloc(1024*512);
	strcpy(kernel_src, "");

	cl_int clerr = 0;
	// init input buffer
	maxcoinGPU.buffer_blockInputData = malloc(80+8); // endian swapped block data + share target attached at the end
	memset(maxcoinGPU.buffer_blockInputData, 0x00, 80+8);
	maxcoinGPU.clBuffer_blockInputData = clCreateBuffer(openCL_getActiveContext(), CL_MEM_READ_WRITE, 88, maxcoinGPU.buffer_blockInputData, &clerr);
	// init output buffer
	sint32 outputBlocks = 256;
	maxcoinGPU.buffer_nonceOutputData = malloc(outputBlocks*4*sizeof(uint32));
	memset(maxcoinGPU.buffer_nonceOutputData, 0x00, outputBlocks*4*sizeof(uint32));
	maxcoinGPU.clBuffer_nonceOutputData = clCreateBuffer(openCL_getActiveContext(), CL_MEM_READ_WRITE, outputBlocks*4*sizeof(uint32), maxcoinGPU.buffer_nonceOutputData, &clerr);

	maxcoinMiner_openCL_appendKeccakFunction(kernel_src);

	strcat(kernel_src, "__kernel void xptMiner_cl_maxcoin_keccak(__global unsigned long *blockData, __global unsigned int *nonceIndexOut)\r\n");
	strcat(kernel_src, "{\r\n");

	strcat(kernel_src, 
	"unsigned long nonceAndBits = blockData[9] & 0x00000000FFFFFFFF;\r\n"
	"unsigned long shareTarget = blockData[10];\r\n"
	"nonceIndexOut[get_local_id(0)] = 0xFFFFFFFF;\r\n"

	"nonceAndBits += 0x100000000UL*0x1000UL*(unsigned long)get_local_id(0);\r\n"
	
	//"nonceAndBits = 0x01f94bdb00000000UL;\r\n"

	"for(int i=0; i<0x1000; i++) {\r\n"
	//"for(int i=0; i<1; i++) {\r\n"
	//"if( keccak256_maxcoin_opt_v(blockData, nonceAndBits) < shareTarget ) nonceIndexOut[0] = nonceAndBits>>32;\r\n"
	"if( keccak256_maxcoin_opt_v(blockData, nonceAndBits) < 0x0040000000000000UL ) nonceIndexOut[get_local_id(0)] = nonceAndBits>>32;\r\n"
	"nonceAndBits += 0x100000000UL;\r\n"
	"}\r\n");

	strcat(kernel_src, "}\r\n");

	const char* source = kernel_src;
	size_t src_size = strlen(kernel_src);
	cl_program program = clCreateProgramWithSource(openCL_getActiveContext(), 1, &source, &src_size, &clerr);
	if(clerr != CL_SUCCESS)
		printf("Error creating OpenCL program\n");
	// builds the program
	clerr = clBuildProgram(program, 1, openCL_getActiveDeviceID(), NULL, NULL, NULL);
	if(clerr != CL_SUCCESS)
		printf("Error compiling OpenCL program\n");
	// shows the log
	char* build_log;
	size_t log_size;
	// First call to know the proper size
	clGetProgramBuildInfo(program, *openCL_getActiveDeviceID(), CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	build_log = (char*)malloc(log_size+1);
	memset(build_log, 0x00, log_size+1);
	// Second call to get the log
	clGetProgramBuildInfo(program, *openCL_getActiveDeviceID(), CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
	build_log[log_size] = '\0';
	puts(build_log);
	free(build_log);

	maxcoinGPU.kernel_keccak = clCreateKernel(program, "xptMiner_cl_maxcoin_keccak", &clerr);

	clerr = clSetKernelArg(maxcoinGPU.kernel_keccak, 0, sizeof(cl_mem), &maxcoinGPU.clBuffer_blockInputData);
	clerr = clSetKernelArg(maxcoinGPU.kernel_keccak, 1, sizeof(cl_mem), &maxcoinGPU.clBuffer_nonceOutputData);

	free(kernel_src);
}