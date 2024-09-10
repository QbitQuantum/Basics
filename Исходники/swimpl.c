BOOL sw_SwapBuffers(HDC hdc, struct wgl_dc_data* dc_data)
{
    struct sw_framebuffer* fb = dc_data->sw_data;
    struct sw_context* sw_ctx = (struct sw_context*)IntGetCurrentDHGLRC();
    
    /* Notify mesa */
    if(sw_ctx)
        _mesa_notifySwapBuffers(&sw_ctx->mesa);
    
    if(!(fb->flags & SW_FB_DOUBLEBUFFERED))
        return TRUE;

    /* Upload to the display */
    return (SetDIBitsToDevice(hdc,
        0,
        0,
        fb->bmi.bmiHeader.biWidth,
        fb->bmi.bmiHeader.biHeight,
        0,
        0,
        0,
        fb->bmi.bmiHeader.biHeight,
        fb->backbuffer.Buffer,
        &fb->bmi,
        DIB_RGB_COLORS) != 0);
}