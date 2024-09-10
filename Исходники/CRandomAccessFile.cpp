ECode CRandomAccessFile::GetLength(
    /* [out] */ Int64* len)
{
    VALIDATE_NOT_NULL(len);
    *len = 0;

    AutoPtr<ILibcore> libcore;
    CLibcore::AcquireSingleton((ILibcore**)&libcore);
    AutoPtr<IOs> os;
    libcore->GetOs((IOs**)&os);

    AutoPtr<IStructStat> stat;
    ECode ec = os->Fstat(mFd, (IStructStat**)&stat);
    if (FAILED(ec)) return E_IO_EXCEPTION;

    return stat->GetSize(len);
}