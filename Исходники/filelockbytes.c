static HRESULT WINAPI FileLockBytesImpl_UnlockRegion(ILockBytes* iface,
    ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    FileLockBytesImpl* This = impl_from_ILockBytes(iface);
    OVERLAPPED ol;

    TRACE("ofs %u count %u flags %x\n", libOffset.u.LowPart, cb.u.LowPart, dwLockType);

    if (dwLockType & LOCK_WRITE)
        return STG_E_INVALIDFUNCTION;

    ol.hEvent = 0;
    ol.u.s.Offset = libOffset.u.LowPart;
    ol.u.s.OffsetHigh = libOffset.u.HighPart;

    if (UnlockFileEx(This->hfile, 0, cb.u.LowPart, cb.u.HighPart, &ol))
        return S_OK;
    return get_lock_error();
}