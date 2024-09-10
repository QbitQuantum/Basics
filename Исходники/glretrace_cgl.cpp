static void retrace_CGLDestroyPixelFormat(trace::Call &call) {
    if (call.ret->toUInt() != kCGLNoError) {
        return;
    }

    trace::Value & pix = call.argByName("pix");

    PixelFormat *pixelFormat = retrace::asObjPointer<PixelFormat>(call, pix);
    delete pixelFormat;

    retrace::delObj(pix);
}