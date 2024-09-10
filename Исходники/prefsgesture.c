/* Handle the Gesture preferences */
Boolean PrefsGesturePreferenceEvent
    (
    ActionType action
    )
{
    Boolean handled;

    handled = false;

    switch ( action ) {
        case AVAILABLE:
            /* Always available */
            handled = true;
            break;

        case SHOWFIRST:
            handled = showFirst;
            showFirst = false;
            break;

        case LOAD:
            gestureSelected = GESTURES_UP;
            MemMove( gestureMode, Prefs()->gestMode, sizeof( gestureMode ) );
            InitializeActionList( frmPrefsGestureActionList );
            CtlSetValue( GetObjectPtr( frmPrefsGestureGestures ),
                Prefs()->gestures );
            SetListToSelection( frmPrefsGestureActionList,
                frmPrefsGestureSelectAction, gestureMode[ gestureSelected ] );
            handled = true;
            break;

        case DISPLAY:
            AffirmControlImage( gestureSelected, frmPrefsGestureUp,
                bmpGestureUp );
            handled = true;
            break;

        case SAVE:
            Prefs()->gestures = CtlGetValue( GetObjectPtr(
                frmPrefsGestureGestures ) );
            MemMove( Prefs()->gestMode, gestureMode, sizeof( gestureMode ) );
            handled = true;
            break;

        default:
            handled = false;
            break;
    }
    return handled;
}