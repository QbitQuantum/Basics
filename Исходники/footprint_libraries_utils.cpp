bool FOOTPRINT_EDIT_FRAME::SaveFootprintToBoard( bool aAddNew )
{
    // update module in the current board,
    // not just add it to the board with total disregard for the netlist...
    PCB_EDIT_FRAME* pcbframe = (PCB_EDIT_FRAME*) Kiway().Player( FRAME_PCB, false );

    if( pcbframe == NULL )      // happens when the board editor is not active (or closed)
    {
        DisplayErrorMessage( this, _("No board currently open." ) );
        return false;
    }

    BOARD*  mainpcb  = pcbframe->GetBoard();
    MODULE* source_module  = NULL;
    MODULE* module_in_edit = GetBoard()->m_Modules;

    // Search the old module (source) if exists
    // Because this source could be deleted when editing the main board...
    if( module_in_edit->GetLink() )        // this is not a new module ...
    {
        source_module = mainpcb->m_Modules;

        for( ; source_module != NULL; source_module = source_module->Next() )
        {
            if( module_in_edit->GetLink() == source_module->GetTimeStamp() )
                break;
        }
    }

    if( !aAddNew && source_module == NULL ) // source not found
    {
        DisplayError( this, _( "Unable to find the footprint on the main board.\nCannot save." ) );
        return false;
    }

    if( aAddNew && source_module != NULL )
    {
        DisplayError( this, _( "Footprint already exists on board." ) );
        return false;
    }

    m_toolManager->RunAction( PCB_ACTIONS::selectionClear, true );
    pcbframe->GetToolManager()->RunAction( PCB_ACTIONS::selectionClear, true );
    BOARD_COMMIT commit( pcbframe );

    // Create the "new" module
    MODULE* newmodule = new MODULE( *module_in_edit );
    newmodule->SetParent( mainpcb );
    newmodule->SetLink( 0 );

    if( source_module )         // this is an update command
    {
        // In the main board,
        // the new module replace the old module (pos, orient, ref, value
        // and connexions are kept)
        // and the source_module (old module) is deleted
        pcbframe->Exchange_Module( source_module, newmodule, commit );
        newmodule->SetTimeStamp( module_in_edit->GetLink() );
        commit.Push( wxT( "Update module" ) );
    }
    else        // This is an insert command
    {
        wxPoint cursor_pos = pcbframe->GetCrossHairPosition();

        commit.Add( newmodule );
        pcbframe->SetCrossHairPosition( wxPoint( 0, 0 ) );
        pcbframe->PlaceModule( newmodule, NULL );
        newmodule->SetPosition( wxPoint( 0, 0 ) );
        pcbframe->SetCrossHairPosition( cursor_pos );
        newmodule->SetTimeStamp( GetNewTimeStamp() );
        commit.Push( wxT( "Insert module" ) );
    }

    newmodule->ClearFlags();
    pcbframe->SetCurItem( NULL );
    // @todo LEGACY should be unnecessary
    mainpcb->m_Status_Pcb = 0;

    return true;
}