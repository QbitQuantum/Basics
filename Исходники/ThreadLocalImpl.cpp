ThreadLocalImpl::ThreadLocalImpl()
{
    m_index = TlsAlloc();
}