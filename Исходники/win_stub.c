value stub_swap_buffers(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(result);
#ifdef __unix__
    glXSwapBuffers(gdisplay, gwin);
#endif
#ifdef _WIN32
    wglSwapLayerBuffers(ghDC, WGL_SWAP_MAIN_PLANE);
#endif
    result = Val_unit;
    CAMLreturn(result);
}