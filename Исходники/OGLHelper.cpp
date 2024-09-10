GLfunction getFuzzyProcAddress(const char * psz)
{
    GLfunction pProc = getProcAddress(psz);
    if (!pProc) {
        string s = string(psz)+"EXT";
        pProc = getProcAddress(s);
    }
    if (!pProc) {
        string s = string(psz)+"ARB";
        pProc = getProcAddress(s);
    }
    if (!pProc) {
        string s = string(psz)+"OES";
        pProc = getProcAddress(s);
    }
    if (!pProc) {
        pProc = invalidGLCall;
    }
    return pProc;
}