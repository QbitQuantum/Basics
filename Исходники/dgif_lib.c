GifFileType *
DGifOpenFileHandle(int FileHandle) {

    unsigned char Buf[GIF_STAMP_LEN + 1];
    GifFileType *GifFile;
    GifFilePrivateType *Private;
    FILE *f;

    GifFile = (GifFileType *)malloc(sizeof(GifFileType));
    if (GifFile == NULL) {
        _GifError = D_GIF_ERR_NOT_ENOUGH_MEM;
        close(FileHandle);
        return NULL;
    }

    memset(GifFile, '\0', sizeof(GifFileType));

    Private = (GifFilePrivateType *)malloc(sizeof(GifFilePrivateType));
    if (Private == NULL) {
        _GifError = D_GIF_ERR_NOT_ENOUGH_MEM;
        close(FileHandle);
        free((char *)GifFile);
        return NULL;
    }
#if defined(__MSDOS__) || defined(WINDOWS32) || defined(_OPEN_BINARY)
    setmode(FileHandle, O_BINARY);    /* Make sure it is in binary mode. */
#endif /* __MSDOS__ */

    f = fdopen(FileHandle, "rb");    /* Make it into a stream: */

#if defined(__MSDOS__) || defined(WINDOWS32)
    setvbuf(f, NULL, _IOFBF, GIF_FILE_BUFFER_SIZE);    /* And inc. stream
                                                          buffer. */
#endif /* __MSDOS__ */

    GifFile->Private = (VoidPtr)Private;
    Private->FileHandle = FileHandle;
    Private->File = f;
    Private->FileState = FILE_STATE_READ;
    Private->Read = 0;    /* don't use alternate input method (TVT) */
    GifFile->UserData = 0;    /* TVT */

    /* Lets see if this is a GIF file: */
    if (READ(GifFile, Buf, GIF_STAMP_LEN) != GIF_STAMP_LEN) {
        _GifError = D_GIF_ERR_READ_FAILED;
        fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    /* The GIF Version number is ignored at this time. Maybe we should do
     * something more useful with it.  */
    Buf[GIF_STAMP_LEN] = 0;
    if (strncmp(GIF_STAMP, Buf, GIF_VERSION_POS) != 0) {
        _GifError = D_GIF_ERR_NOT_GIF_FILE;
        fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    if (DGifGetScreenDesc(GifFile) == GIF_ERROR) {
        fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    _GifError = 0;

    return GifFile;
}