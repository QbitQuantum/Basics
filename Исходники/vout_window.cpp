void VoutWindow::processEvent( EvtKey &rEvtKey )
{
    // Only do the action when the key is down
    if( rEvtKey.getKeyState() == EvtKey::kDown )
        getIntf()->p_sys->p_dialogs->sendKey( rEvtKey.getModKey() );
}