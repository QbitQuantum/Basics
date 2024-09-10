void swapBuffers(EGLNativeInternalDisplayType display,EGLNativeSurfaceType srfc){
    if(srfc && !SwapBuffers(srfc->getDC())) {
        DWORD err = GetLastError();
    }
}