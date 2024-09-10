 Path MemFileSystem::mapTo(const Path& path)
 {
    String file = mVolume;
    file = Path::Join(file, '/', path.getPath());
    file = Path::Join(file, '/', path.getFileName());
    file = Path::Join(file, '.', path.getExtension());
    return file;
 }