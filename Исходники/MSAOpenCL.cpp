	void OpenCL::setupFromOpenGL(int deviceNumber) {
		ofLog(OF_LOG_VERBOSE, "OpenCL::setupFromOpenGL ");

		if(isSetup) {
			ofLog(OF_LOG_VERBOSE, "... already setup. returning");
			return;
		}

		if(deviceInfo.size() == 0) getDeviceInfos(CL_DEVICE_TYPE_GPU);
		deviceNumber = (deviceNumber + getNumDevices()) % getNumDevices();
		clDevice = deviceInfo[deviceNumber].clDeviceId;
		cl_platform_id clPlatformID = deviceInfo[deviceNumber].clPlatformId;

		cl_int err;

#ifdef TARGET_OSX	
		CGLContextObj kCGLContext = CGLGetCurrentContext();
		CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);
		cl_context_properties properties[] = { CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)kCGLShareGroup, 0 };

		clContext = clCreateContext(properties, 0, 0, NULL, NULL, &err);
#elif defined _WIN32
		//aqcuire shared context on windows.
		{
			// TODO: we want to be more specific about the platform,
			// at the moment only the first successful platform is selected. 

			cl_context_properties properties[] = 
			{
				CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(), 
				CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(), 
				CL_CONTEXT_PLATFORM, (cl_context_properties)clPlatformID, 
				0
			};
			ofLogNotice() << "Using OpenCL Platform: 0x" << std::hex << clPlatformID;
			ofLogNotice() << "Using OpenCL Device: 0x" << std::hex << clDevice;

			clContext = clCreateContext(properties, 1, &clDevice, NULL, NULL, &err);
			ofLogNotice() <<  "Created OpenCL context: " << (err == CL_SUCCESS ? "SUCCESS" : "ERROR");
		}

#endif
		if(clContext == NULL) {
			ofLog(OF_LOG_ERROR, "Error creating clContext.");
			assert(err != CL_INVALID_PLATFORM);
			assert(err != CL_INVALID_VALUE);
			assert(err != CL_INVALID_DEVICE);
			assert(err != CL_INVALID_DEVICE_TYPE);
			assert(err != CL_DEVICE_NOT_AVAILABLE);
			assert(err != CL_DEVICE_NOT_FOUND);
			assert(err != CL_OUT_OF_HOST_MEMORY);
			assert(false);
		}

		createQueue();
	}	