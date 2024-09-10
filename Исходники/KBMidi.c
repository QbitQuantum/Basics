LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL bOpened = FALSE ;
     HDC         hdc ;
     HMENU       hMenu ;
     int         i, iNumDevs, iPitchBend, cxClient, cyClient ;
     MIDIOUTCAPS moc ;
     PAINTSTRUCT ps ;
     SIZE        size ;
     TCHAR       szBuffer [16] ;
     
     switch (message)
     {
     case WM_CREATE:
               // Get size of capital letters in system font
          
          hdc = GetDC (hwnd) ;
          
          GetTextExtentPoint (hdc, TEXT ("M"), 1, &size) ;
          cxCaps = size.cx ;
          cyChar = size.cy ;
          
          ReleaseDC (hwnd, hdc) ;
          
               // Initialize "Volume" scroll bar
          
          SetScrollRange (hwnd, SB_HORZ, 1, 127, FALSE) ;
          SetScrollPos   (hwnd, SB_HORZ, iVelocity, TRUE) ;
          
               // Initialize "Pitch Bend" scroll bar
          
          SetScrollRange (hwnd, SB_VERT, 0, 16383, FALSE) ;
          SetScrollPos   (hwnd, SB_VERT, 8192, TRUE) ;
          
               // Get number of MIDI output devices and set up menu
          
          if (0 == (iNumDevs = midiOutGetNumDevs ()))
          {
               MessageBeep (MB_ICONSTOP) ;
               MessageBox (hwnd, TEXT ("No MIDI output devices!"),
                                 szAppName, MB_OK | MB_ICONSTOP) ;
               return -1 ;
          }
          SetMenu (hwnd, CreateTheMenu (iNumDevs)) ;
          return 0 ;
          
     case WM_SIZE:
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          
          xOffset = (cxClient - 25 * 3 * cxCaps / 2) / 2 ;
          yOffset = (cyClient - 11 * cyChar) / 2 + 5 * cyChar ;
          return 0 ;
          
     case WM_COMMAND:
          hMenu = GetMenu (hwnd) ;
          
              // "Open" menu command
          
          if (LOWORD (wParam) == IDM_OPEN && !bOpened)
          {
               if (midiOutOpen (&hMidiOut, iDevice, 0, 0, 0))
               {
                    MessageBeep (MB_ICONEXCLAMATION) ;
                    MessageBox (hwnd, TEXT ("Cannot open MIDI device"),
                                szAppName, MB_OK | MB_ICONEXCLAMATION) ;
               }
               else
               {
                    CheckMenuItem (hMenu, IDM_OPEN,  MF_CHECKED) ;
                    CheckMenuItem (hMenu, IDM_CLOSE, MF_UNCHECKED) ;
                    
                    MidiSetPatch (hMidiOut, iChannel, iVoice) ;
                    bOpened = TRUE ;
               }
          }
          
               // "Close" menu command
          
          else if (LOWORD (wParam) == IDM_CLOSE && bOpened)
          {
               CheckMenuItem (hMenu, IDM_OPEN,  MF_UNCHECKED) ;
               CheckMenuItem (hMenu, IDM_CLOSE, MF_CHECKED) ;
               
                    // Turn all keys off and close device
               
               for (i = 0 ; i < 16 ; i++)
                    MidiOutMessage (hMidiOut, 0xB0, i, 123, 0) ;
               
               midiOutClose (hMidiOut) ;
               bOpened = FALSE ;
          }
          
               // Change MIDI "Device" menu command
          
          else if (LOWORD (wParam) >= IDM_DEVICE - 1 && 
                   LOWORD (wParam) <  IDM_CHANNEL)
          {
               CheckMenuItem (hMenu, IDM_DEVICE + iDevice, MF_UNCHECKED) ;
               iDevice = LOWORD (wParam) - IDM_DEVICE ;
               CheckMenuItem (hMenu, IDM_DEVICE + iDevice, MF_CHECKED) ;
               
                    // Close and reopen MIDI device
               
               if (bOpened)
               {
                    SendMessage (hwnd, WM_COMMAND, IDM_CLOSE, 0L) ;
                    SendMessage (hwnd, WM_COMMAND, IDM_OPEN,  0L) ;
               }
          }
          
               // Change MIDI "Channel" menu command
          
          else if (LOWORD (wParam) >= IDM_CHANNEL && 
                   LOWORD (wParam) <  IDM_VOICE)
          {
               CheckMenuItem (hMenu, IDM_CHANNEL + iChannel, MF_UNCHECKED);
               iChannel = LOWORD (wParam) - IDM_CHANNEL ;
               CheckMenuItem (hMenu, IDM_CHANNEL + iChannel, MF_CHECKED) ;
               
               if (bOpened)
                    MidiSetPatch (hMidiOut, iChannel, iVoice) ;
          }
          
               // Change MIDI "Voice" menu command
          
          else if (LOWORD (wParam) >= IDM_VOICE)
          {
               CheckMenuItem (hMenu, IDM_VOICE + iVoice, MF_UNCHECKED) ;
               iVoice = LOWORD (wParam) - IDM_VOICE ;
               CheckMenuItem (hMenu, IDM_VOICE + iVoice, MF_CHECKED) ;
               
               if (bOpened)
                    MidiSetPatch (hMidiOut, iChannel, iVoice) ;
          }
          
          InvalidateRect (hwnd, NULL, TRUE) ;
          return 0 ;
          
          // Process a Key Up or Key Down message
          
     case WM_KEYUP:
     case WM_KEYDOWN:
          hdc = GetDC (hwnd) ;
          
          if (bOpened)
               ProcessKey (hdc, message, lParam) ;
          
          ReleaseDC (hwnd, hdc) ;
          return 0 ;
          
          // For Escape, turn off all notes and repaint
          
     case WM_CHAR:
          if (bOpened && wParam == 27)
          {
               for (i = 0 ; i < 16 ; i++)
                    MidiOutMessage (hMidiOut, 0xB0, i, 123, 0) ;
               
               InvalidateRect (hwnd, NULL, TRUE) ;
          }
          return 0 ;
          
          // Horizontal scroll: Velocity
          
     case WM_HSCROLL:
          switch (LOWORD (wParam))
          {
          case SB_LINEUP:         iVelocity -= 1 ;  break ;
          case SB_LINEDOWN:       iVelocity += 1 ;  break ;
          case SB_PAGEUP:         iVelocity -= 8 ;  break ;
          case SB_PAGEDOWN:       iVelocity += 8 ;  break ;
          case SB_THUMBPOSITION:  iVelocity = HIWORD (wParam) ;  break ;
          default:                return 0 ;
          }
          iVelocity = max (1, min (iVelocity, 127)) ;
          SetScrollPos (hwnd, SB_HORZ, iVelocity, TRUE) ;
          return 0 ;
          
          // Vertical scroll:  Pitch Bend
     
     case WM_VSCROLL:
          switch (LOWORD (wParam))
          {
          case SB_THUMBTRACK:    iPitchBend = 16383 - HIWORD (wParam) ;  break ;
          case SB_THUMBPOSITION: iPitchBend = 8191 ;                     break ;
          default:               return 0 ;
          }
          iPitchBend = max (0, min (iPitchBend, 16383)) ;
          SetScrollPos (hwnd, SB_VERT, 16383 - iPitchBend, TRUE) ;
          
          if (bOpened)
               MidiPitchBend (hMidiOut, iChannel, iPitchBend) ;
          return 0 ;
     
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          
          for (i = 0 ; i < NUMSCANS ; i++)
               if (key[i].xPos != -1)
                    DrawKey (hdc, i, FALSE) ;
               
          midiOutGetDevCaps (iDevice, &moc, sizeof (MIDIOUTCAPS)) ;
          wsprintf (szBuffer, TEXT ("Channel %i"), iChannel + 1) ;
     
          TextOut (hdc, cxCaps, 1 * cyChar, 
                        bOpened ? TEXT ("Open") : TEXT ("Closed"),
                        bOpened ? 4 : 6) ;
          TextOut (hdc, cxCaps, 2 * cyChar, moc.szPname,
                        lstrlen (moc.szPname)) ;
          TextOut (hdc, cxCaps, 3 * cyChar, szBuffer, lstrlen (szBuffer)) ;
          TextOut (hdc, cxCaps, 4 * cyChar,
                        fam[iVoice / 8].inst[iVoice % 8].szInst,
               lstrlen (fam[iVoice / 8].inst[iVoice % 8].szInst)) ;
     
          EndPaint (hwnd, &ps) ;
          return 0 ;
               
     case WM_DESTROY :
          SendMessage (hwnd, WM_COMMAND, IDM_CLOSE, 0L) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}