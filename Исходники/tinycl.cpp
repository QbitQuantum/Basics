void CL::TinyCL::selectInteropDevice(DEVICE dev, bool profile) {
    try {
        //We assume only the first device and platform will be used
        //This is after all a lazy implementation
        cl::Platform::get(&mPlatforms);
        //Query the devices for the type desired
        mPlatforms.at(0).getDevices(static_cast<cl_device_type>(dev), &mDevices);
#ifdef _WIN32
        cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)(mPlatforms[0])(),
            0
        };
#elif defined(__linux__)
        cl_context_properties properties[] = {
            CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties)glXGetCurrentDisplay(),
            CL_CONTEXT_PLATFORM, (cl_context_properties)(mPlatforms[0])(),
            0
        };
#elif defined(__APPLE__)
        CGLContextObj glContext = CGLGetCurrentContext();
        CGLShareGroupObj shareGroup = CGLGetShareGroup(glContext);
        cl_context_properties properties[] = {
            CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
            (cl_context_properties)shareGroup,
        };
#endif

        mContext = cl::Context(mDevices, properties);
        //Grab the OpenGL device
        mDevices = mContext.getInfo<CL_CONTEXT_DEVICES>();
        if (profile)
            mQueue = cl::CommandQueue(mContext, mDevices.at(0), CL_QUEUE_PROFILING_ENABLE);
        else
            mQueue = cl::CommandQueue(mContext, mDevices.at(0));

        std::cout << "OpenCL Info:"
                  << "\nName: " << mDevices.at(0).getInfo<CL_DEVICE_NAME>()
                  << "\nVendor: " << mDevices.at(0).getInfo<CL_DEVICE_VENDOR>()
                  << "\nDriver Version: " << mDevices.at(0).getInfo<CL_DRIVER_VERSION>()
                  << "\nDevice Profile: " << mDevices.at(0).getInfo<CL_DEVICE_PROFILE>()
                  << "\nDevice Version: " << mDevices.at(0).getInfo<CL_DEVICE_VERSION>()
                  << "\nMax Work Group Size: " << mDevices.at(0).getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()
                  << std::endl;
    }
    catch (const cl::Error &e) {
        std::cout << "Error selecting GL interop device: " << e.what()
                  << " code: " << e.err() << std::endl;
        throw e;
    }

}