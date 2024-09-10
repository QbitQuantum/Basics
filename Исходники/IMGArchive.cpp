IMGArchive::IMGArchive(const File& file, int mode)
    : mode(mode)
{
    const FilePath* path = file.getPath();
    FileContentType type = file.guessContentType();

    if (type == CONTENT_TYPE_DIR) {
        char* imgFilePath = new char[path->toString().length() + 1];
        int basePathLen = path->toString().length() - 3;
        strncpy(imgFilePath, path->toString().get(), basePathLen);
        strcpy(imgFilePath+basePathLen, "img");
        File imgFile(imgFilePath);
        delete[] imgFilePath;

        if ((mode & ReadOnly)  !=  0) {
            dirStream = file.openInputStream(istream::binary);
            imgStream = imgFile.openInputStream(istream::binary);
        } else {
            dirStream = file.openInputOutputStream(iostream::binary);
            imgStream = file.openInputOutputStream(iostream::binary);
        }

        readHeader();
    } else if (type == CONTENT_TYPE_IMG) {
        if ((mode & ReadOnly)  !=  0) {
            imgStream = file.openInputStream(istream::binary);
        } else {
            imgStream = file.openInputOutputStream(iostream::binary);
        }

        if (guessIMGVersion(imgStream, true) == VER2) {
            dirStream = imgStream;
            readHeader();
        } else {
            char* dirFilePath = new char[path->toString().length() + 1];
            int basePathLen = path->toString().length() - 3;
            strncpy(dirFilePath, path->toString().get(), basePathLen);
            strcpy(dirFilePath+basePathLen, "dir");
            File dirFile(dirFilePath);
            delete[] dirFilePath;

            if ((mode & ReadOnly)  !=  0) {
                dirStream = dirFile.openInputStream(istream::binary);
            } else {
                dirStream = dirFile.openInputOutputStream(istream::binary);
            }

            readHeader();
        }
    } else {
        throw IMGException("File name is neither an IMG nor a DIR file", __FILE__, __LINE__);
    }
}