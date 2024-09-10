void PCB_EDIT_FRAME::ReadPcbNetlist( const wxString& aNetlistFileName,
                                     const wxString& aCmpFileName,
                                     REPORTER*       aReporter,
                                     bool            aChangeFootprints,
                                     bool            aDeleteUnconnectedTracks,
                                     bool            aDeleteExtraFootprints,
                                     bool            aSelectByTimeStamp,
                                     bool            aDeleteSinglePadNets,
                                     bool            aIsDryRun )
{
    wxString        msg;
    NETLIST         netlist;
    KIGFX::VIEW*    view = GetGalCanvas()->GetView();
    BOARD*          board = GetBoard();

    netlist.SetIsDryRun( aIsDryRun );
    netlist.SetFindByTimeStamp( aSelectByTimeStamp );
    netlist.SetDeleteExtraFootprints( aDeleteExtraFootprints );
    netlist.SetReplaceFootprints( aChangeFootprints );

    try
    {
        std::auto_ptr<NETLIST_READER> netlistReader( NETLIST_READER::GetNetlistReader(
            &netlist, aNetlistFileName, aCmpFileName ) );

        if( !netlistReader.get() )
        {
            msg.Printf( _( "Cannot open netlist file \"%s\"." ), GetChars( aNetlistFileName ) );
            wxMessageBox( msg, _( "Netlist Load Error." ), wxOK | wxICON_ERROR, this );
            return;
        }

        SetLastNetListRead( aNetlistFileName );
        netlistReader->LoadNetlist();
        loadFootprints( netlist, aReporter );
    }
    catch( const IO_ERROR& ioe )
    {
        msg.Printf( _( "Error loading netlist.\n%s" ), ioe.errorText.GetData() );
        wxMessageBox( msg, _( "Netlist Load Error" ), wxOK | wxICON_ERROR );
        return;
    }

    // Clear undo and redo lists to avoid inconsistencies between lists
    if( !netlist.IsDryRun() )
        GetScreen()->ClearUndoRedoList();

    if( !netlist.IsDryRun() )
    {
        // Remove old modules
        for( MODULE* module = board->m_Modules; module; module = module->Next() )
        {
            module->RunOnChildren( boost::bind( &KIGFX::VIEW::Remove, view, _1 ) );
            view->Remove( module );
        }
    }

    // Clear selection, just in case a selected item has to be removed
    m_toolManager->RunAction( COMMON_ACTIONS::selectionClear, true );

    netlist.SortByReference();
    board->ReplaceNetlist( netlist, aDeleteSinglePadNets, aReporter );

    // If it was a dry run, nothing has changed so we're done.
    if( netlist.IsDryRun() )
        return;

    OnModify();

    SetCurItem( NULL );

    // Reload modules
    for( MODULE* module = board->m_Modules; module; module = module->Next() )
    {
        module->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
        view->Add( module );
        module->ViewUpdate();
    }

    if( aDeleteUnconnectedTracks && board->m_Track )
    {
        // Remove erroneous tracks.  This should probably pushed down to the #BOARD object.
        RemoveMisConnectedTracks();
    }

    // Rebuild the board connectivity:
    if( IsGalCanvasActive() )
        board->GetRatsnest()->ProcessBoard();

    Compile_Ratsnest( NULL, true );

    SetMsgPanel( board );
    m_canvas->Refresh();
}