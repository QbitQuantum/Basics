bool SCH_EDIT_FRAME::OpenProjectFiles( const std::vector<wxString>& aFileSet, int aCtl )
{
    // implement the pseudo code from KIWAY_PLAYER.h:

    SCH_SCREENS screenList;

    // This is for python:
    if( aFileSet.size() != 1 )
    {
        UTF8 msg = StrPrintf( "Eeschema:%s() takes only a single filename", __func__ );
        DisplayError( this, msg );
        return false;
    }

    wxString    fullFileName( aFileSet[0] );

    // We insist on caller sending us an absolute path, if it does not, we say it's a bug.
    wxASSERT_MSG( wxFileName( fullFileName ).IsAbsolute(),
        wxT( "bug in single_top.cpp or project manager." ) );

    if( !LockFile( fullFileName ) )
    {
        wxString msg = wxString::Format( _(
                "Schematic file '%s' is already open." ),
                GetChars( fullFileName )
                );
        DisplayError( this, msg );
        return false;
    }

    // save any currently open and modified project files.
    for( SCH_SCREEN* screen = screenList.GetFirst(); screen; screen = screenList.GetNext() )
    {
        if( screen->IsModify() )
        {
            int response = YesNoCancelDialog( this, _(
                "The current schematic has been modified.  Do you wish to save the changes?" ),
                wxEmptyString,
                _( "Save and Load" ),
                _( "Load Without Saving" )
                );

            if( response == wxID_CANCEL )
            {
                return false;
            }
            else if( response == wxID_YES )
            {
                wxCommandEvent dummy;
                OnSaveProject( dummy );
            }
            else
            {
                // response == wxID_NO, fall thru
            }
            break;
        }
    }

    wxFileName pro = fullFileName;
    pro.SetExt( ProjectFileExtension );

    bool is_new = !wxFileName::IsFileReadable( fullFileName );

    // If its a non-existent schematic and caller thinks it exists
    if( is_new && !( aCtl & KICTL_CREATE ) )
    {
        // notify user that fullFileName does not exist, ask if user wants to create it.
        wxString ask = wxString::Format( _(
                "Schematic '%s' does not exist.  Do you wish to create it?" ),
                GetChars( fullFileName )
                );
        if( !IsOK( this, ask ) )
            return false;
    }

    // unload current project file before loading new
    {
        delete g_RootSheet;
        g_RootSheet = NULL;

        CreateScreens();
    }

    GetScreen()->SetFileName( fullFileName );
    g_RootSheet->SetFileName( fullFileName );

    SetStatusText( wxEmptyString );
    ClearMsgPanel();

    wxString msg = wxString::Format( _(
            "Ready\nProject dir: '%s'\n" ),
            GetChars( wxPathOnly( Prj().GetProjectFullName() ) )
            );
    SetStatusText( msg );

    // PROJECT::SetProjectFullName() is an impactful function.  It should only be
    // called under carefully considered circumstances.

    // The calling code should know not to ask me here to change projects unless
    // it knows what consequences that will have on other KIFACEs running and using
    // this same PROJECT.  It can be very harmful if that calling code is stupid.
    Prj().SetProjectFullName( pro.GetFullPath() );

    LoadProjectFile();

    // load the libraries here, not in SCH_SCREEN::Draw() which is a context
    // that will not tolerate DisplayError() dialog since we're already in an
    // event handler in there.
    // And when a schematic file is loaded, we need these libs to initialize
    // some parameters (links to PART LIB, dangling ends ...)
    Prj().SetElem( PROJECT::ELEM_SCH_PART_LIBS, NULL );
    Prj().SchLibs();

    if( is_new )
    {
        // mark new, unsaved file as modified.
        GetScreen()->SetModify();
    }
    else
    {
        g_RootSheet->SetScreen( NULL );

        DBG( printf( "%s: loading schematic %s\n", __func__, TO_UTF8( fullFileName ) );)

        bool diag = g_RootSheet->Load( this );
        (void) diag;

        SetScreen( m_CurrentSheet->LastScreen() );

        GetScreen()->ClrModify();

        UpdateFileHistory( fullFileName );

        // Check to see whether some old library parts need to be rescued
        // Only do this if RescueNeverShow was not set.
        wxConfigBase *config = Kiface().KifaceSettings();
        bool rescueNeverShow = false;
        config->Read( RESCUE_NEVER_SHOW_KEY, &rescueNeverShow, false );

        if( !rescueNeverShow )
        {
            if( RescueProject( false ) )
            {
                GetScreen()->CheckComponentsToPartsLinks();
                GetScreen()->TestDanglingEnds();
            }
        }
    }