int CatalogItemsComparator::CompareStrings(wxString a, wxString b) const
{
    a.Replace("&", "");
    a.Replace("_", "");

    b.Replace("&", "");
    b.Replace("_", "");

    if (m_collator)
    {
        UErrorCode err = U_ZERO_ERROR;
#if wxUSE_UNICODE_UTF8
        return m_collator->compareUTF8(a.wx_str(), b.wx_str(), err);
#elif SIZEOF_WCHAR_T == 2
        return m_collator->compare(a.wx_str(), a.length(), b.wx_str(), b.length(), err);
#else
        return m_collator->compare(str::to_icu(a), str::to_icu(b), err);
#endif
    }
    else
    {
        return a.CmpNoCase(b);
    }
}