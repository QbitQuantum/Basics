// file system stuff
bool exists(const u::string &inputPath, pathType type) {
    u::string &&path = u::fixPath(inputPath);
    if (type == kFile)
        return dir::isFile(path);

    // type == kDirectory
#if defined(_WIN32)
    const DWORD attribs = GetFileAttributesA(inputPath.c_str());
    if (attribs == INVALID_FILE_ATTRIBUTES)
        return false;
    if (!(attribs & FILE_ATTRIBUTE_DIRECTORY))
        return false;
#else
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
        return false; // Couldn't stat directory
    if (!(info.st_mode & S_IFDIR))
        return false; // Not a directory
#endif
    return true;
}