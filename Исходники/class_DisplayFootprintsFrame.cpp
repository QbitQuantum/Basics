MODULE* DISPLAY_FOOTPRINTS_FRAME::Get_Module( const wxString& aFootprintName )
{
    MODULE* footprint = NULL;

    try
    {
        FPID fpid;

        if( fpid.Parse( aFootprintName ) >= 0 )
        {
            DisplayInfoMessage( this, wxString::Format( wxT( "Footprint ID <%s> is not valid." ),
                                                        GetChars( aFootprintName ) ) );
            return NULL;
        }

        std::string nickname = fpid.GetLibNickname();
        std::string fpname   = fpid.GetFootprintName();

        wxLogDebug( wxT( "Load footprint <%s> from library <%s>." ),
                    fpname.c_str(), nickname.c_str()  );

        footprint = Prj().PcbFootprintLibs()->FootprintLoad(
                FROM_UTF8( nickname.c_str() ), FROM_UTF8( fpname.c_str() ) );
    }
    catch( const IO_ERROR& ioe )
    {
        DisplayError( this, ioe.errorText );
        return NULL;
    }

    if( footprint )
    {
        footprint->SetParent( (EDA_ITEM*) GetBoard() );
        footprint->SetPosition( wxPoint( 0, 0 ) );
        return footprint;
    }

    wxString msg = wxString::Format( _( "Footprint '%s' not found" ), aFootprintName.GetData() );
    DisplayError( this, msg );
    return NULL;
}