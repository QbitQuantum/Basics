static inline HGLRC createContext(HDC hdc, HGLRC shared)
{
    HGLRC result = wglCreateContext(hdc);
    if (!result) {
        qErrnoWarning("%s: wglCreateContext failed.", __FUNCTION__);
        return 0;
    }
    if (shared && !wglShareLists(shared, result))
        qErrnoWarning("%s: wglShareLists() failed.", __FUNCTION__);
    return result;
}