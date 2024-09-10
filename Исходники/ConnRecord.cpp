STDMETHODIMP CConnRecord::get_LongValue(BSTR* retVal)
{
    CComBSTR ret;
    wchar_t tmp[256];
    _i64tow_s(m_rec.longValue, tmp, 256, 10);
    ret = tmp;
    *retVal = ret.Copy();
    return S_OK;
}