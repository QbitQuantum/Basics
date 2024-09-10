// Notice we don't check here the font. It is supposed to be OK before the call.
void wxTextMeasure::DoGetTextExtent(const wxString& string,
                                       wxCoord *width,
                                       wxCoord *height,
                                       wxCoord *descent,
                                       wxCoord *externalLeading)
{
    SIZE sizeRect;
    const size_t len = string.length();
    if ( !::GetTextExtentPoint32(m_hdc, string.t_str(), len, &sizeRect) )
    {
        wxLogLastError(wxT("GetTextExtentPoint32()"));
    }

    // the result computed by GetTextExtentPoint32() may be too small as it
    // accounts for under/overhang of the first/last character while we want
    // just the bounding rect for this string so adjust the width as needed
    if ( len > 0 )
    {
        ABC widthABC;
        const wxChar chFirst = *string.begin();
        if ( ::GetCharABCWidths(m_hdc, chFirst, chFirst, &widthABC) )
        {
            if ( widthABC.abcA < 0 )
                sizeRect.cx -= widthABC.abcA;

            if ( len > 1 )
            {
                const wxChar chLast = *string.rbegin();
                ::GetCharABCWidths(m_hdc, chLast, chLast, &widthABC);
            }
            //else: we already have the width of the last character

            if ( widthABC.abcC < 0 )
                sizeRect.cx -= widthABC.abcC;
        }
        //else: GetCharABCWidths() failed, not a TrueType font?
    }

    *width = sizeRect.cx;
    *height = sizeRect.cy;

    if ( descent || externalLeading )
    {
        TEXTMETRIC tm;
        ::GetTextMetrics(m_hdc, &tm);
        if ( descent )
            *descent = tm.tmDescent;
        if ( externalLeading )
            *externalLeading = tm.tmExternalLeading;
    }
}