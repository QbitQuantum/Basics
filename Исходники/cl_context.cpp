void cl_context::init()
{
    // OpenCL
    try
    {
        // Get available platforms
        vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        LOG_INFO<<platforms.front().getInfo<CL_PLATFORM_VERSION>();

        // context sharing is OS specific
#if defined (__APPLE__) || defined(MACOSX)
        CGLContextObj curCGLContext = CGLGetCurrentContext();
        CGLShareGroupObj curCGLShareGroup = CGLGetShareGroup(curCGLContext);

        cl_context_properties properties[] =
        {
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
            (cl_context_properties)curCGLShareGroup,
            0
        };
#elif defined WIN32
        cl_context_properties properties[] =
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(),
            0
        };
#else
        cl_context_properties properties[] =
        {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
            CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(),
            0
        };
#endif

        m_context = cl::Context(CL_DEVICE_TYPE_GPU, properties);

        // Get a list of devices on this platform
        vector<cl::Device> devices = m_context.getInfo<CL_CONTEXT_DEVICES>();
        m_device = devices[0];

        // Create a command queue and use the first device
        m_queue = cl::CommandQueue(m_context, m_device);

    }
    catch(cl::Error &error)
    {
        LOG_ERROR << error.what() << "(" << oclErrorString(error.err()) << ")";
    }
}