void StepWorldV3OpenCL(world_t &world, float dt, unsigned n)
{
  // OpenCL setup
  // platform
  std::vector<cl::Platform> platforms;

  cl::Platform::get(&platforms);
  if (platforms.size() == 0)
    throw std::runtime_error("No OpenCL platforms found.");

  std::cerr << "Found " << platforms.size() << " platforms\n";
  for (unsigned i = 0; i < platforms.size(); i++) {
    std::string vendor = platforms[i].getInfo<CL_PLATFORM_VENDOR>();
    std::cerr << "  Platform " << i << " : " << vendor << "\n";
  }

  int selectedPlatform = 0;
  if (getenv("HPCE_SELECT_PLATFORM")) {
    selectedPlatform = atoi(getenv("HPCE_SELECT_PLATFORM"));
  }
  std::cerr << "Choosing platform " << selectedPlatform << "\n";
  cl::Platform platform = platforms.at(selectedPlatform);

  // device
  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
  if (devices.size() == 0) {
    throw std::runtime_error("No opencl devices found.\n");
  }

  std::cerr << "Found " << devices.size() << " devices\n";
  for (unsigned i = 0; i < devices.size(); i++) {
    std::string name = devices[i].getInfo<CL_DEVICE_NAME>();
    std::cerr << "  Device " << i << " : " << name << "\n";
  }

  int selectedDevice = 0;
  if (getenv("HPCE_SELECT_DEVICE")) {
    selectedDevice = atoi(getenv("HPCE_SELECT_DEVICE"));
  }
  std::cerr << "Choosing device " << selectedDevice << "\n";
  cl::Device device = devices.at(selectedDevice);

  // context
  cl::Context context(devices);

  std::string kernelSource = LoadSource("step_world_v3_kernel.cl");

  cl::Program::Sources sources;  // A vector of (data,length) pairs
  sources.push_back(
      std::make_pair(kernelSource.c_str(),
                     kernelSource.size() + 1));  // push on our single string

  cl::Program program(context, sources);
  try { program.build(devices); }
  catch (...)
  {
    for (unsigned i = 0; i < devices.size(); i++) {
      std::cerr << "Log for device " << devices[i].getInfo<CL_DEVICE_NAME>()
                << ":\n\n";
      std::cerr << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[i])
                << "\n\n";
    }
    throw;
  }

  size_t cbBuffer = 4 * world.w * world.h;
  cl::Buffer buffProperties(context, CL_MEM_READ_ONLY, cbBuffer);
  cl::Buffer buffState(context, CL_MEM_READ_ONLY, cbBuffer);
  cl::Buffer buffBuffer(context, CL_MEM_WRITE_ONLY, cbBuffer);

  cl::Kernel kernel(program, "kernel_xy");

  float outer = world.alpha * dt;  // We spread alpha to other cells per time
  float inner = 1 - outer / 4;     // Anything that doesn't spread stays

  kernel.setArg(0, inner);
  kernel.setArg(1, outer);
  kernel.setArg(2, buffState);
  kernel.setArg(3, buffProperties);
  kernel.setArg(4, buffBuffer);

  cl::CommandQueue queue(context, device);

  queue.enqueueWriteBuffer(buffProperties, CL_TRUE, 0, cbBuffer,
                           &world.properties[0]);

  unsigned w = world.w, h = world.h;
  // This is our temporary working space
  std::vector<float> buffer(w * h);

  cl::NDRange offset(0, 0);      // Always start iterations at x=0, y=0
  cl::NDRange globalSize(w, h);  // Global size must match the original loops
  cl::NDRange localSize = cl::NullRange;  // We don't care about local size

  for (unsigned t = 0; t < n; t++) {
    cl::Event evCopiedState;
    queue.enqueueWriteBuffer(buffState, CL_FALSE, 0, cbBuffer, &world.state[0],
                             NULL, &evCopiedState);

    std::vector<cl::Event> kernelDependencies(1, evCopiedState);
    cl::Event evExecutedKernel;
    queue.enqueueNDRangeKernel(kernel, offset, globalSize, localSize,
                               &kernelDependencies, &evExecutedKernel);

    std::vector<cl::Event> copyBackDependencies(1, evExecutedKernel);
    queue.enqueueReadBuffer(buffBuffer, CL_TRUE, 0, cbBuffer, &buffer[0],
                            &copyBackDependencies);

    std::swap(world.state, buffer);
    world.t += dt;  // We have moved the world forwards in time
  }
}