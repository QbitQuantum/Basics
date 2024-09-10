static void vigs_gl_backend_wgl_destroy(struct vigs_backend *backend)
{
    struct vigs_gl_backend_wgl *gl_backend_wgl = (struct vigs_gl_backend_wgl*)backend;

    vigs_gl_backend_cleanup(&gl_backend_wgl->base);

    gl_backend_wgl->wglDeleteContext(gl_backend_wgl->ctx);
    gl_backend_wgl->wglDeleteContext(gl_backend_wgl->read_pixels_ctx);
    gl_backend_wgl->wglReleasePbufferDCARB(gl_backend_wgl->sfc, gl_backend_wgl->sfc_dc);
    gl_backend_wgl->wglDestroyPbufferARB(gl_backend_wgl->sfc);
    gl_backend_wgl->wglReleasePbufferDCARB(gl_backend_wgl->read_pixels_sfc, gl_backend_wgl->read_pixels_sfc_dc);
    gl_backend_wgl->wglDestroyPbufferARB(gl_backend_wgl->read_pixels_sfc);

    ReleaseDC(gl_backend_wgl->win, gl_backend_wgl->dc);
    DestroyWindow(gl_backend_wgl->win);

    FreeLibrary(gl_backend_wgl->handle);

    vigs_backend_cleanup(&gl_backend_wgl->base.base);

    g_free(gl_backend_wgl);

    UnregisterClassA((LPCTSTR)VIGS_WGL_WIN_CLASS, NULL);

    VIGS_LOG_DEBUG("destroyed");
}