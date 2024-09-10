MODULE* PCB_BASE_FRAME::LoadModuleFromLibrary( const wxString& aLibrary,
                                               FP_LIB_TABLE*   aTable,
                                               bool            aUseFootprintViewer,
                                               wxDC*           aDC )
{
    MODULE*     module = NULL;
    wxPoint     curspos = GetCrossHairPosition();
    wxString    moduleName, keys;
    wxString    libName = aLibrary;
    bool        allowWildSeach = true;

    static wxArrayString HistoryList;
    static wxString      lastComponentName;

    // Ask for a component name or key words
    DIALOG_GET_COMPONENT dlg( this, HistoryList, _( "Load Module" ), aUseFootprintViewer );

    dlg.SetComponentName( lastComponentName );

    if( dlg.ShowModal() == wxID_CANCEL )
        return NULL;

    if( dlg.m_GetExtraFunction )
    {
        // SelectFootprintFromLibBrowser() returns the "full" footprint name, i.e.
        // <lib_name>/<footprint name> or FPID format "lib_name:fp_name:rev#"
        moduleName = SelectFootprintFromLibBrowser();
    }
    else
    {
        moduleName = dlg.GetComponentName();
    }

    if( moduleName.IsEmpty() )  // Cancel command
    {
        m_canvas->MoveCursorToCrossHair();
        return NULL;
    }

    if( dlg.IsKeyword() )                          // Selection by keywords
    {
        allowWildSeach = false;
        keys = moduleName;
        moduleName = SelectFootprint( this, libName, wxEmptyString, keys, aTable );

        if( moduleName.IsEmpty() )                 // Cancel command
        {
            m_canvas->MoveCursorToCrossHair();
            return NULL;
        }
    }
    else if( moduleName.Contains( wxT( "?" ) )
           || moduleName.Contains( wxT( "*" ) ) )  // Selection wild card
    {
        allowWildSeach = false;
        moduleName     = SelectFootprint( this, libName, moduleName, wxEmptyString, aTable );

        if( moduleName.IsEmpty() )
        {
            m_canvas->MoveCursorToCrossHair();
            return NULL;                           // Cancel command.
        }
    }

    FPID fpid;

    wxCHECK_MSG( fpid.Parse( moduleName ) < 0, NULL,
                 wxString::Format( wxT( "Could not parse FPID string '%s'." ),
                                   GetChars( moduleName ) ) );

    try
    {
        module = loadFootprint( fpid );
    }
    catch( const IO_ERROR& ioe )
    {
        wxLogDebug( wxT( "An error occurred attemping to load footprint '%s'.\n\nError: %s" ),
                    fpid.Format().c_str(), GetChars( ioe.errorText ) );
    }

    if( !module && allowWildSeach )                // Search with wild card
    {
        allowWildSeach = false;

        wxString wildname = wxChar( '*' ) + moduleName + wxChar( '*' );
        moduleName = wildname;

        moduleName = SelectFootprint( this, libName, moduleName, wxEmptyString, aTable );

        if( moduleName.IsEmpty() )
        {
            m_canvas->MoveCursorToCrossHair();
            return NULL;    // Cancel command.
        }
        else
        {
            FPID fpid;

            wxCHECK_MSG( fpid.Parse( moduleName ) < 0, NULL,
                         wxString::Format( wxT( "Could not parse FPID string '%s'." ),
                                           GetChars( moduleName ) ) );

            try
            {
                module = loadFootprint( fpid );
            }
            catch( const IO_ERROR& ioe )
            {
                wxLogDebug( wxT( "An error occurred attemping to load footprint '%s'.\n\nError: %s" ),
                            fpid.Format().c_str(), GetChars( ioe.errorText ) );
            }
        }
    }

    SetCrossHairPosition( curspos );
    m_canvas->MoveCursorToCrossHair();

    if( module )
    {
        GetBoard()->Add( module, ADD_APPEND );
        lastComponentName = moduleName;
        AddHistoryComponentName( HistoryList, moduleName );

        module->SetFlags( IS_NEW );
        module->SetLink( 0 );
        module->SetPosition( curspos );
        module->SetTimeStamp( GetNewTimeStamp() );
        GetBoard()->m_Status_Pcb = 0;

        // Put it on FRONT layer,
        // (Can be stored flipped if the lib is an archive built from a board)
        if( module->IsFlipped() )
            module->Flip( module->GetPosition() );

        // Place it in orientation 0,
        // even if it is not saved with orientation 0 in lib
        // (Can happen if the lib is an archive built from a board)
        Rotate_Module( NULL, module, 0, false );

        RecalculateAllTracksNetcode();

        if( aDC )
            module->Draw( m_canvas, aDC, GR_OR );
    }

    return module;
}