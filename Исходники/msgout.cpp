void wxMessageOutputStderr::Output(const wxString& str)
{
    const wxString strWithLF = AppendLineFeedIfNeeded(str);
    const wxWX2MBbuf buf = strWithLF.mb_str();

    if ( buf )
        fprintf(stderr, "%s", (const char*) buf);
    else // print at least something
        fprintf(stderr, "%s", (const char*) strWithLF.ToAscii());
}