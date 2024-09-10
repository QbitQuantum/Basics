bool TOOL_MANAGER::ProcessEvent( const TOOL_EVENT& aEvent )
{
    bool hotkey_handled = processEvent( aEvent );

    if( TOOL_STATE* active = GetCurrentToolState() )
        setActiveState( active );

    if( m_view->IsDirty() )
    {
        auto f = dynamic_cast<EDA_DRAW_FRAME*>( GetEditFrame() );

        if( f )
            f->GetGalCanvas()->Refresh(); // fixme: ugly hack, provide a method in TOOL_DISPATCHER.

#if defined( __WXMAC__ ) || defined( __WINDOWS__ )
        wxTheApp->ProcessPendingEvents(); // required for updating brightening behind a popup menu
#endif
    }

    return hotkey_handled;
}