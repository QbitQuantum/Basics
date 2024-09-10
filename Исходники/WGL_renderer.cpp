void wgl_FindBestPF(HDC hDC, int *nRegularFormat, int *nMSFormat)
{	*nRegularFormat = 0;
	*nMSFormat = 0;

	// easy check, just look for the entrypoint
	if(gltIsWGLExtSupported(hDC, "WGL_ARB_pixel_format"))
		if(wglGetPixelFormatAttribivARB == NULL)
			wglGetPixelFormatAttribivARB = (PFNWGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");

    // First try to use new extended wgl way
    if(wglGetPixelFormatAttribivARB != NULL)
        {
        // Only care about these attributes
        int nBestMS = 0;
        int i;
        int iResults[9];
        int iAttributes [9] = {	WGL_SUPPORT_OPENGL_ARB, // 0
								WGL_ACCELERATION_ARB,   // 1
								WGL_DRAW_TO_WINDOW_ARB, // 2
								WGL_DOUBLE_BUFFER_ARB,  // 3
								WGL_PIXEL_TYPE_ARB,     // 4
								WGL_DEPTH_BITS_ARB,     // 5
								WGL_STENCIL_BITS_ARB,   // 6
								WGL_SAMPLE_BUFFERS_ARB, // 7
								WGL_SAMPLES_ARB}; 	    // 8

        // How many pixelformats are there?
        int nFormatCount[] = { 0 };
        int attrib[] = { WGL_NUMBER_PIXEL_FORMATS_ARB };
        wglGetPixelFormatAttribivARB(hDC, 1, 0, 1, attrib, nFormatCount);

        // Loop through all the formats and look at each one
        for(i = 0; i < nFormatCount[0]; i++)
            {
            // Query pixel format
            wglGetPixelFormatAttribivARB(hDC, i+1, 0, 10, iAttributes, iResults);

            // Match? Must support OpenGL AND be Accelerated AND draw to Window
            if(iResults[0] == 1 && iResults[1] == WGL_FULL_ACCELERATION_ARB && iResults[2] == 1)
            if(iResults[3] == 1)                    // Double buffered
            if(iResults[4] == WGL_TYPE_RGBA_ARB)    // Full Color
            if(iResults[5] >= 16)                   // Any Depth greater than 16
            if(iResults[6] > 0)                     // Any Stencil depth (not zero)
                {
                // We have a candidate, look for most samples if multisampled
                if(iResults[7] == 1)	            // Multisampled
                    {
                    if(iResults[8] > nBestMS)       // Look for most samples
                        {
                        *nMSFormat = i;			// Multisamples
                        nBestMS = iResults[8];	// Looking for the best
                        }
                    }
                else // Not multisampled
                    {
                    // Good enough for "regular". This will fall through
                    *nRegularFormat = i;
                    }
                }
            }
        }
    else
        {
        // Old fashioned way...
        // or multisample
        PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,      // Full color
        32,                 // Color depth
        0,0,0,0,0,0,0,      // Ignored
        0,0,0,0,            // Accumulation buffer
        24,                 // Depth bits
        8,                  // Stencil bits
        0,0,0,0,0,0 };      // Some used, some not

        *nRegularFormat = ChoosePixelFormat(hDC, &pfd);
	}
}