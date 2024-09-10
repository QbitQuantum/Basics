LRESULT VLCControlsWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg){
        case WM_CREATE:{
            const int ControlsHeight = 21+3;
            const int ButtonsWidth = ControlsHeight;

            int HorizontalOffset = xControlsSpace;
            int ControlWidth = ButtonsWidth;
            hPlayPauseButton =
                CreateWindow(TEXT("BUTTON"), TEXT("Play/Pause"),
                             WS_CHILD|WS_VISIBLE|BS_BITMAP|BS_FLAT,
                             HorizontalOffset, xControlsSpace,
                             ControlWidth, ControlsHeight, hWnd(),
                             (HMENU)ID_FS_PLAY_PAUSE, 0, 0);
            SendMessage(hPlayPauseButton, BM_SETIMAGE,
                        (WPARAM)IMAGE_BITMAP, (LPARAM)RC().hPauseBitmap);
            HorizontalOffset+=ControlWidth+xControlsSpace;

            ControlWidth = 200;
            int VideoPosControlHeight = 10;
            hVideoPosScroll =
                CreateWindow(PROGRESS_CLASS, TEXT("Video Position"),
                             WS_CHILD|WS_DISABLED|WS_VISIBLE|SBS_HORZ|SBS_TOPALIGN|PBS_SMOOTH,
                             HorizontalOffset, xControlsSpace+(ControlsHeight-VideoPosControlHeight)/2,
                             ControlWidth, VideoPosControlHeight, hWnd(),
                             (HMENU)ID_FS_VIDEO_POS_SCROLL, 0, 0);
            HMODULE hThModule = LoadLibrary(TEXT("UxTheme.dll"));
            if(hThModule){
                FARPROC proc = GetProcAddress(hThModule, "SetWindowTheme");
                typedef HRESULT (WINAPI* SetWindowThemeProc)(HWND, LPCWSTR, LPCWSTR);
                if(proc){
                    ((SetWindowThemeProc)proc)(hVideoPosScroll, L"", L"");
                }
                FreeLibrary(hThModule);
            }
            HorizontalOffset+=ControlWidth+xControlsSpace;

            ControlWidth = ButtonsWidth;
            hMuteButton =
                CreateWindow(TEXT("BUTTON"), TEXT("Mute"),
                             WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX|BS_PUSHLIKE|BS_BITMAP, //BS_FLAT
                             HorizontalOffset, xControlsSpace,
                             ControlWidth, ControlsHeight,
                             hWnd(), (HMENU)ID_FS_MUTE, 0, 0);
            SendMessage(hMuteButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP,
                        (LPARAM)RC().hVolumeBitmap);
            HorizontalOffset+=ControlWidth+xControlsSpace;

            ControlWidth = 100;
            hVolumeSlider =
                CreateWindow(TRACKBAR_CLASS, TEXT("Volume"),
                             WS_CHILD|WS_VISIBLE|TBS_HORZ|TBS_BOTTOM|TBS_AUTOTICKS,
                             HorizontalOffset, xControlsSpace,
                             ControlWidth, ControlsHeight - 4, hWnd(),
                             (HMENU)ID_FS_VOLUME, 0, 0);
            HorizontalOffset+=ControlWidth+xControlsSpace;
            SendMessage(hVolumeSlider, TBM_SETRANGE, FALSE, (LPARAM) MAKELONG (0, 100));
            SendMessage(hVolumeSlider, TBM_SETTICFREQ, (WPARAM) 10, 0);

            ControlWidth = ButtonsWidth;
            DWORD dwFSBtnStyle = WS_CHILD|BS_BITMAP|BS_FLAT;
            if( !PO() || PO()->get_enable_fs() ){
                dwFSBtnStyle |= WS_VISIBLE;
            }
            hFSButton =
                CreateWindow(TEXT("BUTTON"), TEXT("Toggle fullscreen"),
                             dwFSBtnStyle,
                             HorizontalOffset, xControlsSpace,
                             ControlWidth, ControlsHeight, hWnd(),
                             (HMENU)ID_FS_SWITCH_FS, 0, 0);
            SendMessage(hFSButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP,
                        (LPARAM)RC().hDeFullscreenBitmap);
            HorizontalOffset+=ControlWidth+xControlsSpace;

            RECT rect;
            GetClientRect(GetParent(hWnd()), &rect);

            int ControlWndWidth = HorizontalOffset;
            int ControlWndHeight = xControlsSpace+ControlsHeight+xControlsSpace;
            SetWindowPos(hWnd(), 0,
                         0, (rect.bottom - rect.top) - ControlWndWidth,
                         rect.right-rect.left, ControlWndHeight,
                         SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_NOACTIVATE);

            //new message blinking timer
            SetTimer(hWnd(), 2, 500, NULL);

            CreateToolTip();

            break;
        }
        case WM_SHOWWINDOW:{
            if(FALSE!=wParam){ //showing
                UpdateButtons();
            }
            break;
        }
        case WM_LBUTTONUP:{
            POINT BtnUpPoint = {LOWORD(lParam), HIWORD(lParam)};
            RECT VideoPosRect;
            GetWindowRect(hVideoPosScroll, &VideoPosRect);
            ClientToScreen(hWnd(), &BtnUpPoint);
            if(PtInRect(&VideoPosRect, BtnUpPoint)){
                SetVideoPos(float(BtnUpPoint.x-VideoPosRect.left)/(VideoPosRect.right-VideoPosRect.left));
            }
            break;
        }
        case WM_TIMER:{
            switch(wParam){
                case 1:{
                    POINT MousePoint;
                    GetCursorPos(&MousePoint);
                    RECT ControlWndRect;
                    GetWindowRect(hWnd(), &ControlWndRect);
                    if(PtInRect(&ControlWndRect, MousePoint)||GetCapture()==hVolumeSlider){
                        //do not allow control window to close while mouse is within
                        NeedShowControls();
                    }
                    else{
                        NeedHideControls();
                    }
                    break;
                }
                case 2:{
                    UpdateButtons();
                    break;
                }
            }
            break;
        }
        case WM_SETCURSOR:{
            RECT VideoPosRect;
            GetWindowRect(hVideoPosScroll, &VideoPosRect);
            DWORD dwMsgPos = GetMessagePos();
            POINT MsgPosPoint = {LOWORD(dwMsgPos), HIWORD(dwMsgPos)};
            if(PtInRect(&VideoPosRect, MsgPosPoint)){
                SetCursor(LoadCursor(NULL, IDC_HAND));
                return TRUE;
            }
            else{
                return VLCWnd::WindowProc(uMsg, wParam, lParam);
            }
            break;
        }
        case WM_NCDESTROY:
            break;
        case WM_COMMAND:{
            WORD NCode = HIWORD(wParam);
            WORD Control = LOWORD(wParam);
            switch(NCode){
                case BN_CLICKED:{
                    switch(Control){
                        case ID_FS_SWITCH_FS:
                            WM().ToggleFullScreen();
                            break;
                        case ID_FS_PLAY_PAUSE:{
                            if( VP() ){
                                if( IsPlaying() )
                                    VP()->pause();
                                else
                                    VP()->play();
                            }
                            break;
                        }
                        case ID_FS_MUTE:{
                            if( VP() ){
                                VP()->set_mute( IsDlgButtonChecked(hWnd(), ID_FS_MUTE) != FALSE );
                                SyncVolumeSliderWithVLCVolume();
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case WM_SIZE:{
            if( GetWindowLong(hWnd(), GWL_STYLE) & WS_VISIBLE &&
                !WM().IsFullScreen() &&
                ( !PO() || !PO()->get_show_toolbar() ) )
            {
                //hide controls when they are not allowed
                NeedHideControls();
            }

            const int new_client_width = LOWORD(lParam);

            bool isFSBtnVisible =
                (GetWindowLong(hFSButton, GWL_STYLE) & WS_VISIBLE) != 0;

            HDWP hDwp = BeginDeferWindowPos(4);

            int VideoScrollWidth = new_client_width;

            POINT pt = {0, 0};
            RECT rect;
            GetWindowRect(hPlayPauseButton, &rect);
            pt.x = rect.right;
            ScreenToClient(hWnd(), &pt);
            VideoScrollWidth -= pt.x;
            VideoScrollWidth -= xControlsSpace;

            RECT VideoSrcollRect;
            GetWindowRect(hVideoPosScroll, &VideoSrcollRect);

            RECT MuteRect;
            GetWindowRect(hMuteButton, &MuteRect);
            VideoScrollWidth -= xControlsSpace;
            VideoScrollWidth -= (MuteRect.right - MuteRect.left);

            RECT VolumeRect;
            GetWindowRect(hVolumeSlider, &VolumeRect);
            VideoScrollWidth -= xControlsSpace;
            VideoScrollWidth -= (VolumeRect.right - VolumeRect.left);

            RECT FSRect = {0, 0, 0, 0};
            if( isFSBtnVisible ) {
                GetWindowRect(hFSButton, &FSRect);
                VideoScrollWidth -= xControlsSpace;
                VideoScrollWidth -= (FSRect.right - FSRect.left);
                VideoScrollWidth -= xControlsSpace;
            }

            pt.x = VideoSrcollRect.left;
            pt.y = VideoSrcollRect.top;
            ScreenToClient(hWnd(), &pt);
            hDwp = DeferWindowPos(hDwp, hVideoPosScroll, 0, pt.x, pt.y,
                                  VideoScrollWidth,
                                  VideoSrcollRect.bottom - VideoSrcollRect.top,
                                  SWP_NOACTIVATE|SWP_NOOWNERZORDER);

            int HorizontalOffset =
                pt.x + VideoScrollWidth + xControlsSpace;
            pt.x = 0;
            pt.y = MuteRect.top;
            ScreenToClient(hWnd(), &pt);
            hDwp = DeferWindowPos(hDwp, hMuteButton, 0,
                                  HorizontalOffset, pt.y, 0, 0,
                                  SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
            HorizontalOffset +=
                MuteRect.right - MuteRect.left + xControlsSpace;

            pt.x = 0;
            pt.y = VolumeRect.top;
            ScreenToClient(hWnd(), &pt);
            hDwp = DeferWindowPos(hDwp, hVolumeSlider, 0,
                                  HorizontalOffset, pt.y, 0, 0,
                                  SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
            HorizontalOffset +=
                VolumeRect.right - VolumeRect.left + xControlsSpace;

            if( isFSBtnVisible ) {
                pt.x = 0;
                pt.y = FSRect.top;
                ScreenToClient(hWnd(), &pt);
                hDwp = DeferWindowPos(hDwp, hFSButton, 0,
                                      HorizontalOffset, pt.y, 0, 0,
                                      SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOOWNERZORDER);
            }

            EndDeferWindowPos(hDwp);
            break;
        }
        case WM_HSCROLL:
        case WM_VSCROLL: {
            if( VP() ){
                if(hVolumeSlider==(HWND)lParam){
                    LRESULT SliderPos = SendMessage(hVolumeSlider, (UINT) TBM_GETPOS, 0, 0);
                    SetVLCVolumeBySliderPos(SliderPos);
                }
            }
            break;
        }
        default:
            return VLCWnd::WindowProc(uMsg, wParam, lParam);
    }
    return 0L;
}