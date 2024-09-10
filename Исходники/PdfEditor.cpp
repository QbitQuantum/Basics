ECode PdfEditor::constructor(
    /* [in] */ /*@NonNull*/ IParcelFileDescriptor* input) /*throws IOException*/
{
    if (input == NULL) {
        // throw new NullPointerException("input cannot be NULL");
        return E_NULL_POINTER_EXCEPTION;
    }

    Int64 size = 0;
    // try {
    AutoPtr<IFileDescriptor> fd;
    input->GetFileDescriptor((IFileDescriptor**)&fd);
    AutoPtr<ILibcore> lc;
    CLibcore::AcquireSingleton((ILibcore**)&lc);
    AutoPtr<IOs> os;
    lc->GetOs((IOs**)&os);
    if (FAILED((os->Lseek(fd, 0, OsConstants::_SEEK_SET, &size)))) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    AutoPtr<IStructStat> ss;
    if (FAILED((os->Fstat(fd, (IStructStat**)&ss)))) {
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    ss->GetSize(&size);
    // } catch (ErrnoException ee) {
    //     throw new IllegalArgumentException("file descriptor not seekable");
    // }

    mInput = input;
    Int32 iFd = 0;
    FAIL_RETURN(NativeOpen(mInput->GetFd(&iFd), size, &mNativeDocument));
    mPageCount = NativeGetPageCount(mNativeDocument);
    return mCloseGuard->Open(String("PdfEditor::Close"));
}