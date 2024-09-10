/*
    Tokens:
    ARCH        Build architecture (x86_64)
    CC          Compiler (cc)
    DEBUG       Debug compilation options (-g, -Zi -Od)
    INC         Include directory out/inc
    LIB         Library directory (out/lib, xcode/VS: out/bin)
    LIBS        Libraries required to link with ESP
    OBJ         Name of compiled source (out/lib/view-MD5.o)
    OUT         Output module (view_MD5.dylib)
    SHLIB       Host Shared library (.lib, .so)
    SHOBJ       Host Shared Object (.dll, .so)
    SRC         Source code for view or controller (already templated)
    TMP         Temp directory
    VS          Visual Studio directory
    WINSDK      Windows SDK directory
 */
char *espExpandCommand(cchar *command, cchar *source, cchar *module)
{
    MprBuf      *buf;
    MaAppweb    *appweb;
    cchar       *cp, *out;
    char        *tmp;
    
#if BLD_WIN_LIKE
    cchar   *path;
    path = 0;
#endif

    if (command == 0) {
        return 0;
    }
    out = mprTrimPathExt(module);
    buf = mprCreateBuf(-1, -1);
    appweb = MPR->appwebService;

    for (cp = command; *cp; ) {
		if (*cp == '$') {
            if (matchToken(&cp, "${ARCH}")) {
                /* Build architecture */
                mprPutStringToBuf(buf, appweb->hostArch);

#if BLD_WIN_LIKE
            } else if (matchToken(&cp, "${WINSDK}")) {
                path = mprReadRegistry("HKLM\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows", "CurrentInstallFolder");
				path = strim(path, "\\", MPR_TRIM_END);
                mprPutStringToBuf(buf, path);

            } else if (matchToken(&cp, "${VS}")) {
                path = mprGetPathParent(mprGetPathParent(getenv("VS100COMNTOOLS")));
                mprPutStringToBuf(buf, mprGetPortablePath(path));
#endif
                
            } else if (matchToken(&cp, "${CC}")) {
                /* Compiler */
#if BLD_WIN_LIKE
                //  MOB - what about cross compilation
                path = mprJoinPath(mprGetPathParent(mprGetPathParent(getenv("VS100COMNTOOLS"))), "VC/bin/cl.exe");
                mprPutStringToBuf(buf, mprGetPortablePath(path));
#else
                mprPutStringToBuf(buf, BLD_CC);
#endif
            } else if (matchToken(&cp, "${DEBUG}")) {
                mprPutStringToBuf(buf, ESP_DEBUG);

            } else if (matchToken(&cp, "${INC}")) {
                /* Include directory (out/inc) */
                mprPutStringToBuf(buf, mprResolvePath(mprGetAppDir(), "inc"));

            } else if (matchToken(&cp, "${LIB}")) {
                /* Library directory. IDE's use bin dir */
                mprPutStringToBuf(buf, getOutDir(BLD_LIB_NAME));

            } else if (matchToken(&cp, "${LIBS}")) {
                /* Required libraries to link. These may have nested ${TOKENS} */
                mprPutStringToBuf(buf, espExpandCommand(ESP_LIBS, source, module));

            } else if (matchToken(&cp, "${OBJ}")) {
                /* Output object with extension (.o) */
                mprPutStringToBuf(buf, mprJoinPathExt(out, BLD_OBJ));

            } else if (matchToken(&cp, "${OUT}")) {
                /* Output modules */
                mprPutStringToBuf(buf, out);

            } else if (matchToken(&cp, "${SHLIB}")) {
                /* .lib */
                mprPutStringToBuf(buf, appweb->hostOs);

            } else if (matchToken(&cp, "${SHOBJ}")) {
                /* .dll */
#ifdef BLD_HOST_SHOBJ
                //  MOB - need this for bit
                mprPutStringToBuf(buf, BLD_HOST_SHOBJ);
#else
                mprPutStringToBuf(buf, BLD_SHOBJ);
#endif

            } else if (matchToken(&cp, "${SRC}")) {
                /* View (already parsed into C code) or controller source */
                mprPutStringToBuf(buf, source);

            } else if (matchToken(&cp, "${TMP}")) {
#if BLD_WIN_LIKE
                if ((tmp = getenv("TMP")) == 0) {
                    tmp = getenv("TEMP");
                }
#else
                tmp = getenv("TMPDIR");
#endif
                mprPutStringToBuf(buf, tmp ? tmp : ".");
#ifdef WIND_BASE
            } else if (matchToken(&cp, "${WIND_BASE}")) {
                mprPutStringToBuf(buf, WIND_BASE);
#endif
#ifdef WIND_HOME
            } else if (matchToken(&cp, "${WIND_HOME}")) {
                mprPutStringToBuf(buf, WIND_HOME);
#endif
#ifdef WIND_HOST_TYPE

            } else if (matchToken(&cp, "${WIND_HOST_TYPE}")) {
                mprPutStringToBuf(buf, WIND_HOST_TYPE);
#endif
#ifdef WIND_PLATFORM
            } else if (matchToken(&cp, "${WIND_PLATFORM}")) {
                mprPutStringToBuf(buf, WIND_PLATFORM);

#endif
#ifdef WIND_GNU_PATH
            } else if (matchToken(&cp, "${WIND_GNU_PATH}")) {
                mprPutStringToBuf(buf, WIND_GNU_PATH);
#endif

            } else {
                mprPutCharToBuf(buf, *cp++);
            }
        } else {
            mprPutCharToBuf(buf, *cp++);
        }
    }
    mprAddNullToBuf(buf);
    return sclone(mprGetBufStart(buf));
}