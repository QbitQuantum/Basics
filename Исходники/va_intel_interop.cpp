static float run(const char* infile, const char* outfile1, const char* outfile2, bool doInterop)
{
    VASurfaceID surface;
    VAStatus status;
    Timer t;

    // initialize CL context for CL/VA interop
    cv::va_intel::ocl::initializeContextFromVA(va::display, doInterop);

    // load input image
    cv::UMat u1 = readImage(infile);
    cv::Size size2 = u1.size();
    status = vaCreateSurfaces(va::display, VA_RT_FORMAT_YUV420, size2.width, size2.height, &surface, 1, NULL, 0);
    CHECK_VASTATUS(status, "vaCreateSurfaces");

    // transfer image into VA surface, make sure all CL initialization is done (kernels etc)
    cv::va_intel::convertToVASurface(va::display, u1, surface, size2);
    cv::va_intel::convertFromVASurface(va::display, surface, size2, u1);
    cv::UMat u2;
    cv::blur(u1, u2, cv::Size(7, 7), cv::Point(-3, -3));

    // measure performance on some image processing
    writeImage(u1, outfile1, doInterop);
    t.start();
    cv::va_intel::convertFromVASurface(va::display, surface, size2, u1);
    cv::blur(u1, u2, cv::Size(7, 7), cv::Point(-3, -3));
    cv::va_intel::convertToVASurface(va::display, u2, surface, size2);
    t.stop();
    writeImage(u2, outfile2, doInterop);

    vaDestroySurfaces(va::display, &surface,1);

    return t.time(Timer::MSEC);
}