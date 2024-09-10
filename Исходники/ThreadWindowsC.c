//----------------------------------------------------------------------------------------
amf_handle AMF_CDECL_CALL amf_load_library(const wchar_t* filename)
{
#if defined(METRO_APP)
    return LoadPackagedLibrary(filename, 0);
#else
    return LoadLibraryW(filename);
#endif
}