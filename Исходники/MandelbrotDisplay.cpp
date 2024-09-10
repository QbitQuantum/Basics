int 
main(int argc, char * argv[])
{
    // initalise and run the mandelbrot kernel 
    clMandelbrot.initialize();
    if(clMandelbrot.parseCommandLine(argc, argv))
        return SDK_FAILURE;

    if(clMandelbrot.isDumpBinaryEnabled())
    {
        return clMandelbrot.genBinaryImage();
    }
    else
    {
        int returnVal = clMandelbrot.setup();
        if(returnVal != SDK_SUCCESS)
            return (returnVal == SDK_EXPECTED_FAILURE)? SDK_SUCCESS : SDK_FAILURE;

        if(clMandelbrot.run()!=SDK_SUCCESS)
            return SDK_FAILURE;
        if(clMandelbrot.verifyResults()!=SDK_SUCCESS)
            return SDK_FAILURE;

        // show window if it is not running in quiet mode 
        if(clMandelbrot.showWindow())
        {
            width = clMandelbrot.getWidth();
            height = clMandelbrot.getHeight();
            output = (unsigned char *)clMandelbrot.getPixels();

            initDisplay(argc, argv);
            mainLoopGL();
        }
        cleanup();
    }
    return SDK_SUCCESS;
}