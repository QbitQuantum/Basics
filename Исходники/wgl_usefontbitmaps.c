static int
test_function(HDC hdc)
{
    bool pass = true;
    HGLRC ctx;
    GLuint dlist[2] = {100, 101};
    const char *string = "some string";

    ctx = wglCreateContext(hdc);
    if (!ctx) {
        fprintf(stderr, "Failed to create wgl context\n");
        return 1;
    }
    if (!wglMakeCurrent(hdc, ctx)) {
        fprintf(stderr, "Failed to make context current\n");
        return 1;
    }

    /* First, use the #ifdeffed variant of the function */
    wglUseFontBitmaps(hdc, 0, 255, dlist[1]);
    glListBase(dlist[1]);
    glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);

    /* Now, use the specific version, manually. */
#ifdef UNICODE
    wglUseFontBitmapsW(hdc, 0, 255, dlist[2]);
#else
    wglUseFontBitmapsA(hdc, 0, 255, dlist[2]);
#endif
    glListBase(dlist[2]);
    glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(ctx);

    return !pass;
}