CString sharedResourcesPath()
{
    static CString cachedPath;
    if (!cachedPath.isNull())
        return cachedPath;

#if OS(WINDOWS)
    HMODULE hmodule = 0;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<char*>(sharedResourcesPath), &hmodule);

    GUniquePtr<gchar> runtimeDir(g_win32_get_package_installation_directory_of_module(hmodule));
    GUniquePtr<gchar> dataPath(g_build_filename(runtimeDir.get(), "share", "webkitgtk-" WEBKITGTK_API_VERSION_STRING, NULL));
#else
    GUniquePtr<gchar> dataPath(g_build_filename(DATA_DIR, "webkitgtk-" WEBKITGTK_API_VERSION_STRING, NULL));
#endif

    cachedPath = dataPath.get();
    return cachedPath;
}