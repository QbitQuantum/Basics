TemporaryFile::TemporaryFile(const std::string& parentDirectory, const std::string& contents)
{
    char fileName[L_tmpnam];
    tmpnam_s(fileName, L_tmpnam);

    std::string filePath = parentDirectory + fileName;

    FILE* file = nullptr;
    errno_t result = fopen_s(&file, filePath.c_str(), "w");
    if (result != 0)
        ThrowError("fopen", perror);

    if (fputs(contents.c_str(), file) == EOF)
        ThrowError("fputs", ferror);

    fclose(file);

    m_Name = fileName;
}