void NETLIST_EXPORTER::sprintPinNetName( wxString& aResult,
                                    const wxString& aNetNameFormat, NETLIST_OBJECT* aPin,
                                    bool aUseNetcodeAsNetName )
{
    int netcode = aPin->GetNet();

    // Not wxString::Clear(), which would free memory.  We want the worst
    // case wxString memory to grow to avoid reallocation from within the
    // caller's loop.
    aResult.Empty();

    if( netcode != 0 && aPin->GetConnectionType() == PAD_CONNECT )
    {
        if( aUseNetcodeAsNetName )
        {
            aResult.Printf( wxT("%d"), netcode );
        }
        else
        {
        aResult = aPin->GetNetName();

        if( aResult.IsEmpty() )     // No net name: give a name from net code
            aResult.Printf( aNetNameFormat.GetData(), netcode );
        }
    }
}