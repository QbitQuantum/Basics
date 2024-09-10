/* antlarr: KDE 4.0:  make the first parameter "const QString &" */
bool KConfigINIBackEnd::writeConfigFile(QString filename, bool bGlobal, bool bMerge)
{
    // is the config object read-only?
    if(pConfig->isReadOnly())
        return true; // pretend we wrote it

    KEntryMap aTempMap;
    QFile *mergeFile = (bMerge ? new QFile(filename) : 0);
    bool bEntriesLeft = getEntryMap(aTempMap, bGlobal, mergeFile);
    delete mergeFile;
    if(bFileImmutable)
        return true; // pretend we wrote it

    // OK now the temporary map should be full of ALL entries.
    // write it out to disk.

    // Check if file exists:
    int fileMode = -1;
    bool createNew = true;

    KDE_struct_stat buf;
    if(KDE_stat(QFile::encodeName(filename), &buf) == 0)
    {
        if(buf.st_uid == getuid())
        {
            // Preserve file mode if file exists and is owned by user.
            fileMode = buf.st_mode & 0777;
        }
        else
        {
            // File is not owned by user:
            // Don't create new file but write to existing file instead.
            createNew = false;
        }
    }

    KSaveFile *pConfigFile = 0;
    FILE *pStream = 0;

    if(createNew)
    {
        pConfigFile = new KSaveFile(filename, 0600);

        if(pConfigFile->status() != 0)
        {
            delete pConfigFile;
            return bEntriesLeft;
        }

        if(!bGlobal && (fileMode == -1))
            fileMode = mFileMode;

        if(fileMode != -1)
        {
            fchmod(pConfigFile->handle(), fileMode);
        }

        pStream = pConfigFile->fstream();
    }
    else
    {
        // Open existing file.
        // We use open() to ensure that we call without O_CREAT.
        int fd = KDE_open(QFile::encodeName(filename), O_WRONLY | O_TRUNC);
        if(fd < 0)
        {
            return bEntriesLeft;
        }
        pStream = KDE_fdopen(fd, "w");
        if(!pStream)
        {
            close(fd);
            return bEntriesLeft;
        }
    }

    writeEntries(pStream, aTempMap);

    if(pConfigFile)
    {
        bool bEmptyFile = (ftell(pStream) == 0);
        if(bEmptyFile && ((fileMode == -1) || (fileMode == 0600)))
        {
            // File is empty and doesn't have special permissions: delete it.
            ::unlink(QFile::encodeName(filename));
            pConfigFile->abort();
        }
        else
        {
            // Normal case: Close the file
            pConfigFile->close();
        }
        delete pConfigFile;
    }
    else
    {
        fclose(pStream);
    }

    return bEntriesLeft;
}