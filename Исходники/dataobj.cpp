void wxDataFormat::SetId( const wxString& id )
{
#if !wxUSE_NANOX
    PrepareFormats();
    m_type = wxDF_PRIVATE;
    m_format = XInternAtom( (Display*) wxGetDisplay(), id.ToAscii(), FALSE );
#endif
}