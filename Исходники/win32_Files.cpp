    String getDriveFromPath (String path)
    {
        if (path.isNotEmpty() && path[1] == ':' && path[2] == 0)
            path << '\\';

        const size_t numBytes = CharPointer_UTF16::getBytesRequiredFor (path.getCharPointer()) + 4;
        HeapBlock<WCHAR> pathCopy;
        pathCopy.calloc (numBytes, 1);
        path.copyToUTF16 (pathCopy, numBytes);

        if (PathStripToRoot (pathCopy))
            path = static_cast <const WCHAR*> (pathCopy);

        return path;
    }