static IKeyIndex *openKeyPart(CActivityBase *activity, const char *logicalFilename, IPartDescriptor &partDesc)
{
    RemoteFilename rfn;
    partDesc.getFilename(0, rfn);
    StringBuffer filePath;
    rfn.getPath(filePath);
    unsigned crc=0;
    partDesc.getCrc(crc);
    Owned<IDelayedFile> lfile = queryThor().queryFileCache().lookup(*activity, partDesc);
    return createKeyIndex(filePath.str(), crc, *lfile, false, false);
}