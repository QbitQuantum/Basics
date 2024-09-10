/******************************************************************************
 Update a new GIF file, given its file handle.
 Returns dynamically allocated GifFileType pointer which serves as the GIF
 info record.
******************************************************************************/
GifFileType *
DGifOpenFileHandle(int FileHandle, int *Error)
{
    char Buf[GIF_STAMP_LEN + 1];
    GifFileType *GifFile;
    GifFilePrivateType *Private;
    FILE *f;

    GifFile = (GifFileType *)malloc(sizeof(GifFileType));
    if (GifFile == NULL) {
        if (Error != NULL)
	    *Error = D_GIF_ERR_NOT_ENOUGH_MEM;
        (void)_close(FileHandle);
        return NULL;
    }

    /*@i1@*/memset(GifFile, '\0', sizeof(GifFileType));

    /* Belt and suspenders, in case the null pointer isn't zero */
    GifFile->SavedImages = NULL;
    GifFile->SColorMap = NULL;

    Private = (GifFilePrivateType *)malloc(sizeof(GifFilePrivateType));
    if (Private == NULL) {
        if (Error != NULL)
	    *Error = D_GIF_ERR_NOT_ENOUGH_MEM;
        (void)_close(FileHandle);
        free((char *)GifFile);
        return NULL;
    }
#ifdef _WIN32
    _setmode(FileHandle, O_BINARY);    /* Make sure it is in binary mode. */
#endif /* _WIN32 */

    f = _fdopen(FileHandle, "rb");    /* Make it into a stream: */

    /*@-mustfreeonly@*/
    GifFile->Private = (void *)Private;
    Private->FileHandle = FileHandle;
    Private->File = f;
    Private->FileState = FILE_STATE_READ;
    Private->Read = NULL;        /* don't use alternate input method (TVT) */
    GifFile->UserData = NULL;    /* TVT */
    /*@=mustfreeonly@*/

    /* Let's see if this is a GIF file: */
    /* coverity[check_return] */
    if (READ(GifFile, (unsigned char *)Buf, GIF_STAMP_LEN) != GIF_STAMP_LEN) {
        if (Error != NULL)
	    *Error = D_GIF_ERR_READ_FAILED;
        (void)fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    /* Check for GIF prefix at start of file */
    Buf[GIF_STAMP_LEN] = 0;
    if (strncmp(GIF_STAMP, Buf, GIF_VERSION_POS) != 0) {
        if (Error != NULL)
	    *Error = D_GIF_ERR_NOT_GIF_FILE;
        (void)fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    if (DGifGetScreenDesc(GifFile) == GIF_ERROR) {
        (void)fclose(f);
        free((char *)Private);
        free((char *)GifFile);
        return NULL;
    }

    GifFile->Error = 0;

    /* What version of GIF? */
    Private->gif89 = (Buf[GIF_VERSION_POS] == '9');

    return GifFile;
}