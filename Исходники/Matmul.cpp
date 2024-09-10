int main(int argc, char *argv[]){
 
    std::string line;
    std::string kersource="";
    std::ifstream myfile ("Matmul.cl");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            kersource=kersource+line;
            kersource=kersource+"\n";
        }
        myfile.close();
    }
  
    const char* kernelSource  = kersource.c_str();
    
    unsigned int n = 1000;
 
    // Host input vectors
    float *h_a;
    float *h_b;
    // Host output vector
    float *h_c;
 
    // Device input buffers
    cl::Buffer d_a;
    cl::Buffer d_b;
    // Device output buffer
    cl::Buffer d_c;
    cl::LocalSpaceArg d_bwrk;
 
    // Size, in bytes, of each vector
    size_t bytes = n*n*sizeof (float);
 
    // Allocate memory for each vector on host
    h_a = new float[n*n];
    h_b = new float[n*n];
    h_c = new float[n*n];
 
    // Initialize vectors on host
    for(int i = 0; i < n*n; i++ )
    {
        h_a[i] = 1;
        h_b[i] = 2;
    }
    cl::STRING_CLASS buildlog;
    cl::Program program_;
    std::vector<cl::Device> devices;

    cl_int err = CL_SUCCESS;
    try {
 
        // Query platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.size() == 0) {
            std::cout << "Platform size 0\n";
            return -1;
        }
        

 
        // Get list of devices on default platform and create context
        cl_context_properties properties[] =
           { CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
        cl::Context context(CL_DEVICE_TYPE_CPU, properties);
         devices = context.getInfo<CL_CONTEXT_DEVICES>();


 
        // Create command queue for first device
        cl::CommandQueue queue(context, devices[0], 0, &err);
 
        // Create device memory buffers
        d_a = cl::Buffer(context, CL_MEM_READ_ONLY, bytes);
        d_b = cl::Buffer(context, CL_MEM_READ_ONLY, bytes);
        d_c = cl::Buffer(context, CL_MEM_WRITE_ONLY, bytes);
        d_bwrk = cl::Local(n*sizeof(float));
 
        // Bind memory buffers
        queue.enqueueWriteBuffer(d_a, CL_TRUE, 0, bytes, h_a);
        queue.enqueueWriteBuffer(d_b, CL_TRUE, 0, bytes, h_b);
 
        //Build kernel from source string
        cl::Program::Sources source(1,
            std::make_pair(kernelSource,strlen(kernelSource)));
        program_ = cl::Program(context, source);
        program_.build(devices);

        
        

        std::cout<<"BuildLog: \n"<<buildlog;
        

        // Create kernel object
        cl::Kernel kernel(program_, "multiMat", &err);
 
        // Bind kernel arguments to kernel
        kernel.setArg(0, d_a);
        kernel.setArg(1, d_b);
        kernel.setArg(2, d_c);
        kernel.setArg(3, n);
        kernel.setArg(4,d_bwrk);
 
        // Number of work items in each local work group
        cl::NDRange localSize(64);
        // Number of total work items - localSize must be devisor
        cl::NDRange globalSize((int)(ceil(n/(float)64)*64));
 
        // Enqueue kernel
        cl::Event event;
        queue.enqueueNDRangeKernel(
            kernel,
            cl::NullRange,
            globalSize,
            localSize,
            NULL,
            &event);
 
        // Block until kernel completion
        event.wait();
 
        // Read back d_c
        queue.enqueueReadBuffer(d_c, CL_TRUE, 0, bytes, h_c);
        }
    catch (cl::Error err) 
    {
        std::cerr
        << "ERROR: "<<err.what()<<"("<<err.err()<<")"<<std::endl;

        buildlog = program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0], NULL);
        std::ofstream logfile ("Matmullog.txt");
        logfile<<buildlog;
        logfile.close();
        
    }
    std::cout<<"Global Size side :"<< (int)(ceil(n/(float)64)*64)<<"\n";
 
    // Sum up vector c and print result divided by n, this should equal 1 within error
    float sum = 0;
    for(int i=0; i<n*n; i++)
        sum += h_c[i];
    std::cout<<"final result: "<<sum<<std::endl;

    //std::ofstream outfile ("MatmulAns.txt");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
    //        outfile<<h_c[i*n+j]<<" ";
        }
    //    outfile<<"\n";
    }
    //outfile.close();
    // Release host memory
    delete(h_a);
    delete(h_b);
    delete(h_c);
 
    return 0;
}