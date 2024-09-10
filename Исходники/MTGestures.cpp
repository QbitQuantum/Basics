// The code below is from the wizard but it has been customized for this 
// application. There is a custom code to handle WM_SIZE, WM_GESTURENOTIFY
// and WM_GESTURE messages.
//
// Processes messages for the main window:
//      WM_COMMAND        - process the application menu
//      WM_SIZE           - process resizing of client window
//      WM_PAINT          - paint the main window
//      WM_DESTROY        - post a quit message and return
//      WM_GESTURENOTIFY  - process a gesture notification message 
//      WM_GESTURE        - process the gesture command
// in:
//      hWnd        window handle
//      message     message code
//      wParam      message parameter (message-specific)
//      lParam      message parameter (message-specific)
// returns:
//      the result of the message processing and depends on the message sent
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_GESTURENOTIFY:
        {
            // This is the right place to define the list of gestures that this
            // application will support. By populating GESTURECONFIG structure 
            // and calling SetGestureConfig function. We can choose gestures 
            // that we want to handle in our application. In this app we
            // decide to handle all gestures.
            GESTURECONFIG gc = {
                0,              // gesture ID
                GC_ALLGESTURES, // settings related to gesture ID that are to be 
                                // turned on
                0               // settings related to gesture ID that are to be 
                                // turned off
            };

            BOOL bResult = SetGestureConfig(
                hWnd,                 // window for which configuration is specified  
                0,                    // reserved, must be 0
                1,                    // count of GESTURECONFIG structures
                &gc,                  // array of GESTURECONFIG structures, dwIDs will be processed in the
                                      // order specified and repeated occurances will overwrite previous ones
                sizeof(GESTURECONFIG) // sizeof(GESTURECONFIG)
            );                        
            
            if (!bResult)
            {
                ASSERT(L"Error in execution of SetGestureConfig" && 0);
            }
        }
        break;

    case WM_GESTURE:
        // The gesture processing code is implemented in the CGestureEngine 
        // class.
        return g_cGestureEngine.WndProc(hWnd,wParam,lParam);
        break;

    case WM_SIZE:
        // resize rectangle and place it in the middle of the new client area
        g_cRect.ResetObject(LOWORD(lParam),HIWORD(lParam));
        break;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);       

        // Full redraw: background + rectangle
        g_cRect.Paint(hdc);

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:

        PostQuitMessage(0);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}