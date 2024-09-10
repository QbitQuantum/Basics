LRESULT CALLBACK WndProc(HWND hWnd, // handle for this window
                         UINT uMsg, // message for this window
                         WPARAM wParam, // additional message information
                         LPARAM lParam) // additional message information
{
    TRect rect;
    switch (uMsg) // check for windows messages
    {
    case WM_PASTE: //[Ctrl]+[V] potrzebujemy do innych celów
        return 0;
    case WM_COPYDATA: // obs³uga danych przes³anych przez program steruj¹cy
        pDane = (PCOPYDATASTRUCT)lParam;
        if (pDane->dwData == 'EU07') // sygnatura danych
            World.OnCommandGet((DaneRozkaz *)(pDane->lpData));
        break;
    case WM_ACTIVATE: // watch for window activate message
        // case WM_ACTIVATEAPP:
        { // Ra: uzale¿nienie aktywnoœci od bycia na wierzchu
            Global::bActive = (LOWORD(wParam) != WA_INACTIVE);
            if (Global::bInactivePause) // jeœli ma byæ pauzowanie okna w tle
                if (Global::bActive)
                    Global::iPause &= ~4; // odpauzowanie, gdy jest na pierwszym planie
                else
                    Global::iPause |= 4; // w³¹czenie pauzy, gdy nieaktywy
            if (Global::bActive)
                SetCursorPos(mx, my);
            ShowCursor(!Global::bActive);
            /*
               if (!HIWORD(wParam))	//check minimization state
                    active=TRUE;	//program is active
               else
                    active=FALSE;	//program is no longer active
            */
            return 0; // return to the message loop
        }
    case WM_SYSCOMMAND: // intercept system commands
    {
        switch (wParam) // check system calls
        {
        case 61696: // F10
            World.OnKeyDown(VK_F10);
            return 0;
        case SC_SCREENSAVE: // screensaver trying to start?
        case SC_MONITORPOWER: // monitor trying to enter powersave?
            return 0; // prevent from happening
        }
        break; // exit
    }
    case WM_CLOSE: // did we receive a close message?
    {
        PostQuitMessage(0); // send a quit message [Alt]+[F4]
        return 0; // jump back
    }
    case WM_MOUSEMOVE:
    {
        // mx= 100;//Global::iWindowWidth/2;
        // my= 100;//Global::iWindowHeight/2;
        // SetCursorPos(Global::iWindowWidth/2,Global::iWindowHeight/2);
        // m_x= LOWORD(lParam);
        // m_y= HIWORD(lParam);
        GetCursorPos(&mouse);
        if (Global::bActive && ((mouse.x != mx) || (mouse.y != my)))
        {
            World.OnMouseMove(double(mouse.x - mx) * 0.005, double(mouse.y - my) * 0.01);
            SetCursorPos(mx, my);
        }
        return 0; // jump back
    }
    case WM_KEYUP:
        if (Global::bActive)
        {
            World.OnKeyUp(wParam);
            return 0;
        }
    case WM_KEYDOWN:
        if (Global::bActive)
        {
            if (wParam != 17) // bo naciœniêcia [Ctrl] nie ma po co przekazywaæ
                if (wParam != 145) //[Scroll Lock] te¿ nie
                    World.OnKeyDown(wParam);
            switch (wParam)
            {
            case VK_ESCAPE: //[Esc] pauzuje tylko bez Debugmode
                if (DebugModeFlag)
                    break;
            case 19: //[Pause]
                if (Global::iPause & 1) // jeœli pauza startowa
                    Global::iPause &= ~1; // odpauzowanie, gdy po wczytaniu mia³o nie startowaæ
                else if (!(Global::iMultiplayer & 2)) // w multiplayerze pauza nie ma sensu
                    if (!Console::Pressed(VK_CONTROL)) // z [Ctrl] to radiostop jest
                        // Ra: poni¿sze nie ma sensu, bo brak komunikacji natychmiast zapauzuje
                        // ponownie
                        // if (Global::iPause&8) //jeœli pauza zwi¹zana z brakiem komunikacji z
                        // PoKeys
                        // Global::iPause&=~10; //odpauzowanie pauzy PoKeys (chyba nic nie da) i
                        // ewentualnie klawiszowej równie¿
                        // else
                        Global::iPause ^= 2; // zmiana stanu zapauzowania
                if (Global::iPause) // jak pauza
                    Global::iTextMode = VK_F1; // to wyœwietliæ zegar i informacjê
                break;
            case VK_F7:
                if (DebugModeFlag)
                { // siatki wyœwietlane tyko w trybie testowym
                    Global::bWireFrame = !Global::bWireFrame;
                    ++Global::iReCompile; // odœwie¿yæ siatki
                    // Ra: jeszcze usun¹æ siatki ze skompilowanych obiektów!
                }
                break;
            }
        }
        return 0; // jump back
    case WM_CHAR:
    {
        /*
           switch ((TCHAR) wParam)
           {
            // case 'q':
            //  done= true;
            //  KillGLWindow();
            //  PostQuitMessage(0);
            //  DestroyWindow( hWnd );
            //  break;
           };
        */
        return 0;
    }
    case WM_SIZE: // resize the OpenGL window
    {
        ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); // LoWord=Width, HiWord=Height
        if (GetWindowRect(hWnd, &rect))
        { // Ra: zmiana rozmiaru okna bez przesuwania myszy
            // mx=WindowWidth/2+rect.left;    // horizontal position
            // my=WindowHeight/2+rect.top;    // vertical position
            // SetCursorPos(mx,my);
        }
        return 0; // jump back
    }
    case WM_MOVE: // przesuwanie okna?
    {
        mx = WindowWidth / 2 + LOWORD(lParam); // horizontal position
        my = WindowHeight / 2 + HIWORD(lParam); // vertical position
        // SetCursorPos(mx,my);
        break;
    }
    case WM_PAINT:
    { // odrysowanie okna
        break;
    }
    // case WM_ERASEBKGND: //Process this message to keep Windows from erasing background.
    case MM_JOY1BUTTONDOWN:
    {
        // WriteLog("Joystick button "+AnsiString(wParam));
        break;
    }
    case WM_CREATE:
        /* Capture the joystick. If this fails, beep and display
         * error, then quit.
         */
        if (joySetCapture(hWnd, JOYSTICKID1, 0, FALSE))
        {
            // MessageBeep(MB_ICONEXCLAMATION);
            // MessageBox(hWnd,"Couldn't capture the joystick",NULL,MB_OK|MB_ICONEXCLAMATION);
            // return -1;
        }
        break;
    }
    // pass all unhandled messages to DefWindowProc
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
};