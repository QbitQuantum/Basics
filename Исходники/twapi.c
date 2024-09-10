/*
 * Loads the initialization script from image file resource
 */
TCL_RESULT Twapi_SourceResource(Tcl_Interp *interp, HANDLE dllH, const char *name, int try_file)
{
    HRSRC hres = NULL;
    unsigned char *dataP;
    DWORD sz;
    HGLOBAL hglob;
    int result;
    int compressed;
    Tcl_Obj *pathObj;

    /*
     * Locate the twapi resource and load it if found. First check for
     * compressed type. Then uncompressed.
     */
    compressed = 1;
    hres = FindResourceA(dllH,
                         name,
                         TWAPI_SCRIPT_RESOURCE_TYPE_LZMA);
    if (!hres) {
        hres = FindResourceA(dllH,
                             name,
                             TWAPI_SCRIPT_RESOURCE_TYPE);
        compressed = 0;
    }

    if (hres) {
        sz = SizeofResource(dllH, hres);
        hglob = LoadResource(dllH, hres);
        if (sz && hglob) {
            dataP = LockResource(hglob);
            if (dataP) {
                /* If compressed, we need to uncompress it first */
                if (compressed) {
                    dataP = TwapiLzmaUncompressBuffer(interp, dataP, sz, &sz);
                    if (dataP == NULL)
                        return TCL_ERROR; /* interp already has error */
                }
                
                /* The resource is expected to be UTF-8 (actually strict ASCII) */
                /* TBD - double check use of GLOBAL and DIRECT */
                result = Tcl_EvalEx(interp, (char *)dataP, sz, TCL_EVAL_GLOBAL | TCL_EVAL_DIRECT);
                if (compressed)
                    TwapiLzmaFreeBuffer(dataP);
                if (result == TCL_OK)
                    Tcl_ResetResult(interp);
                return result;
            }
        }
        return Twapi_AppendSystemError(interp, GetLastError());
    }

    if (!try_file) {
        Tcl_AppendResult(interp, "Resource ", name,  " not found.", NULL);
        return TCL_ERROR;
    }    

    /* 
     * No resource found. Try loading from twapi script directory if defined
     * or from the twapi dll install directory
     */
    pathObj = Tcl_GetVar2Ex(interp, "::" TWAPI_TCL_NAMESPACE "::scriptdir",
                            NULL, 0);
    if (pathObj != NULL) {
        pathObj = Tcl_DuplicateObj(pathObj);
        Tcl_AppendToObj(pathObj, "/", 1);
    } else {
        Tcl_ResetResult(interp); /* Since the GetVar may have store error */
        pathObj = TwapiGetInstallDir(interp, dllH);
    }
    if (pathObj == NULL)
        return TCL_ERROR;

    ObjIncrRefs(pathObj);  /* Must before calling any Tcl_FS functions */

    /* This bit of shenanigans is to allow MingW based builds to load
     * twapi modules from files without requiring a resource */
#if defined(__GNUC__)
    if (lstrlenA(name) > 6 && _strnicmp(name, "twapi_", 6) == 0)
        name += 6;
#endif
    Tcl_AppendStringsToObj(pathObj, name, ".tcl", NULL);
    result = Tcl_FSEvalFile(interp, pathObj);
    ObjDecrRefs(pathObj);
    return result;
#if 0
    /* Caller should be doing PkgProvide as appropriate. This function
       is not only called for packages.
    */
    if (result != TCL_OK)
       return result;
    return Tcl_PkgProvide(interp, MODULENAME, MODULEVERSION);
#endif
}