static bool physicalPartCopy(IFile *from,const char *tofile, Owned<IException> &exc, StringBuffer *tmpname)
{
    StringBuffer tmpnamestr;
    if (!tmpname)
        tmpname = &tmpnamestr;
    tmpname->append(tofile).append("__");
    size32_t l = tmpname->length();
    genUUID(*tmpname,true); // true for windows
    StringAttr uuid(tmpname->str()+l);
    tmpname->append(".tmp");
    RemoteFilename tmpfn;
    tmpfn.setRemotePath(tmpname->str());
    //unsigned lastpc;
#ifdef LOG_PART_COPY
    PROGLOG("start physicalPartCopy(%s,%s)",from->queryFilename(),tmpname->str());
#endif
    try {
        recursiveCreateDirectoryForFile(tmpname->str());
        while(!asyncCopyFileSection(
                uuid,
                from,
                tmpfn,
                (offset_t)-1, // creates file
                0,
                (offset_t)-1, // all file
                NULL,
                PHYSICAL_COPY_POLL_TIME)) {
            // Abort check TBD
        }
    }
    catch (IException *e) {
        EXCLOG(e,"SingleFileCopy: File copy error");
        if (exc)
            exc.setown(e);
        else
            e->Release();
    }
    Owned<IFile> f = createIFile(tmpfn);
    if (!exc.get()&&(tmpnamestr.length()!=0)) {
        try {
#ifdef LOG_PART_COPY
            PROGLOG("physicalPartCopy rename(%s,%s)",tmpname->str(),pathTail(tofile));
#endif
            f->rename(pathTail(tofile));
        }
        catch (IException *e) {
            EXCLOG(e,"SingleFileCopy: File rename error");
            if (exc)
                exc.setown(e);
            else
                e->Release();
        }
    }
    if (exc.get()) {
        try {
            f->remove();
        }
        catch (IException *e) {
            // ignore
            e->Release();
        }
    }
#ifdef LOG_PART_COPY
    PROGLOG("done physicalPartCopy %s",(exc.get()==NULL)?"OK":"Failed");
#endif
    return exc.get()==NULL;
}