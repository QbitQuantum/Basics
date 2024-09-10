HWND CreateQCQPWindow(LPSTR lpWindowName,
         DWORD   dwStyle,
         int     x,
         int     y,
         int     dx,
         int     dy,
         HWND    hParent,
         HMENU   hMenu,
         HINSTANCE hInstance,
         WPARAM  wMessage)
{
    HWND hTemp ;
    char szClass[MAX_MSG_TXT] ;
    WORD BaseId = 0;
    WORD State;
    HBITMAP hBitmap;

    Dbg(LoadString(hInstance, SYS_QCQPCtrl_wClass, szClass, MAX_MSG_TXT)) ;
    hTemp = CreateWindow(
          (LPSTR)szClass,            // Window szClass name
          lpWindowName,            // Window's title
          WS_CHILD | WS_VISIBLE,   // window created visible
          x, y,                    // X, Y
          dx, dy,                  // Width, Height of window
          hParent,                 // Parent window's handle
          hMenu,                   // child's id
          hInstance,               // Instance of window
          NULL);                   // Create struct for WM_CREATE

    if (hTemp != NULL) {
        SetWindowWord (hTemp, CBWNDEXTRA_STYLE, LOWORD(dwStyle)) ;
        SetWindowWord (hTemp, CBWNDEXTRA_BITMAP, HIWORD(dwStyle)) ;
        SetWindowWord (hTemp, CBWNDEXTRA_STATE, STATE_NORMAL) ;
        SetWindowHandle (hTemp, CBWNDEXTRA_MESSAGE, wMessage) ;

        if (LOWORD(dwStyle) == QCQP_CS_PUSHBUTTON) {
            // Load the bitmaps and store the handles
            switch (HIWORD(dwStyle)) {
              case IDS_CTRL_TRACENORMAL:
              case IDS_CTRL_TRACEPUSHED:
              case IDS_CTRL_TRACEGRAYED:
                BaseId = VGA_TRACE_NORMAL;
                break;

              case IDS_CTRL_STEPNORMAL:
              case IDS_CTRL_STEPPUSHED:
              case IDS_CTRL_STEPGRAYED:
                BaseId = VGA_STEP_NORMAL;
                break;

              case IDS_CTRL_BREAKNORMAL:
              case IDS_CTRL_BREAKPUSHED:
              case IDS_CTRL_BREAKGRAYED:
                BaseId = VGA_BREAK_NORMAL;
                break;

              case IDS_CTRL_GONORMAL:
              case IDS_CTRL_GOPUSHED:
              case IDS_CTRL_GOGRAYED:
                BaseId = VGA_GO_NORMAL;
                break;

              case IDS_CTRL_HALTNORMAL:
              case IDS_CTRL_HALTPUSHED:
              case IDS_CTRL_HALTGRAYED:
                BaseId = VGA_HALT_NORMAL;
                break;

              case IDS_CTRL_QWATCHNORMAL:
              case IDS_CTRL_QWATCHPUSHED:
              case IDS_CTRL_QWATCHGRAYED:
                BaseId = VGA_QWATCH_NORMAL;
                break;

              case IDS_CTRL_SMODENORMAL:
              case IDS_CTRL_SMODEPUSHED:
              case IDS_CTRL_SMODEGRAYED:
                BaseId = VGA_SMODE_NORMAL;
                break;

              case IDS_CTRL_AMODENORMAL:
              case IDS_CTRL_AMODEPUSHED:
              case IDS_CTRL_AMODEGRAYED:
                BaseId = VGA_AMODE_NORMAL;
                break;


              case IDS_CTRL_FORMATNORMAL:
              case IDS_CTRL_FORMATPUSHED:
              case IDS_CTRL_FORMATGRAYED:
                BaseId = VGA_FORMAT_NORMAL;
                break;


              default:


                Assert(FALSE);
            }

            // Load the bitmaps for each state for the button
            for (State = STATE_NORMAL; State <= STATE_GRAYED; State++) {

                Dbg(hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE( BaseId + State )));

                SetWindowHandle(hTemp, GetBitmapIndex(State), (WPARAM)hBitmap);
            }
        }
    }

    return hTemp ;
}                                       /* CreateQCQPWindow() */