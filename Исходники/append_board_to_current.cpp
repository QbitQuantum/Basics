bool PCB_EDIT_FRAME::AppendBoardFile( const wxString& aFullFileName, int aCtl )
{
    IO_MGR::PCB_FILE_T  pluginType = plugin_type( aFullFileName, aCtl );
    PLUGIN::RELEASER pi( IO_MGR::PluginFind( pluginType ) );

    // keep trace of existing items, in order to know what are the new items
    // (for undo command for instance)

    // Tracks are inserted, not append, so mark existing tracks to know what are
    // the new tracks
    for( TRACK* track = GetBoard()->m_Track; track; track = track->Next() )
        track->SetFlags( FLAG0 );

    // Other items are append to the item list, so keep trace to the
    // last existing item is enough
    MODULE* module = GetBoard()->m_Modules.GetLast();
    BOARD_ITEM* drawing = GetBoard()->m_Drawings.GetLast();
    int zonescount = GetBoard()->GetAreaCount();

    // Keep also the count of copper layers, because we can happen boards
    // with different copper layers counts,
    // and the enabled layers
    int initialCopperLayerCount = GetBoard()->GetCopperLayerCount();
    LSET initialEnabledLayers = GetBoard()->GetEnabledLayers();

    try
    {
        PROPERTIES  props;
        char        xbuf[30];
        char        ybuf[30];

        // EAGLE_PLUGIN can use this info to center the BOARD, but it does not yet.
        sprintf( xbuf, "%d", GetPageSizeIU().x );
        sprintf( ybuf, "%d", GetPageSizeIU().y );

        props["page_width"]  = xbuf;
        props["page_height"] = ybuf;

        GetDesignSettings().m_NetClasses.Clear();
        pi->Load( aFullFileName, GetBoard(), &props );
    }
    catch( const IO_ERROR& ioe )
    {
        for( TRACK* track = GetBoard()->m_Track; track; track = track->Next() )
            track->ClearFlags( FLAG0 );

        wxString msg = wxString::Format( _(
                "Error loading board.\n%s" ),
                GetChars( ioe.What() )
                );
        DisplayError( this, msg );

        return false;
    }

    // Now prepare a block move command to place the new items, and
    // prepare the undo command.
    BLOCK_SELECTOR& blockmove = GetScreen()->m_BlockLocate;
    HandleBlockBegin( NULL, BLOCK_PRESELECT_MOVE, wxPoint( 0, 0) );
    PICKED_ITEMS_LIST& blockitemsList = blockmove.GetItems();
    PICKED_ITEMS_LIST undoListPicker;
    ITEM_PICKER picker( NULL, UR_NEW );

    EDA_RECT bbox;          // the new items bounding box, for block move
    bool bboxInit = true;   // true until the bounding box is initialized

    for( TRACK* track = GetBoard()->m_Track; track; track = track->Next() )
    {
        if( track->GetFlags() & FLAG0  )
        {
            track->ClearFlags( FLAG0 );
            continue;
        }

        track->SetFlags( IS_MOVED );
        picker.SetItem( track );
        undoListPicker.PushItem( picker );
        blockitemsList.PushItem( picker );

        if( bboxInit )
            bbox = track->GetBoundingBox();
        else
            bbox.Merge( track->GetBoundingBox() );

        bboxInit = false;
    }

    if( module )
        module = module->Next();
    else
        module = GetBoard()->m_Modules;

    for( ; module; module = module->Next() )
    {
        module->SetFlags( IS_MOVED );
        picker.SetItem( module );
        undoListPicker.PushItem( picker );
        blockitemsList.PushItem( picker );

        if( bboxInit )
            bbox = module->GetBoundingBox();
        else
            bbox.Merge( module->GetBoundingBox() );

        bboxInit = false;
    }

    if( drawing )
        drawing = drawing->Next();
    else
        drawing = GetBoard()->m_Drawings;

    for( ; drawing; drawing = drawing->Next() )
    {
        drawing->SetFlags( IS_MOVED );
        picker.SetItem( drawing );
        undoListPicker.PushItem( picker );
        blockitemsList.PushItem( picker );

        if( bboxInit )
            bbox = drawing->GetBoundingBox();
        else
            bbox.Merge( drawing->GetBoundingBox() );

        bboxInit = false;
    }

    for( ZONE_CONTAINER* zone = GetBoard()->GetArea( zonescount ); zone;
         zone = GetBoard()->GetArea( zonescount ) )
    {
        zone->SetFlags( IS_MOVED );
        picker.SetItem( zone );
        undoListPicker.PushItem( picker );
        blockitemsList.PushItem( picker );
        zonescount++;

        if( bboxInit )
            bbox = zone->GetBoundingBox();
        else
            bbox.Merge( zone->GetBoundingBox() );

        bboxInit = false;
    }

    SaveCopyInUndoList( undoListPicker, UR_NEW );

    // we should not ask PLUGINs to do these items:
    int copperLayerCount = GetBoard()->GetCopperLayerCount();

    if( copperLayerCount > initialCopperLayerCount )
        GetBoard()->SetCopperLayerCount( copperLayerCount );

    // Enable all used layers, and make them visible:
    LSET enabledLayers = GetBoard()->GetEnabledLayers();
    enabledLayers |= initialEnabledLayers;
    GetBoard()->SetEnabledLayers( enabledLayers );
    GetBoard()->SetVisibleLayers( enabledLayers );
    ReCreateLayerBox();
    ReFillLayerWidget();

    if( IsGalCanvasActive() )
        static_cast<PCB_DRAW_PANEL_GAL*>( GetGalCanvas() )->SyncLayersVisibility( GetBoard() );

    GetBoard()->BuildListOfNets();
    GetBoard()->SynchronizeNetsAndNetClasses();

    SetStatusText( wxEmptyString );
    BestZoom();

    // Finish block move command:
    wxPoint cpos = GetNearestGridPosition( bbox.Centre() );
    blockmove.SetOrigin( bbox.GetOrigin() );
    blockmove.SetSize( bbox.GetSize() );
    blockmove.SetLastCursorPosition( cpos );
    HandleBlockEnd( NULL );

    return true;
}