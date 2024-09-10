boolean FileBrowser::IsADirectory(const char* path) {
    return dir->IsADirectory(Normalize(path));
}