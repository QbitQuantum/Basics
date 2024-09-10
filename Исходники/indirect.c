static GLboolean glWinCopyContext(__GLcontext *dst, const __GLcontext *src,
                                   GLuint mask)
{
    BOOL ret;

    GLWIN_DEBUG_MSG("glWinCopyContext\n");
    

    
    ret = wglCopyContext(src->ctx, dst->ctx, mask);
    if (!ret) 
    {
        ErrorF("wglCopyContext error: %s\n", glWinErrorMessage());
        return GL_FALSE;
    }

    return GL_TRUE;
}