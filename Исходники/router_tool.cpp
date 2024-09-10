int ROUTER_TOOL::mainLoop( PNS::ROUTER_MODE aMode )
{
    PCB_EDIT_FRAME* frame = getEditFrame<PCB_EDIT_FRAME>();

    // Deselect all items
    m_toolMgr->RunAction( PCB_ACTIONS::selectionClear, true );

    Activate();

    m_router->SetMode( aMode );

    VIEW_CONTROLS* ctls = getViewControls();
    ctls->ShowCursor( true );
    ctls->ForceCursorPosition( false );
    m_startSnapPoint = ctls->GetCursorPosition();

    std::unique_ptr<ROUTER_TOOL_MENU> ctxMenu( new ROUTER_TOOL_MENU( *frame, aMode ) );
    SetContextMenu( ctxMenu.get() );

    // Main loop: keep receiving events
    while( OPT_TOOL_EVENT evt = Wait() )
    {
        if( TOOL_EVT_UTILS::IsCancelInteractive( *evt ) )
        {
            break; // Finish
        }
        else if( evt->Action() == TA_UNDO_REDO_PRE )
        {
            m_router->ClearWorld();
        }
        else if( evt->Action() == TA_UNDO_REDO_POST || evt->Action() == TA_MODEL_CHANGE )
        {
            m_router->SyncWorld();
        }
        else if( evt->IsMotion() )
        {
            updateStartItem( *evt );
        }
        else if( evt->IsAction( &PCB_ACTIONS::dragFreeAngle ) )
        {
            updateStartItem( *evt, true );
            performDragging( PNS::DM_ANY | PNS::DM_FREE_ANGLE );
        }
        else if( evt->IsAction( &PCB_ACTIONS::drag45Degree ) )
        {
            updateStartItem( *evt, true );
            performDragging( PNS::DM_ANY );
        }
        else if( evt->IsAction( &PCB_ACTIONS::breakTrack ) )
        {
            updateStartItem( *evt, true );
            breakTrack( );
        }
        else if( evt->IsClick( BUT_LEFT ) || evt->IsAction( &ACT_NewTrack ) )
        {
            updateStartItem( *evt );

            if( evt->Modifier( MD_CTRL ) )
                performDragging( PNS::DM_ANY );
            else
                performRouting();
        }
        else if( evt->IsAction( &ACT_PlaceThroughVia ) )
        {
            m_toolMgr->RunAction( PCB_ACTIONS::layerToggle, true );
        }
    }

    frame->SetNoToolSelected();
    SetContextMenu( nullptr );

    // Store routing settings till the next invocation
    m_savedSettings = m_router->Settings();
    m_savedSizes = m_router->Sizes();

    return 0;
}