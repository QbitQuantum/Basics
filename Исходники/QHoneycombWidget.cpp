cl_context QHoneycombWidget::CreateContext()
{
  cl_int errNum;
  cl_uint numPlatforms;
  cl_platform_id firstPlatformId;
  cl_context context = NULL;

  // First, select an OpenCL platform to run on.  For this example, we
  // simply choose the first available platform.  Normally, you would
  // query for all available platforms and select the most appropriate one.
  errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
  if (errNum != CL_SUCCESS || numPlatforms <= 0)
  {
    std::cerr << "Failed to find any OpenCL platforms." << std::endl;
    return NULL;
  }

  // Next, create an OpenCL context on the platform.  Attempt to
  // create a GPU-based context, and if that fails, try to create
  // a CPU-based context.
  cl_context_properties contextProperties[] =
  {
#ifdef _WIN32
    CL_CONTEXT_PLATFORM,
    (cl_context_properties)firstPlatformId,
    CL_GL_CONTEXT_KHR,
    (cl_context_properties)wglGetCurrentContext(),
    CL_WGL_HDC_KHR,
    (cl_context_properties)wglGetCurrentDC(),
#elif defined( __GNUC__)
    CL_CONTEXT_PLATFORM, (cl_context_properties)clSelectedPlatformID,
    CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
    CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
#elif defined(__APPLE__) 
    //todo
#endif
    0



  };
  context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,
    NULL, NULL, &errNum);
  if (errNum != CL_SUCCESS)
  {
    std::cout << "Could not create GPU context, trying CPU..." << std::endl;
    context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
      NULL, NULL, &errNum);
    if (errNum != CL_SUCCESS)
    {
      std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
      return NULL;
    }
  }

  return context;
}