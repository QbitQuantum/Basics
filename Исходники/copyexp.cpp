int copyExpanded(const char *from, const char *to, bool stats)
{
    Owned<IFile> srcfile = createIFile(from);
    Owned<IFileIO> srcio = srcfile->open(IFOread);
    if (!srcio) {
        printf("ERROR: could not open '%s' for read\n",from);
        doexit(3);
    }
    Owned<ICompressedFileIO> cmpio = createCompressedFileReader(srcio);
    Owned<IFileIOStream>  flzstrm = cmpio?NULL:createFastLZStreamRead(srcio);
    int ret = 0;
    if (cmpio||flzstrm) 
        printCompDetails(from,srcio,cmpio,flzstrm);
    else {
        ret = 1;
        printf("%s is not compressed, size= %"I64F"d\n",from,srcio->size());
    }
    if (!to||!*to)
        return ret;
    Owned<IFile> dstfile = createIFile(to);
    StringBuffer fulldst;
    if (dstfile->isDirectory()==foundYes) {
        dstfile.clear();
        addPathSepChar(fulldst.append(to)).append(pathTail(from));
        to = fulldst.str();
        dstfile.setown(createIFile(to));
    }

    if (dstfile->exists()) {
        printf("ERROR: file '%s' already exists\n",to);
        doexit(4);
    }
    unsigned start;
    unsigned startu;
    if (stats) {
         start = msTick();
         startu = usTick();
    }
    Owned<IFileIO> dstio = dstfile->open(IFOcreate);
    if (!dstio) {
        printf("ERROR: could not open '%s' for write\n",to);
        doexit(5);
    }
#ifdef __linux__
    // this is not really needed in windows - if it is we will have to
    // test the file extension - .exe, .bat

    struct stat info;
    if (stat(from, &info) == 0)  // cannot fail - exception would have been thrown above
        dstfile->setCreateFlags(info.st_mode&(S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH|S_IXUSR|S_IXGRP|S_IXOTH));
#endif
    MemoryAttr mb;
    void * buffer = mb.allocate(BUFFERSIZE);

    offset_t offset = 0;
    try
    {
        loop {
            size32_t got = cmpio.get()?cmpio->read(offset,BUFFERSIZE, buffer):
                (flzstrm?flzstrm->read(BUFFERSIZE, buffer):
                    srcio->read(offset, BUFFERSIZE, buffer));
            if (got == 0)
                break;
            dstio->write(offset, got, buffer);
            offset += got;
        }
    }
    catch (IException *e)
    {
        // try to delete partial copy
        dstio.clear();
        try {
            dstfile->remove();
        }
        catch (IException *e2) {
            StringBuffer s;
            pexception(s.clear().append("Removing partial copy file: ").append(to).str(),e2);
            e2->Release();
        }
        throw e;
    }
    dstio.clear();
    if (stats) 
        printStats(offset,start,startu);
    CDateTime createTime, modifiedTime;
    if (srcfile->getTime(&createTime, &modifiedTime, NULL))
        dstfile->setTime(&createTime, &modifiedTime, NULL);
    printf("copied %s to %s%s\n",from,to,cmpio.get()?" expanding":"");
    return 0;
}