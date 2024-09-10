 virtual void processEvent( EvtKey &rEvtKey )
 {
     // Only do the action when the key is down
     if( rEvtKey.getKeyState() == EvtKey::kDown )
         var_SetInteger( getIntf()->p_libvlc, "key-pressed",
                          rEvtKey.getModKey() );
 }