    Redirection(FILE* f)
        : fi(Base::FileInfo::getTempFileName()), file(f)
    {
#ifdef WIN32
        _wfreopen(fi.toStdWString().c_str(),L"w",file);
#else
        freopen(fi.filePath().c_str(),"w",file);
#endif
    }