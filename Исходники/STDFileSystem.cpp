        FileSystem::status STDFileSystem::_renameFile(const char* src, const char* dest)
        {
            char buffSrc[512];
            _getFullPath(src, buffSrc);

            char buffDest[512];
            _getFullPath(dest, buffDest);

#if __S3E__
            return (s3eFileRename(buffSrc, buffDest) == S3E_RESULT_SUCCESS ? status_ok : status_error);
#elif OXYGINE_EDITOR
            return status_error;
#elif _WIN32
            std::wstring s = utf8tows(buffSrc);
            std::wstring d = utf8tows(buffDest);
            return MoveFileW(s.c_str(), d.c_str()) ? status_ok : status_error;
#else
            return (::rename(buffSrc, buffDest) != -1 ? status_ok : status_error);
#endif
            return status_error;
        }