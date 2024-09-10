int PCBNEW_CONTROL::AppendBoard( const TOOL_EVENT& aEvent )
{
    int open_ctl;
    wxString fileName;
    PICKED_ITEMS_LIST undoListPicker;
    ITEM_PICKER picker( NULL, UR_NEW );

    PCB_EDIT_FRAME* editFrame = dynamic_cast<PCB_EDIT_FRAME*>( m_frame );
    BOARD* board = getModel<BOARD>();
    KIGFX::VIEW* view = getView();

    if( !editFrame )
        return 0;

    // Pick a file to append
    if( !AskLoadBoardFileName( editFrame, &open_ctl, &fileName, true ) )
        return 0;

    IO_MGR::PCB_FILE_T pluginType = plugin_type( fileName, open_ctl );
    PLUGIN::RELEASER pi( IO_MGR::PluginFind( pluginType ) );

    // keep track of existing items, in order to know what are the new items
    // (for undo command for instance)

    // Tracks are inserted, not appended, so mark the existing tracks to know what are the new tracks
    for( TRACK* track = board->m_Track; track; track = track->Next() )
        track->SetFlags( FLAG0 );

    // Other items are appended to the item list, so keep trace to the last existing item is enough
    MODULE* module = board->m_Modules.GetLast();
    BOARD_ITEM* drawing = board->m_Drawings.GetLast();
    int zonescount = board->GetAreaCount();

    // Keep also the count of copper layers, to adjust if necessary
    int initialCopperLayerCount = board->GetCopperLayerCount();
    LSET initialEnabledLayers = board->GetEnabledLayers();

    // Load the data
    try
    {
        PROPERTIES  props;
        char        xbuf[30];
        char        ybuf[30];

        // EAGLE_PLUGIN can use this info to center the BOARD, but it does not yet.
        sprintf( xbuf, "%d", editFrame->GetPageSizeIU().x );
        sprintf( ybuf, "%d", editFrame->GetPageSizeIU().y );

        props["page_width"]  = xbuf;
        props["page_height"] = ybuf;

        editFrame->GetDesignSettings().m_NetClasses.Clear();
        pi->Load( fileName, board, &props );
    }
    catch( const IO_ERROR& ioe )
    {
        wxString msg = wxString::Format( _( "Error loading board.\n%s" ), GetChars( ioe.errorText ));
        DisplayError( editFrame, msg );

        return 0;
    }

    m_toolMgr->RunAction( COMMON_ACTIONS::selectionClear, true );

    // Process the new items
    for( TRACK* track = board->m_Track; track; track = track->Next() )
    {
        if( track->GetFlags() & FLAG0 )
        {
            track->ClearFlags( FLAG0 );
            continue;
        }

        picker.SetItem( track );
        undoListPicker.PushItem( picker );
        view->Add( track );
        m_toolMgr->RunAction( COMMON_ACTIONS::selectItem, true, track );
    }

    module = module ? module->Next() : board->m_Modules;

    for( ; module; module = module->Next() )
    {
        picker.SetItem( module );
        undoListPicker.PushItem( picker );

        module->RunOnChildren( boost::bind( &KIGFX::VIEW::Add, view, _1 ) );
        view->Add( module );
        m_toolMgr->RunAction( COMMON_ACTIONS::selectItem, true, module );
    }

    drawing = drawing ? drawing->Next() : board->m_Drawings;

    for( ; drawing; drawing = drawing->Next() )
    {
        picker.SetItem( drawing );
        undoListPicker.PushItem( picker );
        view->Add( drawing );
        m_toolMgr->RunAction( COMMON_ACTIONS::selectItem, true, drawing );
    }

    for( ZONE_CONTAINER* zone = board->GetArea( zonescount ); zone;
         zone = board->GetArea( zonescount ) )
    {
        picker.SetItem( zone );
        undoListPicker.PushItem( picker );
        zonescount++;
        view->Add( zone );
        m_toolMgr->RunAction( COMMON_ACTIONS::selectItem, true, zone );
    }

    if( undoListPicker.GetCount() == 0 )
        return 0;

    editFrame->SaveCopyInUndoList( undoListPicker, UR_NEW );

    // Synchronize layers
    // we should not ask PLUGINs to do these items:
    int copperLayerCount = board->GetCopperLayerCount();

    if( copperLayerCount > initialCopperLayerCount )
        board->SetCopperLayerCount( copperLayerCount );

    // Enable all used layers, and make them visible:
    LSET enabledLayers = board->GetEnabledLayers();
    enabledLayers |= initialEnabledLayers;
    board->SetEnabledLayers( enabledLayers );
    board->SetVisibleLayers( enabledLayers );
    editFrame->ReCreateLayerBox();
    editFrame->ReFillLayerWidget();
    static_cast<PCB_DRAW_PANEL_GAL*>( editFrame->GetGalCanvas() )->SyncLayersVisibility( board );

    // Ratsnest
    board->BuildListOfNets();
    board->SynchronizeNetsAndNetClasses();
    board->GetRatsnest()->Recalculate();

    // Start dragging the appended board
    VECTOR2D v( static_cast<BOARD_ITEM*>( undoListPicker.GetPickedItem( 0 ) )->GetPosition() );
    getViewControls()->WarpCursor( v, true, true );
    m_toolMgr->InvokeTool( "pcbnew.InteractiveEdit" );

    return 0;
}