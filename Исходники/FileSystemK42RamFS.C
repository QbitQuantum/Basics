/* virtual */ SysStatusUval
FileSystemK42RamFS::readlink(FileToken fileInfo, char *buf, uval bufsize)
{
    FileInfoK42RamFSSymLink *syml = SINF(fileInfo);
    if (!S_ISLNK(syml->status.st_mode)) {
	return _SERROR(2660, 0, EINVAL);
    }

    char *path;
    uval plen = syml->getPath(path);
    if (plen > bufsize) {
	plen = bufsize; // truncate
    }

    memcpy(buf, path, plen);
    return _SRETUVAL(plen);
}