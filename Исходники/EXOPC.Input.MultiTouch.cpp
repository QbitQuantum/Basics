static void FixWindowForGesture(HWND hwnd)
{
    UnregisterTouchWindow(hwnd);

    // reenable right-click on touch and hold

    // The atom identifier and Tablet PC atom
    ATOM atomID = 0;
    LPCWSTR tabletAtom = L"MicrosoftTabletPenServiceProperty";

    // Get the Tablet PC atom ID
    atomID = GlobalAddAtom(tabletAtom);

    if (atomID != 0)
    {
        // Try to disable press and hold gesture by
        // setting the window property
        RemoveProp(hwnd, tabletAtom);
    }

    /*
    GESTURECONFIG gc1[3];
    UINT uiGcs1 = 3;

    ZeroMemory(&gc1, sizeof(gc1));
    gc1[0].dwID  = GID_ZOOM;
    gc1[1].dwID  = GID_ROTATE;
    gc1[2].dwID  = GID_PAN;
    BOOL bResult1 = GetGestureConfig(hwnd, 0, 0, &uiGcs1, gc1, sizeof(GESTURECONFIG));
    if (!bResult1){
        DWORD err = GetLastError();
    	tracei("zoom get config err ", bResult1);
    }
    tracei("zoom want config ", gc1[0].dwWant);
    tracei("zoom block config ", gc1[0].dwBlock);
    */

    /*
    DWORD dwPanWant  = GC_PAN_WITH_SINGLE_FINGER_VERTICALLY | GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY;
    DWORD dwPanBlock = GC_PAN_WITH_GUTTER | GC_PAN_WITH_INERTIA;

    // set the settings in the gesture configuration
    GESTURECONFIG gc[] = {{ GID_ZOOM, 0, GC_ZOOM },
    					  { GID_ROTATE, GC_ROTATE, 0},
    					  { GID_PAN, dwPanWant , dwPanBlock}
    					 };

    UINT uiGcs = 3;
    BOOL bResult = SetGestureConfig(hwnd, 0, uiGcs, gc, sizeof(GESTURECONFIG));

    if (!bResult)
    {
    	DWORD err = GetLastError();
    	tracei("error: ", err);
    }
    */
}