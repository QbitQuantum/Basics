WXDLLIMPEXP_BASE int wxMSLU__wrename(const wchar_t *oldname,
                                     const wchar_t *newname)
{
    if ( wxUsingUnicowsDll() )
        return rename(wxConvFile.cWX2MB(oldname), wxConvFile.cWX2MB(newname));
    else
        return _wrename(oldname, newname);
}