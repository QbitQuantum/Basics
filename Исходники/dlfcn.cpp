/**
@Status Caveat
@Notes This function can only find libraries in the root of the current
       package. The mode parameter is ignored. In addition, error information
       is not available on failure.
*/
void* dlopen(const char* path, int mode) {
    try {
        // We can only load libraries from within our own package or any dependent
        // packages, so absolute paths are not much use to us. From whatever path
        // we're given, just strip off everything but the leaf file name and try
        // to load that. This isn't always correct, but it is sometimes correct.

        std::wstring widePath(path, path + strlen(path));

        DWORD pathLength = GetFullPathNameW(widePath.c_str(), 0, nullptr, nullptr);
        auto fullPath = std::make_unique<WCHAR[]>(pathLength);
        LPWSTR fileName = nullptr;

        GetFullPathNameW(widePath.c_str(), pathLength, fullPath.get(), &fileName);

        return LoadPackagedLibrary(fileName, 0);
    } catch (...) {
    }

    return NULL;
}