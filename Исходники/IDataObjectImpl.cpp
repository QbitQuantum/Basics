HRESULT STDMETHODCALLTYPE DataObjectImpl::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC **ppenumFormatEtc)
{
    if (dwDirection == DATADIR_GET)
    {
        unsigned count = m_contents.get_count();
        pfc::array_staticsize_t<FORMATETC> fmt(count);
        for (unsigned i = 0; i < count; i++)
        {
            fmt[i] = m_contents[i]->formatEtc;
        }
        return SHCreateStdEnumFmtEtc(m_contents.get_count(), fmt.get_ptr(), ppenumFormatEtc);
    }

    return E_NOTIMPL;
}