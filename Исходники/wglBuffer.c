HANDLE
CreateBufferRegion(unsigned int buffers)
{
    /* Create the buffer region. */
    HANDLE FBRegion = wglCreateBufferRegionARB(wglGetCurrentDC(), 0, buffers);

    if (FBRegion == 0)
        puts("wglCreateBufferRegionARB Failed");

    return FBRegion;
}