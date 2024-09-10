ULONG VMR9CustomPresenter::Release()
{
    ULONG ret = _InterlockedDecrement(&m_RefCount);
    if (ret == 0)
    {
        delete this;
    }
    return ret;
}